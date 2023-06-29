#!/bin/sh
set -e

rm -rf ./build

cd ./kernel
make all || exit 1
cd ..

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp kernel/myos.kernel isodir/boot/myos.kernel

cat > isodir/boot/grub/grub.cfg << EOF
menuentry "myos" {
	multiboot /boot/myos.kernel
}
EOF
grub-mkrescue -o myos.iso isodir



