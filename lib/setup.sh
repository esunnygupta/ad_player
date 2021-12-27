#!/bin/bash

#sudo apt update
sudo apt install libc-ares-dev libssl-dev

ROOT=$(pwd)

# Setup cJSON
git clone https://github.com/DaveGamble/cJSON.git
cd cJSON
mkdir build
cd build
#cmake .. -DCMAKE_INSTALL_PREFIX=$ROOT/output/cJSON
cmake ..
make
sudo make install

# Setup libwebsockets-dev
cd $ROOT
git clone https://github.com/warmcat/libwebsockets.git
cd libwebsockets
mkdir build
cd build
cmake ..
make
sudo make install

# Setup Mosquitto
tar -xf mosquitto-2.0.14.tar.gz
cd $ROOT/mosquitto-2.0.14
#make LDFLAGS="-L$ROOT/output/cJSON" CFLAGS="-I$ROOT/output/cJSON"
make
sudo make install
