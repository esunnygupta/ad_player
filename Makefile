include $(PRJROOT)/inc.mk

all: clean app link

run:
	@./bin/$(EXE)

link:
	$(CC) -o $(EXE) build/*.o $(CFLAGS) $(LDFLAGS) $(LIBS)
	@$(MV) $(EXE) bin

create_build:
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p src/include

setup: create_build headers
	$(MAKE) -C lib

app: create_build headers
	$(MAKE) -C src/main build
	$(MAKE) -C src/osal build
	$(MAKE) -C src/subscriber build
	$(MAKE) -C src/player build
	$(MAKE) -C src/mongoc build
	$(MAKE) -C src/auth build
	$(MAKE) -C src/downloader build

headers:
	$(MAKE) -C src/main headers
	$(MAKE) -C src/osal headers
	$(MAKE) -C src/subscriber headers
	$(MAKE) -C src/player headers
	$(MAKE) -C src/mongoc headers
	$(MAKE) -C src/auth headers
	$(MAKE) -C src/downloader headers

clean:
	$(MAKE) -C src/main clean
	$(MAKE) -C src/osal clean
	$(MAKE) -C src/subscriber clean
	$(MAKE) -C src/player clean
	$(MAKE) -C src/mongoc clean
	$(MAKE) -C src/auth clean
	$(MAKE) -C src/downloader clean
	$(MAKE) -C lib clean
	@$(RM) -rf src/include
	@$(RM) -rf build/*.o
	@$(RM) -rf build
	@$(RM) -rf bin/*
	@$(RM) -rf bin
	@clear
