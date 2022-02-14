ECHO=echo
CP=cp
RM=rm
MV=mv
MKDIR=mkdir
PROJECT=ad_platform

CC=gcc #arm-linux-gnueabihf-gcc
AR=ar  #arm-linux-gnueabihf-ar
CFLAGS=-Wall -g
IDIR=-I/usr/local/include -I/usr/include/SDL2 -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0
LDFLAGS=-L./lib/
LD_LIBRARY_PATH=
LIBS=-lpthread -lmosquitto -lmpv -lSDL2-2.0 -lrt -lmongoc-1.0 -lbson-1.0 -lcjson -lhttp_client
EXE=$(PROJECT).elf
