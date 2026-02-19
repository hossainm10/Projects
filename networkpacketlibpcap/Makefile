CC=gcc
CFLAGS= -Wall -Wextra -O2 -std=gnu11 -Iheaders -D_DEFAULT_SOURCE
LDFLAGS= -lpcap

SRC_DIR=src
INC_DIR=headers

TARGET=capture_packet
SOURCES= main.c $(SRC_DIR)/capture.c  $(SRC_DIR)/parser.c $(SRC_DIR)/display.c
OBJECTS= main.o src/capture.o src/display.o src/parser.o
HEADERS= $(INC_DIR)/capture_packet.h $(INC_DIR)/capture.h $(INC_DIR)/parser.h $(INC_DIR)/display.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	echo "Build Complete! Run with: sudo ./$(Target) <interface>"

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c -o main.o

src/%.o: src/ %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main.o src/*.o $(TARGET)

run: $(TARGET)
	sudo ./$(TARGET) eth0 50

.PHONY: all clean run
