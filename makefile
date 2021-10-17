CC := gcc

all: bouncer

bouncer: bouncer.c
	$(CC) $^ -o $@

clean: bouncer
	rm bouncer

run: bouncer
	./bouncer
