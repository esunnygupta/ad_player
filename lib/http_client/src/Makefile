include $(PRJROOT)/inc.mk

IDIR=-I../include -I../../../src/include/
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
OUTPUT=libhttp_client.so

all: clean build

build:$(OBJS)
	@$(MKDIR) builds
	$(CC) -shared -o $(OUTPUT) $(OBJS) $(IDIR)
	$(CP) $(OUTPUT) $(PRJROOT)/lib
	$(MV) -f *.o builds

%.o:%.c
	$(CC) -fPIC -c $(IDIR) $<

clean:
	@$(RM) -rf *.o
	@$(RM) -rf builds $(OUTPUT)
	@clear
