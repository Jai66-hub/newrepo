all: clean target
clean:
  rm -f a.out
target:
  gcc hw3.c -o search
