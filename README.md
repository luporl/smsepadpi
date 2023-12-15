# smsepadpi

Use your SMS Evolution Gamepad on a Raspberry Pi!

(tested on Raspberry Pi 3 only)

## Cable pinout

You'll need a cable to connect your SMS Evolution gamepad to Rasperry Pi's GPIO pins.
It consists of a male DB9 connector in one side and a 10 way female Modu connector on the other side.
Below is how the pins should be connected, from DB9 to Modu:

```
DB9 | Button      | Modu
------------------------
1     UP               2
2     DOWN             3
3     LEFT             4
4     RIGHT            7
5     X+Y+Z            6
6     BUTTON 1         9
7     START            8
8     GND              5
9     BUTTON 2        10
```

This table shows the mapping between the Modu connector and RPi's pins:

```
Modu | Function  | RPi
----------------------
 2     GPIO.05      29
 3     GPIO.12      32
 4     GPIO.06      31
 5     GND          34
 6     GPIO.13      33
 7     GPIO.16      36
 8     GPIO.19      35
 9     GPIO.20      38
10     GPIO.26      37
```

In summary, the cable must be connected to RPi's pins 28 to 38.
The Modu connector that I used has the following layout, when viewed from the top (wire side):

```
 _________
|  2 |  1 |
|  4 |  3 |
|  6 |  5 |
|  8 |  7 |
| 10 |  9 |
 ---------
```

## Installation

First, you need to build the DTB overlay and (optionally) the test program:
```
make
```

To build only the DTB overlay:
```
make smsepad.dtbo
```

Next, copy `smsepad.dtbo` to RPi. Put it in `/boot/overlays`.
Then edit `/boot/config.txt` and add the following line:
```
dtoverlay=smsepad
```

That's it. Save, reboot and the gamepad should be detected and loaded automatically, but as a keyboard.
This is the mapping between the keyboard and the gamepad:

```
UP          W
DOWN        S
LEFT        A
RIGHT       D
BUTTON 1    K
BUTTON 2    L
START       E
X+Y+Z       Q
```
