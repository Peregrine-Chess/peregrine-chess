LD = gcc
CC = gcc

CFLAGS := \
	-Isrc/include \
	-Wall \
	-Wextra \
	-std=gnu99 \

CFILES := $(shell find src/ -name '*.c')
OFILES := $(CFILES:.c=.o)

TARGET = cheese

all: clean compile run

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
	@ echo "| [ CLEAN ]"
	@ rm -rf $(OFILES) $(TARGET)
	@ echo "|------------"

run:
	@ ./cheese
