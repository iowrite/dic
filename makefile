all: get_html parse_html

CFLAGS = `xml2-config --cflags`
LDFLAGS = `xml2-config --libs`


get_html:src/fetch_youdao.c
	gcc src/fetch_youdao.c -o build/get_html -lcurl -lz
parse_html: src/parse_html.c
	gcc $(CFLAGS) -o build/parse_html src/parse_html.c $(LDFLAGS)



clean:
	rm  build/*