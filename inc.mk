ECHO=echo
CP=cp
RM=rm
MV=mv
MKDIR=mkdir
PROJECT=ad_platform

CC=gcc #arm-linux-gnueabihf-gcc
AR=ar  #arm-linux-gnueabihf-ar
CFLAGS=-Wall -g
IDIR=-I/usr/local/include -I/usr/include/SDL2
LDFLAGS=-L./lib/
LD_LIBRARY_PATH=
LIBS=-lpthread -lmosquitto -lmpv -lSDL2-2.0 -lrt
EXE=$(PROJECT).elf
