CC=mpicc

handout/parallelism: src/main.c
	mpicc -o handout/parallelism src/main.c
	strip handout/parallelism

gen_flag: src/main.c
	mpicc -o gen_flag src/main.c -DGEN_EXPECTED_FLAG=1

clean:
	rm handout/parallelism processed.txt gen_flag

.PHONY: clean
