all: build build/get_html build/parse_html

build:
	mkdir -p build
build/get_html: source/fetch_youdao.c
	gcc source/fetch_youdao.c -o build/get_html -lcurl -lz
build/parse_html: source/parse_html.c
	gcc -I/usr/include/libxml2 source/parse_html.c -o build/parse_html  -lxml2 -lz -llzma -licui18n -licuuc -licudata -lm

clean:
	rm  -r build

install:
	sudo cp build/get_html          /usr/bin
	sudo cp build/parse_html        /usr/bin
	sudo cp source/dic              /usr/bin
	sudo cp source/dic_uninstall    /usr/bin