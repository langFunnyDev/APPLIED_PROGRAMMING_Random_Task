#include <Windows.h>

#include <iostream>
#include <fstream>

#include <ctime>
#include <string>
#include <vector>

int size;
std::ofstream LogFile;

void logger_init(){
    std::string LogFileName;

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];                                                                    // строка, в которой будет храниться текущее время
    time ( &rawtime );                                                              // текущая дата в секундах
    timeinfo = localtime ( &rawtime );                                              // текущее локальное время, представленное в структуре
    strftime (buffer,80,"(%Y-%m-%d)-(%H-%M-%S)-",timeinfo);    // форматируем строку времени

    LogFileName += buffer;
    LogFileName += "errors-log.txt";

    LogFile.open(LogFileName);
    if(!LogFile.is_open()) {
        std::cout << "Критическая ошибка! Невозможно создать файл журнала " << LogFileName;
        while(true);
    }
}

void logger(const std::string& Message) {

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];                                                     // строка, в которой будет храниться текущее время
    time ( &rawtime );                                               // текущая дата в секундах
    timeinfo = localtime ( &rawtime );                               // текущее локальное время, представленное в структуре
    strftime (buffer,80,"(%H-%M-%S)-",timeinfo);     // форматируем строку времени

    std::string LogMessage;
    LogMessage += buffer;
    LogMessage += Message;

    LogFile << LogMessage << std::endl;
}

/*
 *  Функция error_handler возвращает истину в случае соответствия заданному диапазоне и ложь в обратном
 */

bool error_handler(int number, int minimum, int maximum) {
    if (number >= minimum && number <= maximum) {
        std::string Message;
        Message += "Проверка ввода пройдена успешно.";
        logger(Message);
        return true;
    } else {
        std::string Message;
        Message += "Пользователь допустил ошибку ввода, пользователь ввел - ";
        Message += std::to_string(number);
        Message += " при допустимом диапазоне от ";
        Message += std::to_string(minimum);
        Message += " до ";
        Message += std::to_string(maximum);
        logger(Message);
        std::cout << std::endl << "Вы ввели число не соответствующее заданным условиям. Попробуйте ещё раз!" << std::endl << std::endl;
        return false;
    }
}


void userGreeting(){
    std::cout << "Вас приветствует программа для проведения жеребьёвки методом генерации случайных чисел." << std::endl;
    do {
        std::cout << " Введите количество участников жеребьёвки: ";
        std::cin >> size;
    } while (!error_handler(size, 1, 2147483647));

}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    logger_init();

    srand(time(NULL));

    userGreeting();                                 // Пользовательское приветствие
    std::vector <int> random_numbers (size);  // Инициализация вектора

    std::string LogMessage = "Пользователь запросил последовательность длиной в ";
    LogMessage += std::to_string(size);
    LogMessage += " элементов.";
    logger(LogMessage);

    for (int i = 0; i < size; ++i) {                 // Заполнение вектора значениями
        random_numbers[i] = i + 1;
    }

    for (int i = 0; i < size; ++i) {                  // Перемешивание вектора в случайном порядке
        int ind1 = rand() % size;
        int ind2 = rand() % size;
        int temp = random_numbers[ind1];
        random_numbers[ind1] = random_numbers[ind2];
        random_numbers[ind2] = temp;
    }

    LogMessage = "Итоговая последовательность - ";
    for (int i = 0; i < size; ++i) {                  // Вывод вектора
        std::cout << random_numbers[i] << " ";
        LogMessage += std::to_string(random_numbers[i]);
        LogMessage += " ";
    }
    logger(LogMessage);

    std::cout << std::endl;
    system("pause");
    return 0;
}
