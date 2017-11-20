#include <iostream>

struct memory {
    struct memory *next;
    int size;
};

unsigned int memory_size = 1024;
struct memory *_memory = nullptr;
struct memory *base_memory_address = nullptr;

void inicializa_mem() {
    _memory = (memory *) malloc(memory_size);
    _memory->size = memory_size - sizeof(struct memory);
    _memory->next = nullptr;
}

void mostra_mem() {
    auto *iterator = _memory;
    while (iterator != nullptr) {
        if (iterator->size > 0)
            std::cout << "Avaliable Size:" << iterator->size << std::endl;
        else
            std::cout << (0 - iterator->size) << std::endl;
        iterator = iterator->next;
    }
}

void *first_fit(int size) {
    auto *iterator = _memory;
    struct memory *previous = nullptr;
    int _size = size + sizeof(struct memory);
    while (iterator != nullptr) {
        if (iterator->size >= _size) {
            previous = iterator;
            iterator = iterator + sizeof(struct memory) + size;
            iterator->size = previous->size - size - (sizeof(struct memory));
            iterator->next = previous->next;
            previous->next = iterator;
            previous->size = 0 - size;
            std::cout << previous + sizeof(struct memory) << std::endl;
        } else {
            if (iterator->size > size) {
                iterator->size = iterator->size * -1;
                std::cout << iterator + sizeof(struct memory) << std::endl;
            }
        }
        iterator = iterator->next;
    }
}

struct memory *_next = nullptr;

void *next_fit(int size) {
    struct memory *iterator;
    struct memory *previous = nullptr;
    int _size = size + sizeof(struct memory);

    if (_next->next == nullptr)
        iterator = _memory;
    else
        iterator = _next->next;

    while (iterator != nullptr) {
        if (iterator->size >= _size) {
            previous = iterator;
            iterator = iterator + sizeof(struct memory) + size;
            iterator->size = previous->size - size - (sizeof(struct memory));
            iterator->next = previous->next;
            previous->next = iterator;
            previous->size = 0 - size;
            _next = iterator;
            std::cout << previous + sizeof(struct memory) << std::endl;
        } else {
            if (iterator->size > size) {
                iterator->size = iterator->size * -1;
                _next = iterator;
                std::cout << iterator + sizeof(struct memory) << std::endl;
            }
        }
        iterator = iterator->next;
    }

    iterator = _memory;
    while (iterator != _next) {
        if (iterator->size >= _size) {
            previous = iterator;
            iterator = iterator + sizeof(struct memory) + size;
            iterator->size = previous->size - size - (sizeof(struct memory));
            iterator->next = previous->next;
            previous->next = iterator;
            previous->size = 0 - size;
            _next = iterator;
            std::cout << previous + sizeof(struct memory) << std::endl;
        } else {
            if (iterator->size > size) {
                iterator->size = iterator->size * -1;
                _next = iterator;
                std::cout << iterator + sizeof(struct memory) << std::endl;
            }
        }
        iterator = iterator->next;
    }
}

int main(int argc, char *argv[]) {
    inicializa_mem();
    next_fit(10);
    next_fit(20);
    mostra_mem();

    return 0;
}