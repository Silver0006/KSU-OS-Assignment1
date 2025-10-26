// consumer.cpp by Aidan Marias
#include <cstdlib>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 

int main(){
    sem_t *sem_full = sem_open("/sem_full", 0); // Indicator if buffer is full
    sem_t *sem_empty = sem_open("/sem_empty", 0); // Indicator if buffer is empty
    sem_t *sem_mutex = sem_open("/sem_mutex", 0); // If process is modifying shared memory
    int shm_fd = shm_open("/shared_data", O_RDWR, 0666); // Create shared memory object
    int *cart = (int*) mmap(
        NULL, // Address starting point/hint thing?
        2*sizeof(int), // Allocation size
        PROT_READ, // Permision to write to shared data
        MAP_SHARED, // Permision to make viewable to other processes
        shm_fd, //Shared memory
        0 // Adress offset
    );

    while(true) {
        sem_wait(sem_full);
        sem_wait(sem_mutex); 
        std::cout << "Consumer: " << cart[0] << ' ' << cart[1] << std::endl;
        sem_post(sem_mutex);
        sem_post(sem_empty);
    }
    




    return 0;
}