# Maintainer: Your Name <your.email@example.com>
pkgname=translate
pkgver=1.0.0
pkgrel=1
pkgdesc="A simple translation tool"
arch=('x86_64')
url="https://github.com/yourusername/translate"
license=('GPL3')
depends=('glibc' 'curl' 'libxml2' 'zlib')
makedepends=('gcc' 'make')
source=("translate-$pkgver.tar.gz::https://github.com/yourusername/translate/archive/v$pkgver.tar.gz")
sha256sums=('SKIP') # 你可以在这里填写实际的校验和

build() {
    cd "$srcdir/translate-$pkgver"
    make
}

package() {
    cd "$srcdir/translate-$pkgver"
    install -Dm755 build/get_html "$pkgdir/usr/bin/get_html"
    install -Dm755 build/parse_html "$pkgdir/usr/bin/parse_html"
}