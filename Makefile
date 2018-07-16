
OBJECTS += main.o src/fika/common_string.o src/fika/linux_io.o src/fika/arch/x86/syscall.o

# Perhaps remove this too... In the future.
CRT1=$(whereis /usr/lib/x86_64-linux-gnu/crt1.o)

all: $(OBJECTS)
	g++ $(OBJECTS) -o a.out

%.o: %.asm
	nasm -f elf64 $< -o $@

%.o: %.cpp
	g++ -nostdlib -c $< -o $@ -Isrc/fika/arch/x86

clean:
	rm $(OBJECTS)