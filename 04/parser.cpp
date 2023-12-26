#include <functional>
#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>

class TokenParser
{
public:
    using func_ptr = std::function<void(const std::string&)>;
    using func_digit_ptr = std::function<void(const uint64_t&)>;
    using func_str_ptr = std::function<void(const std::string&)>;

    TokenParser() = default;

    void SetStartCallback(func_ptr callback)
    {
        start_callback = callback;
    }

    void SetEndCallback(func_ptr callback)
    {
        end_callback = callback;
    }

    void SetDigitTokenCallback(func_digit_ptr callback)
    {
        digit_callback = callback;
    }

    void SetStringTokenCallback(func_str_ptr callback)
    {
        string_callback = callback;
    }

    void Parse(const std::string& text)
    {
        if (start_callback)
            start_callback(text);

        std::istringstream iss(text);
        std::string token;
        while (iss >> token)
        {
            if (IsNumber(token))
            {
                if (digit_callback)
                {
                    uint64_t number = std::stoull(token);
                    digit_callback(number);
                }
            }
            else
            {
                if (string_callback)
                    string_callback(token);
            }
        }

        if (end_callback)
            end_callback(text);
    }

private:
    bool IsNumber(const std::string& token)
    {
        for (char c : token)
        {
            if (!std::isdigit(c))
                return false;
        }
        return true;
    }

    func_ptr start_callback;
    func_ptr end_callback;
    func_digit_ptr digit_callback;
    func_str_ptr string_callback;
};

void start_callback(const std::string& text)
{
    std::cout << "Start Parsing: " << text << std::endl;
}

void end_callback(const std::string& text)
{
    std::cout << "End Parsing: " << text << std::endl;
}

void digit_callback(const uint64_t& number)
{
    std::cout << "Digit Token: " << number << std::endl;
}

void string_callback(const std::string& token)
{
    std::cout << "String Token: " << token << std::endl;
}

int main()
{
    TokenParser parser;
    parser.SetStartCallback(start_callback);
    parser.SetEndCallback(end_callback);
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);

    std::string line;
    while (std::getline(std::cin, line)) {
        parser.Parse(line);
    }

    return 0;
}