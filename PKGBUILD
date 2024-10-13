# Maintainer: Your Name <your.email@example.com>
pkgname=dic
pkgver=1.0.0
pkgrel=1
pkgdesc="A simple translation tool"
arch=('x86_64')
depends=('glibc' 'curl' 'libxml2' 'zlib')
makedepends=('gcc' 'make')
source=("git+https://github.com/iowrite/dic.git")
sha256sums=('SKIP') # 你可以在这里填写实际的校验和

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