#ifndef DWBUTTON_H
#define DWBUTTON_H

#include <Arduino.h>

#define DW_TICK_DELAY 50
#define DW_SIGNAL_ERROR 15
#define DW_HOLD_TIME 1000

#define DW_FLAG_PRESS       B00000001
#define DW_FLAG_PRESSES     B00000010
#define DW_FLAG_CLICK       B00000100
#define DW_FLAG_HOLD        B00001000
#define DW_FLAG_RELEASE     B00010000
#define DW_FLAG_LAST_PRESS  B00100000
#define DW_FLAG_LAST_HOLD   B01000000

class DWButton
{
    public:
        DWButton(byte pin, uint16_t signal);
        DWButton(byte pin, uint16_t signal, uint16_t hold_time);
        bool isActive();
        bool isPress();
        bool isPresses();
        bool isHold();
        bool isRelease();
        bool isClick();
        void tick();

    private:
        uint32_t _timer = 0;
        byte _pin;
        uint16_t _signal;
        uint16_t _hold_time = DW_HOLD_TIME;
        uint32_t _hold_end = 0;
        void check(uint32_t cur_time);
        uint8_t flag = 0;
};

#endif
