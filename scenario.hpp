#pragma once

#include <string>
#include <iostream>

// Класс "Сценарий" — используется комнатой (агрегация).
class Scenario {
private:
    std::string m_name;
    std::string m_condition;
    bool m_isActive;

public:
    // Конструктор с параметрами
    Scenario(const std::string& name, const std::string& condition);

    // Деструктор
    ~Scenario();

    // Содержательные методы
    void Activate(); // Активировать сценарий
    void Deactivate(); // Деактивировать сценарий
    void ChangeCondition(const std::string& newCondition); // Изменить сценарий

    // Геттеры
    std::string GetName() const;
    std::string GetCondition() const;
    bool GetIsActive() const;
};