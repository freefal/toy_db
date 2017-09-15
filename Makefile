CC=gcc
CFLAGS=-I. -lm
DEPS = 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

toy_db: main.o 
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
	rm toy_db 
