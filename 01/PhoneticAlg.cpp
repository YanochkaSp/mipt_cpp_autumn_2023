#include "PhoneticAlg.h"

void ReplaceChars (std::string& new_str, char from, char to)
{
    std::replace(new_str.begin(), new_str.end(), from, to);
}

std::string Replacer (std::string& new_str)
{
    ReplaceChars(new_str, 'b', '1');
    ReplaceChars(new_str, 'f', '1');
    ReplaceChars(new_str, 'p', '1');
    ReplaceChars(new_str, 'v', '1');

    ReplaceChars(new_str, 'c', '2');
    ReplaceChars(new_str, 'g', '2');
    ReplaceChars(new_str, 'j', '2');
    ReplaceChars(new_str, 'k', '2');
    ReplaceChars(new_str, 'q', '2');
    ReplaceChars(new_str, 's', '2');
    ReplaceChars(new_str, 'x', '2');
    ReplaceChars(new_str, 'z', '2');

    ReplaceChars(new_str, 'd', '3');
    ReplaceChars(new_str, 't', '3');

    ReplaceChars(new_str, 'l', '4');

    ReplaceChars(new_str, 'm', '5');
    ReplaceChars(new_str, 'n', '5');

    ReplaceChars(new_str, 'r', '6');

    return new_str;
}

std::string VowelsDeleter (std::string& new_str, std::string& temp_str) // удаление гласных
{
    temp_str = new_str[0];
    int i = 1;
    while (i < new_str.length())
    {
        if (new_str[i] == 'a' || new_str[i] == 'e' || new_str[i] == 'i'
         || new_str[i] == 'o' || new_str[i] == 'u' || new_str[i] == 'y')
        {
            i++; // пропускаем текущую гласную букву
            continue;
        }
        temp_str += new_str[i];
        i++;
    }
    new_str = temp_str;
    return new_str;
}

std::string StrCutter (std::string& new_str)
{
    if (new_str.length() > 4)
    {
        new_str = new_str.substr(0, 4);
    }
    else
    {
        new_str.resize(4, '0');
    }

    return new_str;
}

std::string H_and_W_Deleter (std::string& new_str, const std::string& str, const char FIRST_LETTER)
{
    new_str += FIRST_LETTER;
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
    return new_str;
}

std::string EqualsDeleter (std::string& temp_str, std::string& new_str)
{
    temp_str += new_str[0]; // чтобы созранить первую букву, которую нельзя изменять
    for (int i = 1; i < new_str.length(); i++)
    {
        if (temp_str[temp_str.length() - 1] != new_str[i])
        {
            temp_str += new_str[i];
        }
    }
    new_str = temp_str;

    return new_str;
}

std::string StrToCode (const std::string& str) // функция, возвращающая строку
{
    assert (str.length() != 0); // проверка, что строка не пустая
    std::string result;
    const char FIRST_LETTER = toupper(str[0]); // запоминаем первую букву

    // удаляем все вхождения символов h и w (за исключением первой буквы)
    std::string new_str;
    new_str = H_and_W_Deleter (new_str, str, FIRST_LETTER);

    // заменяем согласные на цифры
    new_str = Replacer (new_str);

    // удаляем последовательность одинаковых цифр
    std::string temp_str;
    new_str = EqualsDeleter (temp_str, new_str);

    // удаляем гласные (за исключением первой буквы)
    new_str = VowelsDeleter (new_str, temp_str);
    new_str[0] = FIRST_LETTER;

    // обрезаем до первых четырёх символов и заполняем недостающие символы 0
    new_str = StrCutter (new_str);

    return new_str; 
}

bool isSimilar (std::string str1, std::string str2)
{
    std::string code1 = StrToCode(str1);
    std::string code2 = StrToCode(str2);

    if (code1 == code2) return true;
    else                return false;
}
