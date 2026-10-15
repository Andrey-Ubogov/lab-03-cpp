#include "Room.hpp"

Room::Room(const std::string& name) : m_name(name) {
    std::cout << "[Room] Создана комната: " << m_name << std::endl;
}

Room::~Room() {
    std::cout << "[Room] Комната '" << m_name << "' уничтожается. Устройства внутри тоже будут уничтожены." << std::endl;
}

void Room::AddDevice(const Device& device) {
    m_devices.push_back(device);
    std::cout << "В комнату '" << m_name << "' добавлено устройство: " << device.GetName() << std::endl;
}

void Room::TurnOnAllDevices() {
    std::cout << "Включение всех устройств в комнате '" << m_name << "':" << std::endl;
    for (auto& dev : m_devices) {
        dev.TurnOn();
    }
}

void Room::TurnOffAllDevices() {
    std::cout << "Выключение всех устройств в комнате '" << m_name << "':" << std::endl;
    for (auto& dev : m_devices) {
        dev.TurnOff();
    }
}

void Room::SetScenario(const std::shared_ptr<Scenario>& newScenario) {
    m_scenario = newScenario; // weak_ptr создаётся из shared_ptr
    if (auto sp = m_scenario.lock()) {
        std::cout << "Комната '" << m_name << "' теперь использует сценарий: " << sp->GetName() << std::endl;
    }
    else {
        std::cout << "Комната '" << m_name << "' отвязана от сценария." << std::endl;
    }
}

void Room::RunScenario() {
    // Пытаемся получить shared_ptr из weak_ptr.
    // lock() возвращает пустой shared_ptr, если объект уже уничтожен.
    auto scenario = m_scenario.lock();

    if (!scenario) {
        std::cout << "  Ошибка: У комнаты '" << m_name << "' нет привязанного сценария (или он уничтожен)!" << std::endl;
        return;
    }

    // ПРОВЕРКА ПРАВИЛА: нельзя запустить неактивный сценарий
    if (!scenario->GetIsActive()) {
        std::cout << "  Ошибка: Сценарий '" << scenario->GetName() << "' не активирован." << std::endl;
        return;
    }

    std::cout << "Комната '" << m_name << "' выполняет сценарий '" << scenario->GetName() << "'..." << std::endl;
    TurnOnAllDevices();
}

std::string Room::GetName() const { return m_name; }
std::size_t Room::GetDeviceCount() const { return m_devices.size(); }