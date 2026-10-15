#include <iostream>
#include <memory>
#include <vector>

#include "Room.hpp"
#include "Scenario.hpp"
#include "Device.hpp"

int main() {
    // Переключаем кодовую страницу консоли на UTF-8
    system("chcp 65001 > nul");
    // Устанавливаем русскую локаль
    setlocale(LC_ALL, "Russian");

    std::cout << "========== ЛР 3. Часть 2: C++ (умные указатели) ==========\n" << std::endl;

    // ==============================================================
    // 1. unique_ptr: один владелец, уничтожается при выходе из блока
    // ==============================================================
    std::cout << "--- 1. unique_ptr ---" << std::endl;
    {
        std::unique_ptr<Device> lamp = std::make_unique<Device>("Лампа в коридоре", 15);
        lamp->TurnOn();
        std::cout << "Выходим из блока — лампа должна уничтожиться автоматически...\n" << std::endl;
    } // Здесь сработает деструктор Device, delete не нужен

    // ==============================================================
    // 2. unique_ptr: передача владения через std::move
    // ==============================================================
    std::cout << "--- 2. Передача владения через std::move ---" << std::endl;
    std::unique_ptr<Device> ownership = std::make_unique<Device>("Умная розетка", 5);
    std::cout << "Указатель до move: " << (ownership ? "не пуст" : "пуст") << std::endl;

    std::unique_ptr<Device> moved = std::move(ownership);

    std::cout << "Указатель ownership после move: " << (ownership ? "не пуст" : "пуст") << std::endl;
    std::cout << "Указатель moved после move:     " << (moved ? "не пуст" : "пуст") << std::endl;
    std::cout << std::endl;

    // ==============================================================
    // 3. shared_ptr: несколько владельцев, счётчик use_count()
    // ==============================================================
    std::cout << "--- 3. shared_ptr и use_count() ---" << std::endl;
    std::shared_ptr<Scenario> morningScenario = std::make_shared<Scenario>("Утренний свет", "07:00");
    morningScenario->Activate();

    std::cout << "use_count() после создания: " << morningScenario.use_count() << std::endl;

    {
        std::shared_ptr<Scenario> secondOwner = morningScenario;
        std::cout << "use_count() после копирования: " << morningScenario.use_count() << std::endl;
    } // secondOwner исчез

    std::cout << "use_count() после выхода из блока: " << morningScenario.use_count() << std::endl;
    std::cout << std::endl;

    // ==============================================================
    // 4. weak_ptr: наблюдатель за shared_ptr
    // ==============================================================
    std::cout << "--- 4. weak_ptr ---" << std::endl;

    std::weak_ptr<Scenario> weakObserver = morningScenario;

    if (auto locked = weakObserver.lock()) {
        std::cout << "Сценарий жив: " << locked->GetName() << std::endl;
    }
    else {
        std::cout << "Сценарий уже уничтожен." << std::endl;
    }

    // Сбрасываем последнего владельца — сценарий уничтожается
    morningScenario.reset();
    std::cout << "После morningScenario.reset():" << std::endl;

    if (auto locked = weakObserver.lock()) {
        std::cout << "Сценарий всё ещё жив: " << locked->GetName() << std::endl;
    }
    else {
        std::cout << "Сценарий уничтожен (lock() вернул пустой указатель)." << std::endl;
    }
    std::cout << std::endl;

    // ==============================================================
    // 5. Композиция и агрегация вместе
    // ==============================================================
    std::cout << "--- 5. Композиция и агрегация ---" << std::endl;

    std::shared_ptr<Scenario> eveningScenario = std::make_shared<Scenario>("Вечерний свет", "19:00");
    eveningScenario->Activate();

    {
        Room livingRoom("Гостиная");
        livingRoom.AddDevice(Device("Умная лампа", 10));
        livingRoom.AddDevice(Device("Телевизор", 150));
        livingRoom.SetScenario(eveningScenario);

        std::cout << "\n--- Запуск сценария ---" << std::endl;
        livingRoom.RunScenario();

        std::cout << "\n--- Проверка правила: поломка устройства ---" << std::endl;
        Device brokenLamp("Сломанная лампа", 5);
        brokenLamp.Break();
        brokenLamp.TurnOn();

        std::cout << "\n--- Выход из блока. Комната уничтожится. ---" << std::endl;
    } // Room уничтожается, Device внутри — тоже (композиция)

    std::cout << "\n--- После уничтожения комнаты ---" << std::endl;
    std::cout << "Сценарий всё ещё существует, т.к. владелец — eveningScenario." << std::endl;
    std::cout << "use_count() = " << eveningScenario.use_count() << std::endl;
    std::cout << std::endl;

    // ==============================================================
    // 6. Массив объектов через unique_ptr<Device[]>
    // ==============================================================
    std::cout << "--- 6. Массив объектов (unique_ptr<Device[]>) ---" << std::endl;
    {
        // make_unique<Device[]>(3) создаёт массив из 3 устройств.
        // Нужен конструктор по умолчанию у Device.
        std::unique_ptr<Device[]> devices = std::make_unique<Device[]>(3);

        for (int i = 0; i < 3; ++i) {
            std::cout << "  Элемент массива " << i << ": " << devices[i].GetName() << std::endl;
        }
        // delete[] писать не нужно — unique_ptr сделает это сам
    }
    std::cout << std::endl;

    // ==============================================================
    // 7. Массив unique_ptr (аналог Device* arr[2] из ЛР 2)
    // ==============================================================
    std::cout << "--- 7. Массив unique_ptr ---" << std::endl;
    {
        std::unique_ptr<Device> shelf[2];
        shelf[0] = std::make_unique<Device>("Лампа 1", 10);
        shelf[1] = std::make_unique<Device>("Лампа 2", 12);

        shelf[0]->TurnOn();
        shelf[1]->TurnOn();

        // Владение передаётся через std::move
        std::unique_ptr<Device> taken = std::move(shelf[0]);
        std::cout << "shelf[0] после move: " << (shelf[0] ? "не пуст" : "пуст") << std::endl;
        std::cout << "taken: " << taken->GetName() << std::endl;
        // Оба указателя уничтожатся автоматически
    }

    std::cout << "\n========== КОНЕЦ ==========" << std::endl;
    return 0;
}