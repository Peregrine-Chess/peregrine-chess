LD = gcc
CC = gcc

CFLAGS := \
	-Isrc/include \
	-Wall \
	-Wextra \
	-Wno-unused-value\
	-Wno-unused-parameter\
	-Wno-return-type\
	-std=gnu99 \

CFILES := $(shell find src/ -name '*.c')
OFILES := $(CFILES:.c=.o)

TARGET = cheese

all: welcome clean compile

welcome:
	@ echo "   .::."
	@ echo "   _::_"
	@ echo " _/____\_"
	@ echo " \      /"
	@ echo "  \____/"
	@ echo "  (____)"
	@ echo "   |  |  C H E E S E"
	@ echo "   |__|  C H E S S"
	@ echo "  /    \\"
	@ echo " (______)"
	@ echo "(________)"
	@ echo "/________\\"
	@ echo ""

compile: ld
	@ echo "| Done!"
	@ echo "|------------"
	
ld: $(OFILES)
	@ echo "|------------"
	@ echo "| [ LD ] $^"
	@ $(LD) $^ -o $(TARGET)
	@ echo "|------------"

%.o: %.c
	@ echo "| [ CC ] $<"
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ echo "|------------"
	@ echo "| [ CLEAN ]"
	@ rm -rf $(OFILES) $(TARGET)
	@ echo "|------------"

run:
	@ ./cheese

install:
	@ echo "|------------"
	@ echo "| Installing..."
	@ echo "|------------"
	@ cp ./cheese /usr/bin
	@ echo "| Done!"
	@ echo "|------------"
