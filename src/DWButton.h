#ifndef DWBUTTON_H
#define DWBUTTON_H

#include <Arduino.h>

#define DW_TICK_DELAY 50
#define DW_SIGNAL_ERROR 15
#define DW_HOLD_TIME 1000

class DWButton
{
    public:
        DWButton(byte pin, uint16_t signal);
        #ifndef DWB_ONLY_CLICK
        DWButton(byte pin, uint16_t signal, uint16_t hold_time);
        bool isPress();
        bool isPresses();
        bool isHold();
        bool isRelease();
        #endif

        bool isClick();
        void tick();

    private:
        uint32_t _timer = 0;
        byte _pin;
        uint16_t _signal;
        #ifndef DWB_ONLY_CLICK
        uint16_t _hold_time = DW_HOLD_TIME;
        bool _is_hold = false;
        bool _last_hold = false;
        uint32_t _hold_end = 0;
        bool _is_presses = false;
        bool _is_press = false;
        bool _is_release = false;
        void check(uint32_t cur_time);
        bool _last_press = false;
        #endif
        bool _is_click = false;
        #ifdef DWB_ONLY_CLICK
        void check();
        #endif
};

#endif