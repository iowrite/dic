#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/HTMLparser.h>

int main() {
    // 初始化库
    xmlInitParser();
    LIBXML_TEST_VERSION

    // 打开文件
    const char *filename = "output.html";
    xmlDoc *doc = htmlReadFile(filename, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == NULL) {
        fprintf(stderr, "Document not parsed successfully.\n");
        return EXIT_FAILURE;
    }

    // 获取文档根节点
    xmlNode *root_element = xmlDocGetRootElement(doc);

    // 查找 <ul class="basic">
    xmlXPathContext *xpathCtx = xmlXPathNewContext(doc);
    xmlXPathObject *xpathObj;



    printf("\n-------------->\n");
    // 创建XPath表达式
    const char *xpathExpr = "//ul[@class='basic']//li";
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpathExpr, xpathCtx);

    if (xpathObj != NULL) {
        int size = xpathObj->nodesetval->nodeNr;
        for (int i = 0; i < size; ++i) {
            xmlNode *curNode = xpathObj->nodesetval->nodeTab[i];
            xmlChar *pos = xmlGetProp(curNode, (const xmlChar *)"class");
            if (pos && !xmlStrcmp(pos, (const xmlChar *)"word-exp")) {
                int spancnt = 0;
                xmlNode *child = curNode->children;
                while (child != NULL) {
                    if (child->type == XML_ELEMENT_NODE && !xmlStrcmp(child->name, (const xmlChar *)"span")) {
                        spancnt ++;
                        xmlChar *class = xmlGetProp(child, (const xmlChar *)"class");
                        if (!xmlStrcmp(class, (const xmlChar *)"pos")) {
                            printf("%s\t: ", xmlNodeListGetString(doc, child->children, 1));
                        } else if (!xmlStrcmp(class, (const xmlChar *)"trans")) {
                            if(spancnt == 1){
                                printf("\t:");
                            }
                            printf("%s\n\n", xmlNodeListGetString(doc, child->children, 1));
                        }
                        xmlFree(class);
                    }
                    child = child->next;
                }
            }
            xmlFree(pos);
        }
        xmlXPathFreeObject(xpathObj);
    }


    printf("\n-------------->\n");
    // 创建XPath表达式
    const char *xpathExpr2 = "//div[@class='exam_type']//span";
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpathExpr2, xpathCtx);
    if (xpathObj != NULL) {
        // 检查XPath查询结果
        xmlNodeSetPtr nodeset = xpathObj->nodesetval;
        for (int i = 0; i < nodeset->nodeNr; ++i) {
            xmlNodePtr node = nodeset->nodeTab[i];
            if (node->type == XML_ELEMENT_NODE) {
                xmlChar *content = xmlNodeGetContent(node);
                printf("%s ", content);
                xmlFree(content);
            }
        }
    }





    printf("\n\n-------------->\n");

    // 创建XPath表达式
    const char *xpathExpr3 = "//ul[@class='word-wfs-less']//li";
    xpathObj = xmlXPathEvalExpression((const xmlChar *)xpathExpr3, xpathCtx);

    if (xpathObj != NULL) {
        // printf("1111111\n");
        int size = xpathObj->nodesetval->nodeNr;
        for (int i = 0; i < size; ++i) {
            // printf("22222\n");
            xmlNode *curNode = xpathObj->nodesetval->nodeTab[i];
            xmlChar *pos = xmlGetProp(curNode, (const xmlChar *)"class");
            if (pos && !xmlStrcmp(pos, (const xmlChar *)"word-wfs-cell-less")) {
                // printf("333333\n");
                xmlNode *child = curNode->children;
                while (child != NULL) {
                    if (child->type == XML_ELEMENT_NODE && !xmlStrcmp(child->name, (const xmlChar *)"p")) {
                        // printf("44444 %s\n", child->name);
                        xmlNode *pc = child->children;
                        while (pc != NULL) {
                            // printf("555555 %s\n", pc->name);

                            if (pc->type == XML_ELEMENT_NODE && !xmlStrcmp(pc->name, (const xmlChar *)"span")) {
                                // printf("66666\n");
                                xmlChar *class = xmlGetProp(pc, (const xmlChar *)"class");
                                if (!xmlStrcmp(class, (const xmlChar *)"wfs-name")) {
                                    printf("%s: ", xmlNodeListGetString(doc, pc->children, 1));
                                }
                                xmlFree(class);
                            }
                            pc = pc->next;
                        }
                    }
                    if (child->type == XML_ELEMENT_NODE && !xmlStrcmp(child->name, (const xmlChar *)"span")) {

                        xmlChar *class = xmlGetProp(child, (const xmlChar *)"class");
                        if (!xmlStrcmp(class, (const xmlChar *)"transformation")) {
                            printf("%s\n", xmlNodeListGetString(doc, child->children, 1));
                        }
                        xmlFree(class);
                    }
                    child = child->next;
                }
            }
            xmlFree(pos);
        }
        xmlXPathFreeObject(xpathObj);
    }

    printf("\n");



    // 清理资源
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return EXIT_SUCCESS;
}