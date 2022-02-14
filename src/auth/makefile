include $(PRJROOT)/inc.mk

IDIR+=-Iinclude/
IDIR+=-I$(PRJROOT)/src/include/
IDIR+=-I$(PRJROOT)/lib/http_client/include
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

headers:
	@$(CP) include/*.h $(PRJROOT)/src/include/

build:$(OBJS)
	@$(ECHO) "\033[0;32m----------compiling auth completed----------\033[0;37m"
	@$(MV) *.o $(PRJROOT)/build/

%.o:%.c
	$(CC) $(IDIR) $(CFLAGS) -c $<

clean:
	@rm -rf *.o
