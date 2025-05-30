#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum LogType {
    USER_INPUT,
    LOG_ERROR,
    ATTEMPTS,
    GENERATED_NUMBER
};

struct LogEntry {
    LogType type;
    string message;
    string timestamp;

    LogEntry(LogType t, const string& msg) : type(t), message(msg) {
        timestamp = getCurrentTime();
    }

    static string getCurrentTime() {
        time_t now = std::time(nullptr);
        tm localtime;
        localtime_s(&localtime, &now);

        ostringstream oss;
        oss << put_time(&localtime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};

void logMessage(const LogEntry& entry, const string& filename) {
    ofstream logFile(filename, ios_base::app);
    if (logFile.is_open()) {
        logFile << "[" << entry.timestamp << "] "
            << (entry.type == USER_INPUT ? "USER_INPUT" :
                entry.type == LOG_ERROR ? "ERROR" :
                entry.type == ATTEMPTS ? "ATTEMPTS" : "GENERATED_NUMBER")
            << ": " << entry.message << endl;
        logFile.close();
    }
    else {
        cerr << "Ошибка открытия файла лога!" << endl;
    }
}

int ugad(int n, int k) {
    cout << "Доступно попыток: " << k << endl;

    logMessage(LogEntry(GENERATED_NUMBER, to_string(n)), "log.txt");
    logMessage(LogEntry(ATTEMPTS, to_string(k)), "log.txt");

    while (k > 0) {
        int chis;
        cout << "Введите число: ";
        cin >> chis;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(); // Игнорируем некорректный ввод
            cout << "Вы ввели некорректное число! Попробуйте снова." << endl;
            logMessage(LogEntry(LOG_ERROR, "Некорректный ввод числа"), "log.txt");
            continue;
        }

        // Логируем ввод пользователя
        logMessage(LogEntry(USER_INPUT, to_string(chis)), "log.txt");

        if (chis > n) {
            cout << "Загаданное число меньше" << endl;
        }
        else if (chis < n) {
            cout << "Загаданное число больше" << endl;
        }
        else {
            cout << "Вы угадали!" << endl;
            return chis;
        }

        --k; // Уменьшаем количество попыток только после корректного ввода
    }

    cout << endl << "Вы не смогли угадать число " << n << endl;
    return 0;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");

    int k = 3; // Кол-во попыток
    int n = 4; // Загаданное число
    ugad(n, k);

    return 0;
}
