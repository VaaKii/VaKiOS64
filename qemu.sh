#!/bin/bash

sh build.sh

qemu-system-i386 -cdrom myos.iso -monitor stdio -S -s


rm -rf isodir
rm -rf myos.iso
