include $(PRJROOT)/inc.mk

all: clean app link

run:
	@./bin/$(EXE)

link:
	$(CC) -o $(EXE) build/*.o $(LDFLAGS) $(CFLAGS) $(LIBS)
	@$(MV) $(EXE) bin

create_build:
	@mkdir build
	@mkdir bin

setup:
	$(MAKE) -C lib

app: create_build headers
	$(MAKE) -C src/main build
	$(MAKE) -C src/osal build
	$(MAKE) -C src/subscriber build
	$(MAKE) -C src/player build

headers:
	$(MAKE) -C src/main headers
	$(MAKE) -C src/osal headers
	$(MAKE) -C src/subscriber headers
	$(MAKE) -C src/player headers

clean:
	$(MAKE) -C src/main clean
	$(MAKE) -C src/osal clean
	$(MAKE) -C src/subscriber clean
	$(MAKE) -C src/player clean
	@$(RM) -rf src/include/*.h
	@$(RM) -rf build/*.o
	@$(RM) -rf build
	@$(RM) -rf bin/*
	@$(RM) -rf bin
	@clear
