#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstring>

template<typename T>
class Vector 
{
public:
    Vector() : size_(0), capacity_(0), data_(nullptr) {}

    Vector(unsigned int size) : size_(size), capacity_(size) 
    {
        data_ = new T[size];
    }

    Vector(unsigned int size, const T& value) : size_(size), capacity_(size) 
    {
        data_ = new T[size];
        for (unsigned int i = 0; i < size_; i++) 
        {
            data_[i] = value;
        }
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) 
    {
        data_ = new T[capacity_];
        std::memcpy(data_, other.data_, size_ * sizeof(T));
    }

    Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), data_(other.data_) 
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~Vector() 
    {
        delete[] data_;
    }

    Vector& operator=(const Vector& other) 
    {
        if (this != &other) 
        {
            size_ = other.size_;
            capacity_ = other.capacity_;
            delete[] data_;
            data_ = new T[capacity_];
            std::memcpy(data_, other.data_, size_ * sizeof(T));
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept 
    {
        if (this != &other) 
        {
            size_ = other.size_;
            capacity_ = other.capacity_;
            delete[] data_;
            data_ = other.data_;
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    T& operator[](unsigned int index) 
    {
        return data_[index];
    }

    const T& operator[](unsigned int index) const 
    {
        return data_[index];
    }

    T& front() 
    {
        return data_[0];
    }

    const T& front() const 
    {
        return data_[0];
    }

    T& back() 
    {
        return data_[size_ - 1];
    }

    const T& back() const 
    {
        return data_[size_ - 1];
    }

    T* data() 
    {
        return data_;
    }

    const T* data() const 
    {
        return data_;
    }

    bool empty() const 
    {
        return size_ == 0;
    }

    unsigned int size() const 
    {
        return size_;
    }

    unsigned int max_size() const 
    {
        return std::numeric_limits<unsigned int>::max();
    }

    void reserve(unsigned int newCapacity) 
    {
        if (newCapacity > capacity_) 
        {
            T* newData = new T[newCapacity];
            std::memcpy(newData, data_, size_ * sizeof(T));
            delete[] data_;
            data_ = newData;
            capacity_ = newCapacity;
        }
    }

    unsigned int capacity() const 
    {
        return capacity_;
    }

    void shrink_to_fit() 
    {
        if (capacity_ > size_) 
        {
            T* newData = new T[size_];
            std::memcpy(newData, data_, size_ * sizeof(T));
            delete[] data_;
            data_ = newData;
            capacity_ = size_;
        }
    }

    void push_back(const T& value) 
    {
        if (size_ == capacity_) 
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_] = value;
        size_++;
    }

    void pop_back() 
    {
        if (size_ > 0) 
        {
            size_--;
        }
    }

    void insert(const T& value, unsigned int index) 
    {
        if (index > size_) 
        {
            return;
        }
        if (size_ == capacity_) 
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        for (unsigned int i = size_; i > index; i--) 
        {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        size_++;
    }

    template<typename... Args>
    void emplace(unsigned int index, Args&&... args) 
    {
        if (index > size_) 
        {
            return;
        }
        if (size_ == capacity_) 
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        for (unsigned int i = size_; i > index; i--) 
        {
            data_[i] = data_[i - 1];
        }
        data_[index] = T(std::forward<Args>(args)...);
        size_++;
    }

    void resize(unsigned int size) 
    {
        if (size <= capacity_) 
        {
            size_ = size;
        }
        else 
        {
            reserve(size);
            size_ = size;
        }
    }

    void erase(unsigned int index) 
    {
        if (index >= size_) 
        {
            return;
        }
        for (unsigned int i = index; i < size_ - 1; i++) 
        {
            data_[i] = data_[i + 1];
        }
        size_--;
    }

    void clear() 
    {
        size_ = 0;
    }
    
private:
    unsigned int size_;
    unsigned int capacity_;
    T* data_;
};


#endif 