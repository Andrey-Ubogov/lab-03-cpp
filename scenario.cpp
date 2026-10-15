#include "Scenario.hpp"

Scenario::Scenario(const std::string& name, const std::string& condition)
    : m_name(name),
      m_condition(condition),
      m_isActive(false)
{
    std::cout << "[Scenario] Создан сценарий: " << m_name << " (" << m_condition << ")" << std::endl;
}

Scenario::~Scenario() {
    std::cout << "[Scenario] Уничтожен сценарий: " << m_name << std::endl;
}

void Scenario::Activate() {
    m_isActive = true;
    std::cout << "  Сценарий '" << m_name << "' активирован." << std::endl;
}

void Scenario::Deactivate() {
    m_isActive = false;
    std::cout << "  Сценарий '" << m_name << "' деактивирован." << std::endl;
}

void Scenario::ChangeCondition(const std::string& newCondition) {
    m_condition = newCondition;
    std::cout << "  У сценария '" << m_name << "' изменено условие на: " << m_condition << std::endl;
}

std::string Scenario::GetName() const { return m_name; }
std::string Scenario::GetCondition() const { return m_condition; }
bool Scenario::GetIsActive() const { return m_isActive; }