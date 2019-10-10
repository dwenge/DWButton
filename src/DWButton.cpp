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

bool DWButton::isPresses() {
    return _is_presses;
}

bool DWButton::isPress() {
    return _is_press;
}

bool DWButton::isHold() {
    return _is_hold;
}

bool DWButton::isRelease() {
    return _is_release;
}

bool DWButton::isClick() {
    return _is_click;
}

void DWButton::tick() {
    uint32_t cur_t = millis();
    _is_press = false;
    _is_release = false;
    _is_hold = false;
    _is_click = false;
    if (_timer < cur_t) {
        check(cur_t);
        _timer = cur_t + DW_TICK_DELAY;
    }
}
void DWButton::check(uint32_t cur_time) {
    uint16_t sig = analogRead(_pin);
    if ((sig > _signal - DW_SIGNAL_ERROR) && (sig < _signal + DW_SIGNAL_ERROR)) {
        _is_presses = true;
        if (!_last_press) {
            _is_press = true;
            _last_press = true;
            _last_hold = false;
        }
        if (_hold_end > 0) {
            if (!_last_hold && _hold_end < cur_time) {
                _is_hold = true;
                _last_hold = true;
                _hold_end = 0;
            }
        } else if (!_last_hold) {
            _hold_end = cur_time + _hold_time;
        }
    } else {
        _is_presses = false;
        if (_last_press) {
            _is_release = true;
            _last_press = false;

            if (_hold_end > 0) {
                _is_click = true;
                _hold_end = 0;
            }
        }
    }
}
