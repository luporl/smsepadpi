# vim: noexpandtab

CFLAGS := -Wall -Werror -g

all: smsepad

smsepad: smsepad.o
	$(CC) -o $@ $< -lwiringPi

tags:
	ctags -R .

clean:
	rm -f *.o smsepad tags
