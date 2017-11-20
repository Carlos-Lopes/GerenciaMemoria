#include <iostream>

struct memory {
    struct memory *next;
    int size;
};

unsigned int memory_size = 1024;
struct memory *_memory = nullptr;

void begin_memory() {
    _memory = (memory *) malloc(memory_size);
    _memory->size = memory_size - sizeof(struct memory);
    _memory->next = nullptr;
}

void show_memory() {
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
    struct memory *address = nullptr;
    struct memory *previous = nullptr;
    auto *iterator = _memory;
    int _size = size + sizeof(struct memory);

    while (iterator != nullptr) {
        if (iterator->size >= _size) {
            previous = iterator;
            iterator += sizeof(struct memory) + size;
            iterator->size = previous->size - size - (sizeof(struct memory));
            iterator->next = previous->next;
            previous->next = iterator;
            previous->size = 0 - size;
            address = previous + sizeof(struct memory);
        } else {
            if (iterator->size > size) {
                iterator->size = iterator->size * -1;
                address = iterator + sizeof(struct memory);
            }
        }
        iterator = iterator->next;
    }

    return address;
}

struct memory *_next = nullptr;

void *next_fit(int size) {
    struct memory *address = nullptr;
    struct memory *iterator = nullptr;
    struct memory *previous = nullptr;
    int _size = size + sizeof(struct memory);

    if (_next == nullptr)
        iterator = _memory;
    else
        iterator = _next;

    while (iterator != nullptr) {
        if (iterator->size >= _size) {
            previous = iterator;
            iterator += sizeof(struct memory) + size;
            iterator->size = previous->size - size - (sizeof(struct memory));
            iterator->next = previous->next;
            previous->next = iterator;
            previous->size = 0 - size;
            _next = iterator;
            address = previous + sizeof(struct memory);
        } else {
            if (iterator->size > size) {
                iterator->size = iterator->size * -1;
                _next = iterator;
                address = iterator + sizeof(struct memory);
            }
        }
        iterator = iterator->next;
    }

    iterator = _memory;
    while (iterator != _next) {
        if (iterator->size >= _size) {
            previous = iterator;
            iterator += sizeof(struct memory) + size;
            iterator->size = previous->size - size - (sizeof(struct memory));
            iterator->next = previous->next;
            previous->next = iterator;
            previous->size = 0 - size;
            _next = iterator;
            address = previous + sizeof(struct memory);
        } else {
            if (iterator->size > size) {
                iterator->size = iterator->size * -1;
                _next = iterator;
                address = iterator + sizeof(struct memory);
            }
        }
        iterator = iterator->next;
    }

    return address;
}

void *best_fit(int size) {
    struct memory *address = nullptr;
    struct memory *best = nullptr;
    struct memory *previous_best = nullptr;
    auto *iterator = _memory;
    int _size = size + sizeof(struct memory);

    while (iterator != nullptr) {
        if (best == nullptr && iterator->size > 0)
            best = iterator;
        else if (((iterator->size >= _size) || (iterator->size >= size)))
            best = iterator;

        iterator = iterator->next;
    }

    if (best->size >= _size) {
        previous_best = best;
        best += sizeof(struct memory) + size;
        best->size = previous_best->size - size - (sizeof(struct memory));
        best->next = previous_best->next;
        previous_best->next = best;
        previous_best->size = 0 - size;

        address = previous_best + sizeof(struct memory);
    } else {
        if (best->size > size) {
            best->size = best->size * -1;
            address = best + sizeof(struct memory);
        }
    }
    return address;
}

void *worst_fit(int size) {
    struct memory *address = nullptr;
    struct memory *worst = nullptr;
    struct memory *previos_best = nullptr;
    auto *iterator = _memory;
    int _size = size + sizeof(struct memory);

    while (iterator != nullptr) {
        if (worst == nullptr && iterator->size > 0) {
            worst = iterator;
        } else {
            if (((iterator->size >= _size) || (iterator->size >= size)) && (iterator->size > worst->size)) {
                worst = iterator;
            }
        }
        iterator = iterator->next;
    }

    if (worst->size >= _size) {
        previos_best = worst;
        worst += sizeof(struct memory) + size;
        worst->size = previos_best->size - size - (sizeof(struct memory));
        worst->next = previos_best->next;
        previos_best->next = worst;
        previos_best->size = 0 - size;

        address = previos_best + sizeof(struct memory);
    } else {
        if (worst->size > size) {
            worst->size = worst->size * -1;;
            address = worst + sizeof(struct memory);
        }
    }
    return address;
}

void free(struct memory *address) {
    auto *iterator = _memory;
    auto *aux = address - sizeof(struct memory);
    struct memory *previous = nullptr;

    while (iterator != nullptr && iterator != aux)
        iterator = iterator->next;

    if (iterator == nullptr || (iterator->size > 0)) {
        std::cout << "Invalid Address" << std::endl;
        return;
    }

    aux->size = aux->size * -1;
    iterator = _memory;
    while (iterator != nullptr) {
        if (iterator == address) {
            if (previous->size > 0) {
                previous->size += iterator->size + sizeof(struct memory);
                previous->next = iterator->next;
                if (_next == iterator)
                    _next = previous;
            } else
                previous = previous->next;

            iterator = iterator->next;
            if (iterator->size > 0) {
                previous->size += iterator->size + sizeof(struct memory);
                previous->next = iterator->next;
                if (_next == iterator)
                    _next = previous;
            }
        }
        previous = iterator;
        iterator = iterator->next;
    }
}

int main(int argc, char *argv[]) {
    begin_memory();
    auto first_address = (struct memory *) first_fit(10);
    auto next_address = (struct memory *) next_fit(20);
    auto best_address = (struct memory *) best_fit(8);
    auto worst_address = (struct memory *) worst_fit(15);
    show_memory();
    return 0;
}