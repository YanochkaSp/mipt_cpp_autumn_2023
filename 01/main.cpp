#include <iostream>
#include <string>
#include <algorithm>

std::string Replacer (std::string new_str)
{
    std::replace(new_str.begin(), new_str.end(), 'b', '1');
    std::replace(new_str.begin(), new_str.end(), 'f', '1');
    std::replace(new_str.begin(), new_str.end(), 'p', '1');
    std::replace(new_str.begin(), new_str.end(), 'v', '1');

    std::replace(new_str.begin(), new_str.end(), 'c', '2');
    std::replace(new_str.begin(), new_str.end(), 'g', '2');
    std::replace(new_str.begin(), new_str.end(), 'j', '2');
    std::replace(new_str.begin(), new_str.end(), 'k', '2');
    std::replace(new_str.begin(), new_str.end(), 'q', '2');
    std::replace(new_str.begin(), new_str.end(), 's', '2');
    std::replace(new_str.begin(), new_str.end(), 'x', '2');
    std::replace(new_str.begin(), new_str.end(), 'z', '2');

    std::replace(new_str.begin(), new_str.end(), 'd', '3');
    std::replace(new_str.begin(), new_str.end(), 't', '3');

    std::replace(new_str.begin(), new_str.end(), 'l', '4');

    std::replace(new_str.begin(), new_str.end(), 'm', '5');
    std::replace(new_str.begin(), new_str.end(), 'n', '5');

    std::replace(new_str.begin(), new_str.end(), 'r', '6');

    return new_str;
}

std::string StrToCode (const std::string& str) // функция, возвращающая строку
{
    std::string result;

    const char first_letter = toupper(str[0]); // запоминаем первую букву

    // удаляем все вхождения символов h и w (за исключением первой буквы)
    std::string new_str;
    new_str += first_letter;
    bool isNeedToSkip = false;
    for (int i = 1; i < str.length(); i++)
    {
        char cur = tolower(str[i]);
        if (cur == 'h' || cur == 'w')
        {
            if (isNeedToSkip == true)
            {
                isNeedToSkip = false;
            }
            else
            {
                continue;
            }
        }
        new_str += cur;
        if (cur == 'a' || cur == 'e' || cur == 'i' || cur == 'o' \
                       || cur == 'u' || cur == 'y')
        {
            isNeedToSkip = true;
        }
    }

    // заменяем согласные на цифры
    std::replace(new_str.begin(), new_str.end(), 'b', '1');
    std::replace(new_str.begin(), new_str.end(), 'f', '1');
    std::replace(new_str.begin(), new_str.end(), 'p', '1');
    std::replace(new_str.begin(), new_str.end(), 'v', '1');

    std::replace(new_str.begin(), new_str.end(), 'c', '2');
    std::replace(new_str.begin(), new_str.end(), 'g', '2');
    std::replace(new_str.begin(), new_str.end(), 'j', '2');
    std::replace(new_str.begin(), new_str.end(), 'k', '2');
    std::replace(new_str.begin(), new_str.end(), 'q', '2');
    std::replace(new_str.begin(), new_str.end(), 's', '2');
    std::replace(new_str.begin(), new_str.end(), 'x', '2');
    std::replace(new_str.begin(), new_str.end(), 'z', '2');

    std::replace(new_str.begin(), new_str.end(), 'd', '3');
    std::replace(new_str.begin(), new_str.end(), 't', '3');

    std::replace(new_str.begin(), new_str.end(), 'l', '4');

    std::replace(new_str.begin(), new_str.end(), 'm', '5');
    std::replace(new_str.begin(), new_str.end(), 'n', '5');

    std::replace(new_str.begin(), new_str.end(), 'r', '6');

    // удаляем последовательность одинаковых цифр
    std::string temp_str;
    temp_str += new_str[0]; // чтобы созранить первую букву, которую нельзя изменять
    for (int i = 1; i < new_str.length(); i++)
    {
        if (temp_str[temp_str.length() - 1] != new_str[i])
        {
            temp_str += new_str[i];
        }
    }
    new_str = temp_str;

    // удаляем гласные (за исключением первой буквы)
    isNeedToSkip = false;
    temp_str = new_str[0];
    for (int i = 1; i < new_str.length(); i++)
    {
        if (isNeedToSkip == true)
        {
            isNeedToSkip = false;
            continue;
        }
        if (new_str[i] == 'a' || new_str[i] == 'e' || new_str[i] == 'i' 
         || new_str[i] == 'o' || new_str[i] == 'u' || new_str[i] == 'y')
        {
            isNeedToSkip = true;
            continue;
        }
        temp_str += new_str[i];
    }
    new_str = temp_str;
    new_str[0] = first_letter;

    // Шаг 7: обрезаем до первых четырёх символов и заполняем недостающие символы 0
    if (new_str.length() > 4)
    {
        new_str.substr(0, 4);
    }
    else
    {
        new_str.resize(4, '0');
    }

    return new_str;
}

void isSimilar (std::string& str1, std::string& str2)
{
    std::string code1 = StrToCode(str1);
    std::string code2 = StrToCode(str2);

    if (code1 == code2)
    {
        printf("The strings are phonetically similar");
    }
    else
    {
        printf("The strings are not phonetically similar");
    }
}

int main (int argc, char* argv[])
{
    std::string string1 = argv[0];
    std::string string2 = argv[1];
    // std::getline(std::cin, string1);
    // std::string string2 = getline(std::cin, string2);
    isSimilar(string1, string2);
}