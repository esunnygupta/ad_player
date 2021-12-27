include $(PRJROOT)/inc.mk

all: build

build: setup_mosquitto

setup_mosquitto:
	@./setup.sh

clean:
	@$(RM) -rf cJSON
	@$(RM) -rf mosquitto-2.0.14
	@$(RM) -rf libwebsockets
	@clear
