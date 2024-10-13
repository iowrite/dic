# Maintainer: hewo <iowrite@icloud.com>
pkgname=dic
pkgver=1.0.2
pkgrel=1
pkgdesc="A command line translate tool useing youdao web api"
arch=('x86_64')
depends=('glibc' 'curl' 'libxml2' 'zlib')
makedepends=('gcc' 'make')
source=("git+https://github.com/iowrite/dic.git")
sha256sums=('SKIP') 

build() {
    cd "$srcdir/dic"
    make
} 

package() {
    cd "$srcdir/dic/"
    install -Dm755 source/dic "$pkgdir/usr/bin/dic"
    install -Dm755 build/get_html "$pkgdir/usr/bin/get_html"
    install -Dm755 build/parse_html "$pkgdir/usr/bin/parse_html"
}