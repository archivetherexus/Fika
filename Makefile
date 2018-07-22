
OBJECTS += main.o
CFLAGS += -g -nostdlib -Isrc -fmax-errors=1
include src/fika/targets/linux/target.mk

# Perhaps remove this too... In the future.
CRT1=$(whereis /usr/lib/x86_64-linux-gnu/crt1.o)

all: $(OBJECTS)
	g++ $(OBJECTS) -o a.out

%.o: %.asm
	nasm -g -f elf64 $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)