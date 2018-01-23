CC=gcc
CFLAGS=-I./include/
LDFLAGS=-lchunfeng
SOURCE=$(shell ls *.c)
TARGET=$(notdir $(shell pwd))
all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o
