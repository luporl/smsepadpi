# vim: noexpandtab

CFLAGS := -Wall -Werror -g

all: smsepad smsepad.dtbo

smsepad: smsepad.o
	$(CC) -o $@ $< -lwiringPi

smsepad.dtbo: smsepad.dts
	dtc -I dts -O dtb -o smsepad.dtbo smsepad.dts

tags:
	ctags -R .

clean:
	rm -f *.o smsepad smsepad.dtbo tags
