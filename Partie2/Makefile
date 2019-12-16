CC := g++
CFLAGS := -std=c++11

all : main

main : main.o
	$(CC) $(CFLAGS) -fopenmp -o $@  $<

%.o : %.cpp
	$(CC) $(CFLAGS) -fopenmp -o $@ -c $<

clean:
	rm -f *.o *~ main