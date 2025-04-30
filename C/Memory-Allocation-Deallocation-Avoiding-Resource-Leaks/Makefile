CC=gcc
FILES=Driver.c MemoryManager.c
OUT_EXE=Driver

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

all: build

run: build
	./$(OUT_EXE)

clean:
	rm -f *.o $(OUT_EXE)`