#ifndef DWBUTTON_H
#define DWBUTTON_H

#include <Arduino.h>

#ifndef DW_TICK_DELAY
// Задержка для опроса кнопки
#define DW_TICK_DELAY 50
#endif
#ifndef DW_SIGNAL_ERROR
// Погрешность сигнала
#define DW_SIGNAL_ERROR 15
#endif
#ifndef DW_HOLD_TIME
// Задержка на удержание кнопкп по умолчанию.
#define DW_HOLD_TIME 1000
#endif

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
        /**
         * @param pin       Аналоговый номер пина на котором находится кнопка
         * @param signal    Сигнал с аналогового пина на который будет реагировать кнопка
         */
        DWButton(byte pin, uint16_t signal);
        /**
         * @param pin       Аналоговый номер пина на котором находится кнопка
         * @param signal    Сигнал с аналогового пина на который будет реагировать кнопка
         * @param hold_time Время задержки для удержания кнопки
         */
        DWButton(byte pin, uint16_t signal, uint16_t hold_time);
        /**
         * Возвращает true, если кнопка нажата.
         * Метод использует непосредствунное чтение данных с пина.
         */
        bool isActive();
        // Возвращает true в начале нажатия
        bool isPress();
        // Возвращает true, когда нажата/удерживается кнопка.
        bool isPresses();
        // Вернет true после истечения таймера удержания (hold_time).
        bool isHold();
        // Вернет true после отпуска кнопки.
        bool isRelease();
        // Вернет true при быстром нажатии (до истечения hold_time)
        bool isClick();
        // Опрос
        void tick();

    private:
        uint32_t _timer = 0;
        byte _pin;
        uint16_t _signal;
        uint16_t _hold_time = DW_HOLD_TIME;
        uint32_t _hold_end = 0;
        void check(uint32_t *cur_time);
        uint8_t flag = 0;
};

#endif
