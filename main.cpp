#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

int size;
std::vector <int> random_numbers;
std::ofstream LogFile;

void logger_init(){
    std::string LogFileName;
    // LogFileName += "\\File\\";

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];                                                     // строка, в которой будет храниться текущее время
    time ( &rawtime );                                               // текущая дата в секундах
    timeinfo = localtime ( &rawtime );                               // текущее локальное время, представленное в структуре
    strftime (buffer,80,"(%Y-%m-%d)-(%H-%M-%S)-",timeinfo);     // форматируем строку времени

    LogFileName += buffer;
    LogFileName += "errors-log.txt";

    LogFile.open(LogFileName);
    if(!LogFile.is_open()) {
        std::cout << "Критическая ошибка! Невозможно создать файл журнала " << LogFileName;
        while(true);
    }
}

void logger(std::string Message) {

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


void fillInitialSequence(int vector_size) {
    for (int i = 1; i <= vector_size; ++i) {
        random_numbers.push_back(i);
    }
}

void userGreeting(){
    std::cout << "Вас приветствует программа для проведения жеребьёвки методом генерации случайных чисел." << std::endl;
    std::cout << " Введите количество участников жеребьёвки: ";
}

int main() {

    srand(time(nullptr));



    fillInitialSequence(size);


    return 0;
}
