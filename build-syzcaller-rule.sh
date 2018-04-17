#!/bin/bash

./bin/syz-extract -arch amd64 -os linux -sourcedir=$KERNEL i2c.txt
make generate &&
make
