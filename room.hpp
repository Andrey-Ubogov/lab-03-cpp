#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Device.hpp"
#include "Scenario.hpp"

class Room {
private:
    std::string m_name;
    std::vector<Device> m_devices;              // ÊÎÌÏÎÇÈÖÈß: ïî çíà÷åíèş
    std::weak_ptr<Scenario> m_scenario;         // ÀÃĞÅÃÀÖÈß: weak_ptr

public:
    Room(const std::string& name);
    ~Room();

    void AddDevice(const Device& device);
    void TurnOnAllDevices();
    void TurnOffAllDevices();

    void SetScenario(const std::shared_ptr<Scenario>& newScenario);
    void RunScenario();

    std::string GetName() const;
    std::size_t GetDeviceCount() const;
};