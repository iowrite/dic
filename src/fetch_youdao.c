#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <zlib.h>

// 定义一个结构体来存储接收到的数据
struct MemoryStruct {
    char *memory;
    size_t size;
};

// 回调函数，用于处理接收到的数据
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        // out of memory!
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// 解压gzip数据
void ungzip_data(const unsigned char *in, size_t in_size, unsigned char **out, size_t *out_size)
{
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if(inflateInit2(&zs, 16 + MAX_WBITS) != Z_OK) {
        fprintf(stderr, "Error initializing zlib stream\n");
        return;
    }

    zs.next_in = (Bytef *)in;
    zs.avail_in = in_size;
    zs.next_out = (Bytef *)*out;
    zs.avail_out = *out_size;

    int ret;
    do {
        ret = inflate(&zs, Z_NO_FLUSH);
        if(ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            fprintf(stderr, "Error inflating data\n");
            inflateEnd(&zs);
            return;
        }
        if(zs.avail_out == 0) {
            // Need more output space
            *out_size *= 2;
            *out = realloc(*out, *out_size);
            zs.next_out = (Bytef *)*out + zs.total_out;
            zs.avail_out = *out_size - zs.total_out;
        }
    } while(ret != Z_STREAM_END);

    *out_size = zs.total_out;
    inflateEnd(&zs);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    char url[256];
    snprintf(url, sizeof(url), "https://www.youdao.com/result?word=%s&lang=en", word);

    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    unsigned char *ungzipped_data = NULL;
    size_t ungzipped_size = 0;

    // 初始化全局环境
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // 创建一个curl会话句柄
    curl = curl_easy_init();
    if(curl) {
        // 设置请求的URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // 设置回调函数和用户数据指针
        chunk.memory = malloc(1);  // will be grown as needed by the realloc above
        chunk.size = 0;            // no data at this point
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // 设置HTTP头
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:131.0) Gecko/20100101 Firefox/131.0");
        headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br, zstd");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 执行请求
        res = curl_easy_perform(curl);

        // 检查错误
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // 假设数据是gzip压缩的，尝试解压
            ungzipped_size = chunk.size * 2;  // 初始分配两倍的空间
            ungzipped_data = malloc(ungzipped_size);
            ungzip_data((unsigned char *)chunk.memory, chunk.size, &ungzipped_data, &ungzipped_size);

            // 将解压后的内容写入文件
            FILE *file = fopen("output.html", "w");
            if(file == NULL) {
                perror("Failed to open file");
                free(chunk.memory);
                free(ungzipped_data);
                return 1;
            }
            fwrite(ungzipped_data, 1, ungzipped_size, file);
            fclose(file);

            // printf("Data written to output.html\n");
        }

        // 清理HTTP头
        curl_slist_free_all(headers);

        // 清理内存
        free(chunk.memory);
        free(ungzipped_data);

        // 清理curl句柄
        curl_easy_cleanup(curl);
    }

    // 清理全局环境
    curl_global_cleanup();

    return 0;
}