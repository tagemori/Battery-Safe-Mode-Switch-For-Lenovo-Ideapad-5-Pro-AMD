/**
 * @file safeModeSwitch.cpp
 * @brief Утыліта для кіравання рэжымам захавання акумулятара (Conservation Mode) на Lenovo IdeaPad
 * 
 * Гэтая праграма дазваляе ўключаць і выключаць рэжым захавання акумулятара,
 * які абмяжоўвае максімальны зарад да 60% для падаўжэння тэрміну службы батарэі.
 * 
 * @author Generated with refactoring
 * @license MIT
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

// Канстанты шляхоў
namespace Paths {
    constexpr const char* ACPI_CONSERVATION_MODE = "/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/conservation_mode";
    constexpr const char* ACPI_VENDOR_PATH = "/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/modalias";
    constexpr const char* PROGRAM_NAME = "safeModeSwitch";
}

// Канстанты паведамленняў
namespace Messages {
    constexpr const char* USAGE = R"(
Ужыванне:
  --switch-status  Пераключэнне рэжыму захавання акумулятара
  --get-status     Атрыманне бягучага статусу рэжыму

Прыклады:
  safeModeSwitch --get-status
  safeModeSwitch --switch-status
)";
    
    constexpr const char* STATUS_ENABLED = "✅ Рэжым захавання акумулятара УКЛЮЧАНЫ\n   Максімальны зарад абмежаваны да 60%";
    constexpr const char* STATUS_DISABLED = "🔋 Рэжым захавання акумулятара АДКЛЮЧАНЫ\n   Максімальны зарад дасягае 100%";
    constexpr const char* ERROR_FILE_READ = "❌ Памылка чытання файла ACPI. Праверце правы доступу.";
    constexpr const char* ERROR_FILE_WRITE = "❌ Памылка запісу ў файл ACPI. Патрабуецца доступ root.";
    constexpr const char* ERROR_PARSE_STATUS = "❌ Памылка разбору статусу з файла ACPI.";
    constexpr const char* ERROR_SECURITY_CHECK = "⚠️ Папярэджанне: не пройдзена праверка бяспекі ACPI прылады.";
    constexpr const char* INFO_ELEVATING_PRIVS = "🔐 Запыт правоў суперкарыстальніка...";
}

/**
 * @brief Правярае, ці існуе файл і ці з'яўляецца ён рэгулярным файлам
 * @param filepath Шлях да файла
 * @return true калі файл існуе і з'яўляецца рэгулярным
 */
bool fileExists(const std::string& filepath) {
    struct stat buffer;
    return (stat(filepath.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

/**
 * @brief Правярае цэласнасць ACPI прылады (абарона ад падмены)
 * @return true калі прылада праверана і з'яўляецца сапраўднай Lenovo IdeaPad
 */
bool verifyAcpiDevice() {
    std::ifstream modaliasFile(Paths::ACPI_VENDOR_PATH);
    
    if (!modaliasFile.is_open()) {
        return false;
    }
    
    std::string modaliasContent;
    std::getline(modaliasFile, modaliasContent);
    modaliasFile.close();
    
    // Правяраем, што гэта сапраўды прылада Lenovo (LNV)
    // Формат: acpi:LNV0001:VPC2004:
    if (modaliasContent.find("LNV") != std::string::npos || 
        modaliasContent.find("VPC2004") != std::string::npos) {
        return true;
    }
    
    return false;
}

/**
 * @brief Атрымлівае бягучы статус рэжыму захавання акумулятара
 * @return true калі рэжым захавання ўключаны (60%), false калі выключаны (100%)
 */
bool getBatteryStatus() {
    if (!verifyAcpiDevice()) {
        std::cerr << Messages::ERROR_SECURITY_CHECK << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    std::ifstream acpiFile(Paths::ACPI_CONSERVATION_MODE);
    
    if (!acpiFile.is_open()) {
        std::cerr << Messages::ERROR_FILE_READ << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    char statusChar;
    acpiFile.get(statusChar);
    acpiFile.close();
    
    // Правяраем, што значэнне карэктнае ('0' або '1')
    if (statusChar == '0') {
        return false;  // Рэжым выключаны
    } else if (statusChar == '1') {
        return true;   // Рэжым уключаны
    } else {
        std::cerr << Messages::ERROR_PARSE_STATUS << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Змяняе статус рэжыму захавання акумулятара
 * @param newStatus Новы статус (true = уключыць, false = выключыць)
 */
void setBatteryStatus(bool newStatus) {
    if (!verifyAcpiDevice()) {
        std::cerr << Messages::ERROR_SECURITY_CHECK << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    std::ofstream acpiFile(Paths::ACPI_CONSERVATION_MODE);
    
    if (!acpiFile.is_open()) {
        std::cerr << Messages::ERROR_FILE_WRITE << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    acpiFile << (newStatus ? '1' : '0') << std::endl;
    
    if (acpiFile.fail()) {
        std::cerr << Messages::ERROR_FILE_WRITE << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    acpiFile.close();
}

/**
 * @brief Правярае наяўнасць правоў запісу ў файл ACPI
 * @return true калі ёсць правы запісу
 */
bool hasWriteAccess() {
    std::ofstream testFile(Paths::ACPI_CONSERVATION_MODE, std::ios::app);
    bool hasAccess = testFile.is_open();
    if (hasAccess) {
        testFile.close();
    }
    return hasAccess;
}

/**
 * @brief Выводзіць паведамленне карыстальніку
 * @param notificationText Тэкст паведамлення
 */
void showNotification(const std::string& notificationText) {
    if (hasWriteAccess()) {
        // Калі ёсць правы root, выводзім у кансоль
        std::cout << notificationText << std::endl;
    } else {
        // Інакш спрабуем адправіць desktop-паведамленне
        std::string command = "notify-send -i battery -a '" + std::string(Paths::PROGRAM_NAME) + "' '" + notificationText + "'";
        int result = std::system(command.c_str());
        
        // Калі notify-send не атрымаўся, выводзім у кансоль
        if (result != 0) {
            std::cout << notificationText << std::endl;
        }
    }
}

/**
 * @brief Запускае праграму з правамі суперкарыстальніка праз pkexec
 * @param programName Шлях да праграмы
 * @param argument Аргумент каманднага радка
 */
void elevatePrivileges(const std::string& programName, const std::string& argument) {
    std::cout << Messages::INFO_ELEVATING_PRIVS << std::endl;
    
    // Выкарыстоўваем pkexec замест kdesu для большай універсальнасці
    // pkexec працуе з GNOME, KDE, XFCE і іншымі асяроддзямі
    std::string command = "pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY '" + 
                          programName + "' " + argument;
    
    int result = std::system(command.c_str());
    
    if (result != 0) {
        std::cerr << "⚠️ Не атрымалася атрымаць правы суперкарыстальніка." << std::endl;
        std::cerr << "   Запусціце праграму з sudo: sudo " << programName << " " << argument << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Галоўная функцыя праграмы
 * @param argc Колькасць аргументаў каманднага радка
 * @param argv Масіў аргументаў каманднага радка
 * @return Код завяршэння праграмы
 */
int main(int argc, char *argv[]) {
    // Праверка колькасці аргументаў
    if (argc < 2) {
        std::cout << Messages::USAGE << std::endl;
        return EXIT_SUCCESS;
    }
    
    std::string command = argv[1];
    std::string programPath = argv[0];
    
    // Апрацоўка каманд
    if (command == "--get-status") {
        bool status = getBatteryStatus();
        
        if (status) {
            showNotification(Messages::STATUS_ENABLED);
        } else {
            showNotification(Messages::STATUS_DISABLED);
        }
        
    } else if (command == "--switch-status") {
        bool hasAccess = hasWriteAccess();
        
        if (!hasAccess) {
            // Патрабуецца падвышэнне правоў
            elevatePrivileges(programPath, "--switch-status");
            // Пасля pkexec праграма перазапускаецца з правамі root
            // і выконвае гэты ж блок кода, але ўжо з доступам
            return EXIT_SUCCESS;
        }
        
        // Чытаем бягучы статус і пераключаем
        bool currentStatus = getBatteryStatus();
        setBatteryStatus(!currentStatus);
        
        // Паказваем новы статус
        bool newStatus = getBatteryStatus();
        
        if (newStatus) {
            showNotification(Messages::STATUS_ENABLED);
        } else {
            showNotification(Messages::STATUS_DISABLED);
        }
        
    } else {
        std::cerr << "❌ Невядомая каманда: " << command << std::endl;
        std::cout << Messages::USAGE << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
