#pragma once

#include <string>
#include <iostream>

// Класс "Устройство" — часть комнаты (композиция).
class Device {
private:
    std::string m_name;
    bool m_isOn;
    bool m_isBroken;
    int m_powerConsumption; // Ватты (потребление энергии)

public:
    // Конструктор с параметрами
    Device(const std::string& name, int power);

    // Конструктор по умолчанию
    Device();

    // Деструктор
    ~Device();

    // Содержательные методы
    void TurnOn(); // Включить
    void TurnOff(); // Выключить
    void Break();   // Сломать устройство
    void Repair();  // Починить

    // Геттеры
    std::string GetName() const;
    bool GetIsOn() const;
    bool GetIsBroken() const;
    int GetPower() const;
};