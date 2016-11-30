all: clean network
INCLUDES=-I.  -I/apps/networking/thirdparty/boost/include
LIBDIR=-L. -L/usr/lib/ -L/apps/networking/thirdparty/boost/lib/
LIBS= -lboost_filesystem -lpthread -lboost_thread -lboost_system -lboost_iostreams -lboost_coroutine -lboost_context -ldl
CC=g++ -g -std=c++0x -pthread

network: connection.o
		$(CC) $(INCLUDES) $(LIBDIR) main.cpp \
		obj/connection.o \
		$(LIBS) -o network

connection.o: asio/connection.cpp
		$(CC) $(INCLUDES) -c $(LIBDIR) asio/connection.cpp $(LIBS) -o obj/connection.o	
clean: 
		rm -f network

IMAGE_NAME = networking
CONTAINER_NAME = networking
VOLUMES = -v ${PWD}/..:/apps/networking
PORTS = -p 9999:9999

help:
	@echo "Please use 'make <target>' where <target> is one of"
	@echo "  dbuild           build the docker image"
	@echo "  drebuild         rebuilds the image from scratch without using any cached layers"
	@echo "  drun             run the built docker image"
	@echo "  drestart         restarts the docker image"
	@echo "  druntest         run the unit tests in a docker container and exit"
	@echo "  dbash            starts bash inside a running container."

dbuild:
	@echo "Building docker image..."
	docker build -t ${IMAGE_NAME} .

drebuild:
	@echo "Rebuilding docker image..."
	docker build --no-cache=true -t ${IMAGE_NAME} .

ddorun:
	@echo "Running docker image..."
	docker run --rm $(VOLUMES) $(HOSTS) ${PORTS} -i -t ${IMAGE_NAME} --name=$(CONTAINER_NAME)

druntest:
	make dstop
	make dbuild
	docker run --rm $(VOLUMES) $(HOSTS) -h ewr-fbrain-x1 --entrypoint=/d1/apps/brain/brain-test/test-entrypoint.sh -t ${IMAGE_NAME} --name=$(CONTAINER_NAME)

drun: dstop dbuild ddorun

dcompile:
	make dstop
	make dbuild
	docker run --rm $(VOLUMES) ${PORTS} -t ${IMAGE_NAME} --name=$(CONTAINER_NAME)

drestart: drun

dbash:
	docker exec -it $(CONTAINER_NAME) /bin/bash

dstop:
	-docker stop $(CONTAINER_NAME)