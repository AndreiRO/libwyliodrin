/**************************************************************************************************
 * This file contains the functions available on UDOO pin headers.
 * See documentation here: 
 *      http://arduino.cc/en/Reference/HomePage
 *      file:///home/andrei/Desktop/UDOO_Starting_Manual_beta0.4_11_28_2013.pdf
 *
 * Follow "Wyliodrin Coding Style Convention" at:
 *      https://docs.google.com/document/d/14zRCX1KIwvQ1qEzWBVH-We0CkQmd5-kZb81bzvbIQKY/edit
 * 
 * CONTENT:
 * 1.  General configuration
 * 2.  Digital I/O
 * 3.  Analog I/O
 * 4.  Advanced I/O
 * 5.  Time
 * 6.  Communication (Serial, Stream)
 * 7.  UARTs: uart1, uart3, uart4, uart5
 * 8.  SD1
 * 9.  SPIs: spi1, spi2, spi5
 * 10. I2C1
 * 11. Spdif
 * 12. Timer capture
 * 13. Timer compare
 * 14. WATCHDOG FUNCTIONALITIES: watchdog reset, watchdog out
 * 15. Clock out
 * 16. PWMs: pwm1, pwm2, pwm3, pwm4
 * 17. Digital audio 
 *************************************************************************************************/

//#ifdef UDOO
<<<<<<< HEAD
/*
#ifdef __cplusplus
=======

/*#ifdef __cplusplus
>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
extern "C" {
#endif
*/

#include <time.h>
#include "wiring.h"
#include "udooConfig.h"
<<<<<<< HEAD
#include "serial.h"
=======
>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
#include "firmata.h"


/**************************************************************************************************
 * 2. Digital I/O
 *************************************************************************************************/

/**
 * Configures the specified pin to behave either as an input or an output
 * pin: the number of the pin whose mode you wish to set (gpio pin)
 * mode: INPUT or OUTPUT
 */
<<<<<<< HEAD
=======

>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
void pinMode (int pin, int mode) 
{
    if (mode != INPUT && mode != OUTPUT) {
        debug("Mode can be either INPUT or OUTPUT");
        return;
    }
    gpioExport(pin);
    if (mode == INPUT) {
        gpioSetDirInput(pin);
    } else {
        gpioSetDirOutput(pin);
    }
}

/**
 * Write a HIGH or a LOW value to a pin
 * pin: the pin number (gpio pin)
 * value: HIGH or LOW
 */
<<<<<<< HEAD
void digitalWrite (int pin, int value)
{
=======

void digitalWrite (int pin, int value)
{
    pinMode(pin, OUTPUT);
>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
    gpioSetValue(pin, value);
}

/** 
 * Reads the value from a specified digital pin, either HIGH or LOW
 * pin: the number of the digital pin you want to read
 */
<<<<<<< HEAD
=======

>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
int digitalRead (int pin)
{
    // See defined error values in udooConfig.h for invalid/unexported pin that can be returned 
    return gpioGetValue(pin);
}


<<<<<<< HEAD
/**************************************************************************************************
 3. Analog I/O  &  16. PWMs: PWM1, PWM2, PWM3, PWM4
 *************************************************************************************************/

int analogRead (int pin)
{
    firmata_pinMode(firmata, pin, MODE_ANALOG);
    firmata_pull(firmata);
    return firmata->pins[pin].value;
}

void analogWrite (int pin, int value)
{
    t_firmata *firmata;
=======

/**************************************************************************************************
 *  3. Analog I/O 
 * 16. PWMs: pwm1, pwm2, pwm3, pwm4
 *************************************************************************************************/


int analogRead (int pin)
{
    firmata_pinMode(firmata, pin, MODE_ANALOG);
    firmata_pull(firmata);
    return firmata->pins[pin].value;
}

void analogWrite (int pin, int value)
{
    t_firmata *firmata;
    int i = 0;
>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
    char str[] = "/dev/ttymxc3";
    firmata = firmata_new(str);     // init Firmata
    while (!firmata->isReady)       // wait until device is up
        firmata_pull(firmata);
    firmata_pinMode(firmata, pin, MODE_PWM);
    firmata_analogWrite(firmata, pin, value);
}
<<<<<<< HEAD


/**************************************************************************************************
 * 4. Advanced I/O
 *************************************************************************************************/

/*
 * Shifts in a byte of data one bit at a time.
 * Starts either from the most or least significant bit.
 * For each bit the clock pin is pulled high, the next bit is read from the data line, and then
 * the clock pin is taken low. 
 */
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
    uint8_t value = 0;
    uint8_t i;
    for (i = 0; i < 8; i++) {
        digitalWrite(clockPin, HIGH);
        // TODO: handle case if digitalRead() returns error codes
        if (bitOrder == LSBFIRST) {
            value |= digitalRead(dataPin) << i;
        } else {
            value |= digitalRead(dataPin) << (7 - i);
        }
        digitalWrite(clockPin, LOW);
    }
    return value;
}

/*
 * Shifts data out to a clocked source
 * Each bit is written in turn to a data pin after wich a clock pin is pulsed (taken high, 
 * the low), to indicate that the bit is available.
 */ 
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            digitalWrite(dataPin, !!(val & (1 << i)));
        } else {
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));
        }
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}


/**************************************************************************************************
 * 5. Time
 *************************************************************************************************/

/*
 * Pauses the program for the amount of time (in milliseconds) specified as parameter
 * There are 1000 milliseconds in 1 second
 */
void delay (unsigned int ms)
{

 // Suspend execution of the calling thread for (at least) ms microseconds
 
    usleep(ms * 1000);
}

/*
 * Pauses the program for the amount of time (in microseconds) specified
 * as parameter
 */
void delayMicroseconds (unsigned int mcs)
{
    usleep(mcs);
}

/*
 * Returns the number of microseconds since the UDOO board began running the current program
 * This number will go back to zero after some time.
 * Note: there are 1000 microseconds in 1 millisecond and 1000000 microseconds in 1 second
 */
/* 
unsigned int micros ()
{
    struct timespec tm;
    tm.tv_sec = tm.tv_nsec = 0;
    int ret = clock_gettime(CLOCK_REALTIME, &tm);
    if (ret == -1) {
        debug("Clock Time error");
        return CLOCK_TIME_ERROR;
    }
    return (unsigned int)(tm.tv_sec * 1000000L + tm.tv_nsec / 1000L);
}

unsigned int milis ()
{
    return micros() / 1000;
}
*/
=======


/**************************************************************************************************
 * 4. Advanced I/O
 *************************************************************************************************/

/*
 * Shifts in a byte of data one bit at a time.
 * Starts either from the most or least significant bit.
 * For each bit the clock pin is pulled high, the next bit is read from the data line, and then
 * the clock pin is taken low. 
 */
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
    uint8_t value = 0;
    uint8_t i;
    for (i = 0; i < 8; i++) {
        digitalWrite(clockPin, HIGH);
        // TODO: handle case if digitalRead() returns error codes
        if (bitOrder == LSBFIRST) {
            value |= digitalRead(dataPin) << i;
        } else {
            value |= digitalRead(dataPin) << (7 - i);
        }
        digitalWrite(clockPin, LOW);
    }
    return value;
}

/*
 * Shifts data out to a clocked source
 * Each bit is written in turn to a data pin after wich a clock pin is pulsed (taken high, 
 * the low), to indicate that the bit is available.
 */
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            digitalWrite(dataPin, !!(val & (1 << i)));
        } else {
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));
        }
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}



/**************************************************************************************************
 * 5. Time
 *************************************************************************************************/

/*
 * Pauses the program for the amount of time (in milliseconds) specified as parameter
 * There are 1000 milliseconds in 1 second
 */
void delay (unsigned int ms)
{
/*
 * Suspend execution of the calling thread for (at least) ms microseconds
 */
    usleep(ms * 1000);
}

/*
 * Pauses the program for the amount of time (in microseconds) specified
 * as parameter
 */
void delayMicroseconds (unsigned int mcs)
{
    usleep(mcs);
}

/*
 * Returns the number of microseconds since the UDOO board began running the current program
 * This number will go back to zero after some time.
 * Note: there are 1000 microseconds in 1 millisecond and 1000000 microseconds in 1 second
 */
/*
unsigned long micros (void)
{
    struct timespec tm;
    int ret = clock_gettime(CLOCK_REALTIME, &tm);
    if (ret == -1) {
        debug("Clock Time error");
        return CLOCK_TIME_ERROR;
    }
    return (unsigned long)(tm.tv_sec * 1000000L + tm.tv_nsec / 1000L);
}

unsigned long milis (void)
{
    return micros() / 1000;
}
*/

>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
/*
#ifdef __cplusplus
}
#endif
*/
<<<<<<< HEAD
=======

>>>>>>> 45083e654333cd3f28691095aba5ce06a5d4b16a
//#endif /* UDOO */
