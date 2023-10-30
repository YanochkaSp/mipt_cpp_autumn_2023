#ifndef PHONETICALG_H
#define PHONETICALG_H

#include <iostream>
#include <string>
#include <algorithm>

std::string Replacer (std::string& new_str);

std::string StrToCode (const std::string& str); // функция, возвращающая строку

void isSimilar (std::string& str1, std::string& str2);

std::string VowelsDeleter (std::string& new_str, std::string& temp_str); // удаление гласных

std::string StrCutter (std::string& new_str); // обрезаем до первых четырёх символов и заполняем недостающие символы 0

std::string H_and_W_Deleter (std::string& new_str, const std::string& str, const char FIRST_LETTER); // удаляем все вхождения символов h и w (за исключением первой буквы)

std::string EqualsDeleter (std::string& temp_str, std::string& new_str); // // удаляем последовательность одинаковых цифр

#endif // PHONETICALG_H