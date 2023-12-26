#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

template<typename T>
std::string to_string(const T& value) {
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template<typename... Args>
std::string format(const std::string& formatString, Args... args) {
    std::vector<std::string> arguments = { to_string(args)... };
    std::string result;
    size_t argIndex = 0;
    bool inBraces = false;
  
    for (char c : formatString) {
        if (c == '{') {
            if (inBraces) {
                throw std::invalid_argument("Invalid format string");
            }
            inBraces = true;
        } else if (c == '}') {
            if (!inBraces) {
                throw std::invalid_argument("Invalid format string");
            }
            inBraces = false;
            if (argIndex >= arguments.size()) {
                throw std::invalid_argument("Too few arguments for format string");
            }
            result += arguments[argIndex++];    
        } else {
            if (!inBraces) {
                throw std::invalid_argument("Invalid format string");
            }
            result += c;
        }
    }
  
    if (inBraces) {
        throw std::invalid_argument("Invalid format string");
    }
  
    return result;
}

int main() {
    std::string text = format("{1}+{1} = {0}", 2, "one");
    std::cout << text << std::endl;
    
    return 0;
}
