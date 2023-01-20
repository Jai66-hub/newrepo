all: clean target

clean:
        rm -fr a.out

target:
        gcc blazerid_HW01.c
