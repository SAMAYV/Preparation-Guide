#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t room;
sem_t chopstick[5];

void eat(int phil) {
	printf("\nPhilosopher %d is eating", phil);
}

// Then we have called the sem_wait function which first checks if the resource is available and if it is available,
// the resource is allocated to the philosopher i.e. the semaphore is locked.
void philosopher(int phil)
{
	sem_wait(&room);
	printf("\nPhilosopher %d has entered room", phil);

	// we are blocking the chopsticks towards the left and the right of the philosopher.
	sem_wait(&chopstick[phil]);
	sem_wait(&chopstick[(phil + 1) % 5]);

	eat(phil);
	sleep(2);
	printf("\nPhilosopher %d has finished eating",phil);

	// If it returns a positive value, the semaphore is unlocked successfully.
	sem_post(&chopstick[(phil + 1) % 5]);
	sem_post(&chopstick[phil]);
	sem_post(&room);
}
int main()
{
	// Here, the semaphore room is a counting semaphore since there is one dining room which can accommodate 4 philosophers.
	// Here, the semaphore room is initialized as 4
	// The second parameter is pshared. If it is zero, the semaphore is shared between threads; else it is shared between processes
	sem_init(&room, 0, 4);

	for(int i = 0; i < 5; i++){
		sem_init(&chopstick[i], 0, 1);
	}
	vector<thread> tid;
	for(int i = 0; i < 5; i++){
		tid.push_back(thread(philosopher, i));
	}
	for(int i = 0; i < 5; i++){
		tid.at(i).join();
	}
	return 0;
}

