// Загалоўкі
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

// Аб'яўленне функцый
bool getAccessStatus();
bool getBatteryStatus();
void setBatteryStatus(bool newStatus);
void accessEnhancement(std::string programName);
void notificationOutput(std::string notificationText);

// Шлях да ACPI файла
const std::string filePath = "/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/conservation_mode";

// Галоўная функцыя
int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "Справка\n\n  --switch-status - пераключэнне бяспечнага рэжыму\n  --get-status - атрыманне статусу бяспечнага рэжыму" << std::endl;
    } else if (argc == 2) {
        if (std::string(argv[1]) == "--get-status") {
            if (getBatteryStatus()) {
                notificationOutput("Бяспечны рэжым акумулятара уключаны: максімальны зарад 60%");
            } else {
                notificationOutput("Бяспечны рэжым акумулятара адключаны: максімальны зарад 100%");
            }
        } else if (std::string(argv[1]) == "--switch-status") {
            if (getAccessStatus()) {
                if (getBatteryStatus()) {
                    setBatteryStatus(false);
                } else {
                    setBatteryStatus(true);
                }
            } else {
                accessEnhancement(std::string(argv[0]));
                if (getBatteryStatus()) {
                    notificationOutput("Бяспечны рэжым акумулятара уключаны: максімальны зарад 60%");
                } else {
                    notificationOutput("Бяспечны рэжым акумулятара адключаны: максімальны зарад 100%");
                }
            }
        } else {
            std::cout << "Невядомы параметр" << std::endl;
        }
    } else {
        std::cout << "Памылка разбору аргументаў" << std::endl;
    }

    return 0;
}

// Атрымынне інфарамацыі аб бягучым статусе бяспечнага рэжыму акумулятара
bool getBatteryStatus() {
    std::ifstream acpiFile(filePath);

    bool batteryStatus = false;
    char acpiFileContent[1];

    if (acpiFile.is_open()) {
        acpiFile.read(acpiFileContent, 1);
        acpiFile.close();

        if (int(acpiFileContent[0] - 48) == 1 || int(acpiFileContent[0] - 48) == 0) {
            batteryStatus = bool(acpiFileContent[0] - 48);
        } else {
            notificationOutput("Адбылася памылка разбору статусу");
        }
    } else {
        notificationOutput("Адбылася памылка атрымання статусу");
        std::exit(0);
    }

    return batteryStatus;
}

// Змяненне статуса бяспечнага рэжыму акумулятара
void setBatteryStatus(bool newStatus) {
    std::ofstream acpiFile(filePath);

    if (acpiFile.is_open()) {
        acpiFile << char(newStatus + 48) << std::endl;
    } else {
        notificationOutput("Памылка адкрыцця ACPI файла");
        std::exit(0);
    }

    acpiFile.close();
}

// Адпраўка паведамлення
void notificationOutput(std::string notificationText) {
    if (!getAccessStatus()) {
        std::system(("notify-send -i battery -a 'Упраўленне бяспечным рэжымам акумулятара' '" + notificationText + "'").c_str());
    } else {
        std::cout << notificationText << std::endl;
    }
}

// Праверка доступу да файла ACPI
bool getAccessStatus() {
    std::ofstream acpiFile(filePath);

    if (acpiFile.is_open()) {
        acpiFile.close();
        return true;
    } else {
        return false;
    }
}

// Павышэнне праў доступу да запісу ў файл ACPI
void accessEnhancement(std::string programName) {
    std::system(("kdesu -i battery -c '" + programName + " --switch-status'").c_str());
}
