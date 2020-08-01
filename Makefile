CFLAGS += -Wall -pedantic -Ofast -std=c99

.PHONY: t9

t9:
	$(CC) $(CFLAGS) -o t9 t9.c

run: t9
	./t9
