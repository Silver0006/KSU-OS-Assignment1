// producer.cpp by Aidan Marias
#include "shared.hpp"
#include <cstdlib>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main(){
    srand(300); // Initialize rand() seed. Picked arbitrary number.
    sem_unlink("/sem_full");
    sem_unlink("/sem_empty");
    sem_unlink("/sem_mutex");
    sem_t *sem_full = sem_open("/sem_full", O_CREAT, 0666, 0); // Indicator if buffer is full
    sem_t *sem_empty = sem_open("/sem_empty", O_CREAT, 0666, 1); // Indicator if buffer is empty
    sem_t *sem_mutex = sem_open("/sem_mutex", O_CREAT, 0666, 1); // If process is modifying shared memory

    int shm_fd = shm_open("/shared_data", O_CREAT | O_RDWR, 0666); // Create shared memory object
    ftruncate(shm_fd, sizeof(passable_data)); // Set shared memory to size of passable_data structure.
    passable_data *cart = (passable_data*) mmap(
        NULL, // Address starting point/hint thing?
        sizeof(passable_data), // Allocation size
        PROT_WRITE, // Permision to write to shared data
        MAP_SHARED, // Permision to make viewable to other processes
        shm_fd, //Shared memory
        0 // Adress offset
    );





    while(true) {
        sem_wait(sem_empty);
        sem_wait(sem_mutex); 
        cart->buffer[0] = std::rand();
        cart->buffer[1] = std::rand();
        std::cout << "Producer: " << cart->buffer[0] << ' ' << cart->buffer[1] << std::endl;
        sem_post(sem_mutex);
        sem_post(sem_full);
    }
    




    return 0;
}