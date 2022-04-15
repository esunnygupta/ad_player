#!/bin/bash

#sudo apt update
sudo apt install libc-ares-dev libssl-dev

ROOT=$(pwd)

# Setup cJSON
cd $ROOT
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
cd $ROOT
tar -xf compressed/mosquitto-2.0.14.tar.gz
cd $ROOT/mosquitto-2.0.14
#make LDFLAGS="-L$ROOT/output/cJSON" CFLAGS="-I$ROOT/output/cJSON"
make
sudo make install

# Setup Mongo C Driver
cd $ROOT
tar -xf compressed/mongo-c-driver-1.20.1.tar.gz
cd $ROOT/mongo-c-driver-1.20.1
mkdir cmake_build
cd cmake_build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install

# Setup curl library
cd $ROOT
tar -xf compressed/curl-7.82.0.tar.gz
cd $ROOT/curl-7.82.0
./configure --with-openssl
make
sudo make install
