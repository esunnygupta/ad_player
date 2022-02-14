include $(PRJROOT)/inc.mk

all: build

build:
	$(MAKE) -C http_client/src
#	@./setup.sh

clean:
	$(MAKE) -C http_client/src clean
	@$(RM) -rf cJSON
	@$(RM) -rf mosquitto-2.0.14
	@$(RM) -rf libwebsockets
	@$(RM) -rf mongo-c-driver-1.20.1
	@clear
