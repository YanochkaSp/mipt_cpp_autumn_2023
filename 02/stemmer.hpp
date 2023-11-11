#ifndef STEMMER_HPP
#define STEMMER_HPP

#include <iostream>


bool IsAlpha (const std::string& str); // Проверка, что строка состоит только из символов латинского алфавита.

std::string ToUpper (const std::string& str); // Приводит строку в верхний регистр.

std::string Stem (const std::string& str); // Удаляем окончания и суффиксы.

std::string Normalize (const std::string& str); 

#endif