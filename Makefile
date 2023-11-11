all: src/main.c src/passgen.c src/file.c
	gcc -o ftwgpm src/main.c src/passgen.c src/file.c
