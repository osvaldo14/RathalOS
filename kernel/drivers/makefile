CB=gcc -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -g

all:timer.o keyboard.o key_map.o pic.o ide.o shell_drivers.o

timer.o: timer.c timer.h
	$(CB) -c $< -o $@

keyboard.o: keyboard.c keyboard.h
	$(CB) -c $< -o $@

key_map.o: key_map.c key_map.h
	$(CB) -c $< -o $@

pic.o: pic.c pic.h
	$(CB) -c $< -o $@

ide.o: ide.c ide.h
	$(CB) -c $< -o $@

shell_drivers.o: shell_drivers.c shell_drivers.h
	$(CB) -c $< -o $@

clean:
	rm -f *.o