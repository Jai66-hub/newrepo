all: clean target

clean:
        rm -fr search

target:
        gcc -o search search.c
