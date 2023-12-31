/*
 * This code is intended to run on a Raspberry Pi 3 Model B,
 * with the WiringPi Library.
 */

#include <assert.h>
#include <stdio.h>
#include <wiringPi.h>


/* Macros */

/*
 * _____________________
 * | 1 | 3 | 5 | 7 | 9 |
 * ---------------------    (SMS DB9 to 10-pin cable connector)
 * | 2 | 4 | 6 | 8 | X |
 * ---------------------
 *
 * 1- up
 * 2- down
 * 3- left
 * 4- right
 * 5- x+y+z
 * 6- button 1
 * 7- start
 * 8- gnd
 * 9- button 2
 */

#define PAD_UP          0
#define PAD_DOWN        1
#define PAD_LEFT        2
#define PAD_RIGHT       3
#define PAD_XYZ         4
#define PAD_BUTTON1     5
#define PAD_START       6
#define PAD_GND         7
#define PAD_BUTTON2     8

/* NOTE: wiringPi pin numbering */
#define PAD_UP_PIN      21  /* GPIO.5  */
#define PAD_DOWN_PIN    26  /* GPIO.12 */
#define PAD_LEFT_PIN    22  /* GPIO.6  */
#define PAD_RIGHT_PIN   27  /* GPIO.16 */
#define PAD_XYZ_PIN     23  /* GPIO.13 */
#define PAD_BUTTON1_PIN 28  /* GPIO.20 */
#define PAD_START_PIN   24  /* GPIO.19 */
#define PAD_BUTTON2_PIN 25  /* GPIO.26 */


/* Data */

static char g_keyval[9];
static char g_keymap[10] = "wsadqke0l";


/* Functions */

static inline int pad_pressed(int key)
{
    assert(key < 9);
    return !g_keyval[key];
}

static void pad_setup(void)
{
    pinMode(PAD_UP_PIN, INPUT);
    pinMode(PAD_DOWN_PIN, INPUT);
    pinMode(PAD_LEFT_PIN, INPUT);
    pinMode(PAD_RIGHT_PIN, INPUT);
    pinMode(PAD_XYZ_PIN, INPUT);
    pinMode(PAD_BUTTON1_PIN, INPUT);
    pinMode(PAD_START_PIN, INPUT);
    pinMode(PAD_BUTTON2_PIN, INPUT);

    pullUpDnControl(PAD_UP_PIN, PUD_UP);
    pullUpDnControl(PAD_DOWN_PIN, PUD_UP);
    pullUpDnControl(PAD_LEFT_PIN, PUD_UP);
    pullUpDnControl(PAD_RIGHT_PIN, PUD_UP);
    pullUpDnControl(PAD_XYZ_PIN, PUD_UP);
    pullUpDnControl(PAD_BUTTON1_PIN, PUD_UP);
    pullUpDnControl(PAD_START_PIN, PUD_UP);
    pullUpDnControl(PAD_BUTTON2_PIN, PUD_UP);

    /* Wait for stabilization of signals */
    delayMicroseconds(10);
}

static void pad_read(void)
{
    g_keyval[PAD_UP] = digitalRead(PAD_UP_PIN);
    g_keyval[PAD_DOWN] = digitalRead(PAD_DOWN_PIN);
    g_keyval[PAD_LEFT] = digitalRead(PAD_LEFT_PIN);
    g_keyval[PAD_RIGHT] = digitalRead(PAD_RIGHT_PIN);
    g_keyval[PAD_XYZ] = digitalRead(PAD_XYZ_PIN);
    g_keyval[PAD_BUTTON1] = digitalRead(PAD_BUTTON1_PIN);
    g_keyval[PAD_START] = digitalRead(PAD_START_PIN);
    g_keyval[PAD_BUTTON2] = digitalRead(PAD_BUTTON2_PIN);
}

static void pad_print(void)
{
    int i;

    printf("pad:");
    for (i = 0; i < 9; i++)
        if (pad_pressed(i))
            printf(" %c", g_keymap[i]);
    printf("\n");
}

int main()
{
    /* Init wiringPi */
    if (wiringPiSetup() == -1) {
        printf("failed to initialize wiringPi\n");
        return 1;
    }

    pad_setup();
    /* Specify gamepad's GND pin (8) as never pressed */
    g_keyval[PAD_GND] = 1;

    printf("SMSE Pad on Pi started\n");

    while (1) {
        pad_read();
        pad_print();
        delay(500);	/* ms */
    }
    return 0;
}
