#!/bin/bash

RELEASE=wheezy
DIR=wheezy

# Build a disk image
rm $RELEASE.img
dd if=/dev/zero of=$RELEASE.img bs=1M seek=2047 count=1
sudo mkfs.ext4 -F $RELEASE.img
sudo mkdir -p /mnt/$DIR
sudo mount -o loop $RELEASE.img /mnt/$DIR
sudo cp -a $DIR/. /mnt/$DIR/.
sudo umount /mnt/$DIR
