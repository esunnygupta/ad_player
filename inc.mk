ECHO=echo
CP=cp
RM=rm
MV=mv
MKDIR=mkdir
PROJECT=ad_platform

CC=gcc #arm-linux-gnueabihf-gcc
AR=ar  #arm-linux-gnueabihf-ar
CFLAGS=-Wall
IDIR=-I/usr/local/include
LDFLAGS=
LD_LIBRARY_PATH=
LIBS=-lpthread -lmosquitto
EXE=$(PROJECT).elf
