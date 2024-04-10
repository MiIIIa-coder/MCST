OBJECTS = main.o bitvec.o
HEADERS = bitvec.hpp 
CC = g++
CFLAGS = -Wall

.PHONY: all
all: bitvec

bitvec: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o bitvec

%.o: %.cpp $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run clean
run: all
	./bitvec

clean:
	rm $(OBJECTS)	
