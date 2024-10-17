# dic
This is a command line dictionary(English to Chinese only) using [youdao web](https://www.youdao.com/) API.

## usage 

    dic word



## dependence
* zlib
* libcurl
* libxml2

### ubuntu
    apt install libcurl4-openssl-dev libxml2-dev liblzma-dev zlib1g-dev


## build
### from source
    make

## install 

### from source
    make install 
### arch linux
    makepkg -si

## uninstall 
### from source
    dic_uninstall
### arch linux
    pacman -R dic dic-debug
and then remove source code file.
