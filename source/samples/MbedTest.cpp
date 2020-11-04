#include "MicroBit.h"
#include "mbed.h"

class TimeoutTest {
    public:

    Timeout timeout;

    void onTimeout() {
        uBit.display.image.setPixelValue(0,1,0xFF);
    }

    void setup() {
        timeout.attach(this, &TimeoutTest::onTimeout, 10.0f);
    }

    TimeoutTest() {
    } 

};

class TickerTest {
    public:

    Ticker ticker;
    bool value = 0;

    void onTick() {
        uBit.display.image.setPixelValue(0,2,value ? 0xFF : 0);
        value = !value;
    }

    void setup() {
        ticker.attach(this, &TickerTest::onTick, 5.0f);
    }

    TickerTest() {
    } 

};

class InterruptTest {
    public:
    InterruptIn *interruptIn;

    void rise() {
        uBit.display.scroll("rise");
    }

    void fall() {
        uBit.display.scroll("fall");
    }

    void setup() {
        interruptIn = new InterruptIn((PinName) BUTTONA);
        interruptIn->mode(PullUp);
        interruptIn->rise(this, &InterruptTest::rise);
        interruptIn->fall(this, &InterruptTest::fall);
    }

};

TimeoutTest timeoutTest;
TickerTest tickerTest;
InterruptTest interruptIn;

int 
mbed_test()
{
    PwmOut pwm((PinName)P0_00);

    timeoutTest.setup();
    tickerTest.setup();
    interruptIn.setup();

    while(1) {
        uBit.display.image.setPixelValue(0,0,0);
        pwm.write(0.5);
        uBit.sleep(500);
        uBit.display.image.setPixelValue(0,0,0xFF);
        pwm.write(0.0);
        uBit.sleep(500);
    }
}
