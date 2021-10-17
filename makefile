CC := gcc

all: bouncer

bouncer: bouncer.c
	gcc $^ -o $@

clean: bouncer
	rm bouncer

run: bouncer
	./bouncer
