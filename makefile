all: build/get_html build/parse_html build

CFLAGS = `xml2-config --cflags`
LDFLAGS = `xml2-config --libs`

build:
	mkdir -p build

build/get_html: build source/fetch_youdao.c
	gcc source/fetch_youdao.c -o build/get_html -lcurl -lz
build/parse_html: build source/parse_html.c
	gcc $(CFLAGS) source/parse_html.c -o build/parse_html  $(LDFLAGS)



clean:
	rm  -r build