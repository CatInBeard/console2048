CC=g++
root_include_dir = headers
all:
	$(CC) main.cpp  -lncurses -o output/console2048 -O2 -time -I headers -I headers/*
clean:
	rm -rf *.o
