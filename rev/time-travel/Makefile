all: handout

handout: handout/time_travel handout/input.bin

handout/time_travel: src/main.c src/chall.c src/chall.h
	gcc -O0 -o handout/time_travel src/main.c src/chall.c
	strip --keep-symbol=main --keep-symbol=read_input handout/time_travel

handout/input.bin: generate.py flag.txt
	python3 generate.py

clean:
	rm -f handout/time_travel handout/input.bin

.PHONY: clean handout
