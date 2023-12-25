#include "allocator.hpp"

Allocator* init_allocator(Allocator *alloc, size_t maxSize) // Инициализация аллокатора
{
    return new Allocator(maxSize);
}

char* alloc(Allocator *alloc, size_t size) // Выделение памяти
{
    return alloc->alloc(size);
} 

void reset(Allocator *alloc) // Сброс аллокатора
{
    alloc->reset();
}

void clear(Allocator *alloc) // Очистка аллокатора
{
    delete alloc;
}