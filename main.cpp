#include <iostream>

struct block {
    int size;
};

struct process {
    int size;
};

struct memory {
    struct memory *next;
    struct block *block;
    struct process *process;
};
unsigned int memory_size = 2048;
struct memory *_memory;

void inicializa_mem() {
    _memory = (memory *) malloc(memory_size);
    _memory->next = nullptr;
    _memory->block = nullptr;
    _memory->process = nullptr;
    std::cout << "Memory Adress:" << _memory << std::endl;
    std::cout << "Next Block: " << _memory->block << std::endl;
    std::cout << "Next Process: " << _memory->process << std::endl;
}

void mostra_mem() {
    std::cout << _memory << std::endl;
    auto *iterator = _memory;
    while (iterator != nullptr) {
        if (iterator->block != nullptr)
            std::cout << "Block:" << iterator->block->size << std::endl;

        if (iterator->process != nullptr)
            std::cout << "Process:" << iterator->process->size << std::endl;

        iterator = iterator->next;
    }
}

void next_fit(int size) {
    while (_memory != nullptr) {
        if (_memory->block == nullptr || _memory->block->size <= size) {
            //Insere um novo processo
            _memory->process = new (struct process);
            _memory->process->size = size;
            _memory->next += sizeof(size);
            //Reduz o tamanho do processo do Bloco

            return;
        }
        _memory = _memory->next;
    }

    std::cout << "The process couldn't be inserted" << std::endl;
}

int main(int argc, char *argv[]) {
    inicializa_mem();
    next_fit(10);
    next_fit(20);
    next_fit(30);
    mostra_mem();

    return 0;
}