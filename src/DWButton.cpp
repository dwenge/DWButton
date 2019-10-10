#include "DWButton.h"
#include <Arduino.h>

DWButton::DWButton(uint8_t pin, uint16_t signal) {
    pinMode(pin, INPUT_PULLUP);
    _pin = pin;
    _signal = signal;
}

DWButton::DWButton(uint8_t pin, uint16_t signal, uint16_t hold_time) {
    pinMode(pin, INPUT_PULLUP);
    _pin = pin;
    _signal = signal;
    _hold_time = hold_time;
}

bool DWButton::isActive() {
    uint16_t sig = analogRead(_pin);
    return (sig > _signal - DW_SIGNAL_ERROR) && (sig < _signal + DW_SIGNAL_ERROR);
}

bool DWButton::isPresses() {
    return flag & DW_FLAG_PRESSES;
}

bool DWButton::isPress() {
    return flag & DW_FLAG_PRESS;
}

bool DWButton::isHold() {
    return flag & DW_FLAG_HOLD;
}

bool DWButton::isRelease() {
    return flag & DW_FLAG_RELEASE;
}

bool DWButton::isClick() {
    return flag & DW_FLAG_CLICK;
}

void DWButton::tick() {
    uint32_t cur_t = millis();
    flag &= ~(DW_FLAG_PRESS | DW_FLAG_RELEASE | DW_FLAG_HOLD | DW_FLAG_CLICK);
    if (_timer < cur_t) {
        check(cur_t);
        _timer = cur_t + DW_TICK_DELAY;
    }
}
void DWButton::check(uint32_t cur_time) {
    uint16_t sig = analogRead(_pin);
    if ((sig > _signal - DW_SIGNAL_ERROR) && (sig < _signal + DW_SIGNAL_ERROR)) {
        flag |= DW_FLAG_PRESSES;
        if ((flag & DW_FLAG_LAST_PRESS)==0) {
            flag |= DW_FLAG_PRESS | DW_FLAG_LAST_PRESS;
            flag &= ~DW_FLAG_LAST_HOLD;
        }
        if (_hold_end > 0) {
            if ((flag & DW_FLAG_LAST_HOLD)==0 && _hold_end < cur_time) {
                _hold_end = 0;
                flag |= DW_FLAG_HOLD | DW_FLAG_LAST_HOLD;
            }
        } else if ((flag & DW_FLAG_LAST_HOLD)==0) {
            _hold_end = cur_time + _hold_time;
        }
    } else {
        flag &= ~DW_FLAG_PRESSES;
        if ((flag & DW_FLAG_LAST_PRESS)>0) {
            flag |= DW_FLAG_RELEASE;
            flag &= ~DW_FLAG_LAST_PRESS;

            if (_hold_end > 0) {
                _hold_end = 0;
                flag |= DW_FLAG_CLICK;
            }
        }
    }
}
