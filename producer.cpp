// producer.cpp by Aidan Marias
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
    sem_t *sem_empty = sem_open("/sem_empty", O_CREAT, 0666, 2); // Indicator if buffer is empty
    sem_t *sem_mutex = sem_open("/sem_mutex", O_CREAT, 0666, 1); // If process is modifying shared memory
    int index = 0; // Iterator for array
    int shm_fd = shm_open("/shared_data", O_CREAT | O_RDWR, 0666); // Create shared memory object
    ftruncate(shm_fd, 2*sizeof(int)); // Set shared memory to size of passable_data structure.
    int *cart = (int*) mmap(
        NULL, // Address starting point/hint thing?
        2*sizeof(int), // Allocation size
        PROT_READ | PROT_WRITE, // Permision to read/write to shared data
        MAP_SHARED, // Permision to make viewable to other processes
        shm_fd, //Shared memory
        0 // Adress offset
    );





    while(true) {
        int produce = std::rand();
        sem_wait(sem_empty);
        sem_wait(sem_mutex); 
        cart[index] = produce;
        std::cout << "Producer: " << cart[index] << std::endl;
        index = (index + 1) % 2;
        sem_post(sem_mutex);
        sem_post(sem_full);
        sleep(1);
    }
    




    return 0;
}