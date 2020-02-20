CC = g++

CFLAGS = -c -Wall -g

CONFIG = `pkg-config --cflags --libs opencv`

RSCONF = -lrealsense2

OUT=objects/

SOURCES=sources/

all : final

final : main.o Core.o StreamManager.o ImageProcessor.o
	$(CC) $(OUT)main.o $(OUT)StreamManager.o $(OUT)ImageProcessor.o $(OUT)Core.o $(RSCONF) -o F4C3 $(CONFIG)
main.o : $(SOURCES)main.cpp
	$(CC) $(CFLAGS) $(SOURCES)main.cpp -o $(OUT)main.o

Core.o : $(SOURCES)Core.cpp
	$(CC) $(CFLAGS) $(SOURCES)Core.cpp -o $(OUT)Core.o

StreamManager.o : $(SOURCES)StreamManager.cpp
	$(CC) $(CFLAGS) $(SOURCES)StreamManager.cpp -o $(OUT)StreamManager.o

ImageProcessor.o : $(SOURCES)ImageProcessor.cpp
	$(CC) $(CFLAGS) $(SOURCES)ImageProcessor.cpp -o $(OUT)ImageProcessor.o

clean :
	rm -rf *o final F4C3
	cd objects && rm -rf *o final F4C3
	cd output/arch && rm -rf *
	cd output && rm -rf *png

