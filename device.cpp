#include "Device.hpp"

Device::Device(const std::string& name, int power)
    : m_name(name),
      m_isOn(false), 
      m_isBroken(false),
      m_powerConsumption(power) 
{
    std::cout << "[Device] Создано устройство: " << m_name << std::endl;
}

Device::Device()
    : m_name("Безымянное"),
      m_isOn(false),
      m_isBroken(false),
      m_powerConsumption(0) 
{
    std::cout << "[Device] Создано устройство по умолчанию." << std::endl;
}

Device::~Device() {
    std::cout << "[Device] Уничтожено устройство: " << m_name << std::endl;
}

void Device::TurnOn() {
    // ПРОВЕРКА ПРАВИЛА: Нельзя включить сломанное устройство
    if (m_isBroken) {
        std::cout << "  Ошибка: Устройство '" << m_name << "' сломано! Нельзя включить." << std::endl;
        return;
    }
    m_isOn = true;
    std::cout << "  Устройство '" << m_name << "' включено." << std::endl;
}

void Device::TurnOff() {
    m_isOn = false;
    std::cout << "  Устройство '" << m_name << "' выключено." << std::endl;
}

void Device::Break() {
    m_isBroken = true;
    m_isOn = false;
    std::cout << "  Устройство '" << m_name << "' сломалось!" << std::endl;
}

void Device::Repair() {
    m_isBroken = false;
    std::cout << "  Устройство '" << m_name << "' отремонтировано." << std::endl;
}

std::string Device::GetName() const { return m_name; }
bool Device::GetIsOn() const { return m_isOn; }
bool Device::GetIsBroken() const { return m_isBroken; }
int Device::GetPower() const { return m_powerConsumption; }