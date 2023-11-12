all: src/main.c src/passgen.c src/file.c src/clipboard.c
	gcc -o bin/ftwgpm src/main.c src/passgen.c src/file.c src/clipboard.c

c: src/clipboard.c
	gcc -o src/clipboard.c

f: src/file.c
	gcc -c src/file.c

p: src/passgen.c
	gcc -c src/passgen.c


