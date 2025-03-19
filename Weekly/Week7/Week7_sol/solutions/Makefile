CC := gcc
FLAGS = -Wall

PROGRAMS = $(patsubst %.c,%.o,$(wildcard *.c))
DEP = matvec.h

.PHONY : all clean

all: $(PROGRAMS)

$(PROGRAMS): %.o : %.c
	$(CC) $< -o $@ $(FLAGS) -fopenmp

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
