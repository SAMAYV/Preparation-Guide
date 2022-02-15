#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

#define NUM_THREADS 2
#define BUFFER_SIZE 10

typedef struct {
	int buf[BUFFER_SIZE];
	int w_index;
	int r_index;
	int filled_slots;
} CIR_BUF;

CIR_BUF CirBuf = {0};

mutex sync_mutex;
sem_t sem_empty_slots;
sem_t sem_filled_slots;

/*
 * When Producer Consumer problem is implemented using Mutex and condition variable,
 * we first acquire the sync_mutex and then wait conditionally (if Buffer is full/empty),
 * Conditional wait will unlock the sync_mutex so that consumer can acquire sync_mutex, which will eventually signal the waiting thread
 * so that waiting thread can run. When waiting thread starts running, it automatically acquire the lock on sync_mutex
 * So here we first acquire the sync_mutex and then wait
 *
 * But same is not applicable when Produce consumer problem is solved using Semaphore
 * Here if we first acquire sync_mutex and then if slots are completely empty/filled, then thread will wait
 * inside sem_wait continuously, (In contrast to conditional wait using mutex), sem_wait does not release sync_mutex
 * In this case second thread can not run because sync_mutex is already locked by first thread.
 * To avoid this deadlock, we first wait within sem_wait and if count is non zero then lock the sync mutex,
 * to make sure second thread can not modify shared data at the same moment.
 */

void consumer() {
	while(1) {
		sem_wait(&sem_filled_slots);
		sync_mutex.lock();

		cout << "consumed " << CirBuf.buf[CirBuf.r_index] << endl << flush;
		CirBuf.r_index = (CirBuf.r_index + 1) % BUFFER_SIZE;
		CirBuf.filled_slots--;

		sync_mutex.unlock(); /* It does not matter, you can release lock after sending below wake up signal as well */
		sem_post(&sem_empty_slots);
	}
}
void producer() {
	while(1) {
		sem_wait(&sem_empty_slots);
		sync_mutex.lock();

		CirBuf.buf[CirBuf.w_index] = CirBuf.w_index;
		cout << "produced " << CirBuf.buf[CirBuf.w_index] << endl << flush;
		CirBuf.w_index = (CirBuf.w_index + 1) % BUFFER_SIZE;
		CirBuf.filled_slots++;

		sync_mutex.unlock();
		sem_post(&sem_filled_slots);
	}
}
int main()
{
	thread thread_id[NUM_THREADS];

	if(sem_init(&sem_empty_slots, 0, BUFFER_SIZE)) {
		cout << "Init Sem empty slots failed" << endl;
	}
	if(sem_init(&sem_filled_slots, 0, 0)) {
		cout << "Init Sem filled slots failed" << endl;
	}
	thread_id[0] = thread(producer);
	thread_id[1] = thread(consumer);

	thread_id[0].join();
	thread_id[1].join();

	sem_destroy(&sem_empty_slots);
	sem_destroy(&sem_filled_slots);
	return 0;
}
