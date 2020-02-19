CC=g++

CFLAGS=-c -Wall -g

CONFIG=`pkg-config --cflags --libs opencv`

RSCONF=-lrealsense2

OUT=bin/

all : final

final : main.o Core.o StreamManager.o ImageProcessor.o
	$(CC) $(OUT)main.o $(OUT)StreamManager.o $(OUT)ImageProcessor.o $(OUT)Core.o $(RSCONF) -o $(OUT)F4C3 $(CONFIG)
main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(OUT)main.o

Core.o : Core.cpp
	$(CC) $(CFLAGS) Core.cpp -o $(OUT)Core.o

StreamManager.o : StreamManager.cpp
	$(CC) $(CFLAGS) StreamManager.cpp -o $(OUT)StreamManager.o

ImageProcessor.o : ImageProcessor.cpp
	$(CC) $(CFLAGS) ImageProcessor.cpp -o $(OUT)ImageProcessor.o

clean :
	rm -rf *o final
	cd bin && rm -rf *o final
