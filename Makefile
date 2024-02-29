all: nedit

nedit: nedit.c
	$(CC) nedit.c -lraylib -lm -o nedit -Wall -W -pedantic -std=c99

clean:
	rm nedit
