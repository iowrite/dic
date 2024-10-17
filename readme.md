# dic
This is a command line dictionary(English to Chinese only) using [youdao web](https://www.youdao.com/) API.

## 1 usage 

    dic word



## 2 dependence
* zlib
* libcurl
* libxml2

### 2.1 ubuntu
    apt install libcurl4-openssl-dev libxml2-dev liblzma-dev zlib1g-dev


## 3 build
### 3.1 from source
    make

## 4 install 

### 4.1 from source
    make install 
### 4.2 arch linux
    makepkg -si

## 5 uninstall 
### 5.1 from source
    dic_uninstall
### 5.2 arch linux
    pacman -R dic dic-debug

    
and then remove source code file.
