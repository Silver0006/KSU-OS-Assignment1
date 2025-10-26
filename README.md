Program Description
Through the use of semephores and shared memory two programs/processes(producer/consumer) will transfer an array of two ints.
The producer generates the ints using rand() and the consumer prints them. 
For illustrating the purpose of this program, the producer also prints what it generates.
producer.cpp contains the code for producer. consumer.cpp contains the code for consumer.

Usage Instructions (Run in terminal)
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer & ./consumer

Usage Instructions (Run in background)
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer & ./consumer &

Key Components
The programs use the POSIX shm_open and mmap function to create shared memory.
The programs use the "mutex" semaphore to indicate whether the shared memory is being accessed.
Both programs also use addition semphores to indicate whether the array has been filled "sem_full" & "sem_empty"
