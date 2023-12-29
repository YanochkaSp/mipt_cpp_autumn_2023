#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

class BigInt {
public:
    BigInt() : digits(std::make_unique<int[]>(DEFAULT_SIZE)), size(1), negative(false) 
    {
        digits[0] = 0;
    }

    explicit BigInt(const std::string& number) : digits(std::make_unique<int[]>(DEFAULT_SIZE)), size(1), negative(false) 
    {
        if (number[0] == '-') 
        {
            negative = true;
            size = number.length() - 1;
        }
        else 
        {
            size = number.length();
        }
        
        if (size > DEFAULT_SIZE) 
        {
            resize(size);
        }
        
        int offset = negative ? 1 : 0;
        
        for (int i = 0; i < size; i++) 
        {
            digits[i] = number[size - i - offset] - '0';
        }
    }

    BigInt(int32_t number) : digits(std::make_unique<int[]>(DEFAULT_SIZE)), size(1), negative(false) 
    {
        if (number < 0) 
        {
            negative = true;
            number = -number;
        }
        
        if (number > 0) 
        {
            size = 0;
            while (number > 0) 
            {
                digits[size++] = number % 10;
                number /= 10;
            }
        }
    }

    BigInt(const BigInt& other) : digits(std::make_unique<int[]>(other.size)), size(other.size), negative(other.negative) 
    {
        std::copy(other.digits.get(), other.digits.get() + size, digits.get());
    }

    BigInt(BigInt&& other) noexcept : digits(std::move(other.digits)), size(other.size), negative(other.negative) 
    {
        other.size = 0;
        other.negative = false;
    }

    BigInt& operator=(const BigInt& other) 
    {
        if (this != &other) 
        {
            if (size < other.size) 
            {
                digits.reset(new int[other.size]);
            }
            
            size = other.size;
            negative = other.negative;
            std::copy(other.digits.get(), other.digits.get() + size, digits.get());
        }
        return *this;
    }

    BigInt& operator=(BigInt&& other) noexcept 
    {
        if (this != &other) 
        {
            digits = std::move(other.digits);
            size = other.size;
            negative = other.negative;
            other.size = 0;
            other.negative = false;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& number) 
    {
        if (number.negative) os << '-';
        
        for (int i = number.size - 1; i >= 0; i--) 
        {
            os << number.digits[i];
        }
        
        return os;
    }

    static BigInt add(const BigInt& a, const BigInt& b) 
    {
        return a+b;
    }

    static BigInt subtract(const BigInt& a, const BigInt& b) 
    {
        return a-b;
    }

    friend BigInt operator+(const BigInt& a, const BigInt& b) 
    {
        return a.negative == b.negative ? add(a, b) : subtract(a, b);
    }

    friend BigInt operator+(const BigInt& a, int32_t b) 
    {
        return a + BigInt(b);
    }

    friend BigInt operator+(int32_t a, const BigInt& b) 
    {
        return BigInt(a) + b;
    }

    friend BigInt operator-(const BigInt& a, const BigInt& b) 
    {
        return a.negative == b.negative ? subtract(a, b) : add(a, b);
    }

    friend BigInt operator-(const BigInt& a, int32_t b) 
    {
        return a - BigInt(b);
    }

    friend BigInt operator-(int32_t a, const BigInt& b) 
    {
        return BigInt(a) - b;
    }

    friend BigInt operator*(const BigInt& a, const BigInt& b) 
    {
        BigInt result;
        result.resize(a.size + b.size);

        for (int i = 0; i < a.size; i++) 
        {
            int carry = 0;
            for (int j = 0; j < b.size || carry; j++) 
            {
                int digit = result.digits[i + j] + a.digits[i] * (j < b.size ? b.digits[j] : 0) + carry;
                result.digits[i + j] = digit % 10;
                carry = digit / 10;
            }
        }
        
        result.normalize();
        
        result.negative = a.negative != b.negative;

        return result;
    }

    friend BigInt operator*(const BigInt& a, int32_t b) 
    {
        return a * BigInt(b);
    }

    friend BigInt operator*(int32_t a, const BigInt& b) 
    {
        return BigInt(a) * b;
    }

    BigInt operator-() const 
    {
        BigInt result(*this);
        result.negative = !negative;
        return result;
    }

    void resize(int new_size) 
    {
        auto new_digits = std::make_unique<int[]>(new_size);

        std::copy(digits.get(), digits.get() + size, new_digits.get());
        digits = std::move(new_digits);
        size = new_size;
    }

    void normalize() 
    {
        while (size > 1 && digits[size - 1] == 0) 
        {
            size--;
        }
    }

private:
    std::unique_ptr<int[]> digits;
    int size;
    bool negative;
    static const int DEFAULT_SIZE = 100;
};

int main() 
{
    BigInt a("1234567890");
    BigInt b("9876543210");

    BigInt c = a + b;
    std::cout << c << std::endl;

    BigInt d = a * b;
    std::cout << d << std::endl;

    BigInt e = a - b;
    std::cout << e << std::endl;

    BigInt f = -a;
    std::cout << f << std::endl;

    return 0;
}