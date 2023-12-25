#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>
#include <assert.h>

struct Allocator
{
    char* mem;            // Указатель на начало выделенной памяти
    size_t maxSize;       // Размер выделенной памяти
    size_t offset;        // Смещение от начала памяти

    Allocator(size_t maxSize): maxSize(maxSize), offset(0)
    {
        mem = new char[maxSize];
    }

    char* alloc(size_t size)
    {
        if (offset + size > maxSize) return nullptr;
        char* ptr = mem + offset;
        offset += size;
        return ptr;
    }
    
    void reset()
    {
        offset = 0;
    }

    ~Allocator()
    {
        delete[] mem;
    }
};

Allocator* init_allocator(Allocator *alloc, size_t maxSize);

char* alloc(Allocator *alloc, size_t size);

void reset(Allocator *alloc);

void clear(Allocator *alloc);

#endif