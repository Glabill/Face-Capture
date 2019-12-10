CC=g++

CFLAGS=-c -Wall -g

CONFIG=`pkg-config --cflags --libs opencv`

RSCONF=-lrealsense2

all : final

final : main.o Core.o StreamManager.o ImageProcessor.o
	$(CC) main.o StreamManager.o ImageProcessor.o Core.o $(RSCONF) -o final $(CONFIG) 

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

Core.o : Core.cpp
	$(CC) $(CFLAGS) Core.cpp

StreamManager.o : StreamManager.cpp
	$(CC) $(CFLAGS) StreamManager.cpp

ImageProcessor.o : ImageProcessor.cpp
	$(CC) $(CFLAGS) ImageProcessor.cpp

clean :
	rm -rf *o final
