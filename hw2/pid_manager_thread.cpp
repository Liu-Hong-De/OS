#include <iostream>
#include <limits.h>
#include <unistd.h>

#define MIN_PID 500
#define MAX_PID 3000
#define char_bit CHAR_BIT

unsigned char *init;
int seed;

int allocate_map();
int allocate_pid();
void release_pid(int pid);
void * thread_call(void * data);

int main(void) {
	int thread_num = 0;

	std::cout << "please enter how many threads you want to create: ";
	std::cin >> thread_num;

	pthread_t thread[thread_num];
	
	// random seed
	srand(seed);

	allocate_map();

	for(int i = 0; i < thread_num; i++) {	
		pthread_create(&thread[i], NULL, thread_call, NULL);
	}

	for(int i = 0; i < thread_num; i++) {
		pthread_join(thread[i], NULL);
	}

	return 0;
}

// create and initial data structure
int allocate_map() {
	init = (unsigned char*)malloc((MAX_PID - MIN_PID + char_bit) / char_bit * sizeof(char));
	if(init)
		return 1;	// success
	return -1;		// failed
}

// allocate pid
int allocate_pid() {
	//cout << "allocate_pid" << endl;
	int i = 0;
	int pid = init[i / char_bit] & (1 << (i & (char_bit - 1)));
	
	while(pid != 0) {
		i++;
		pid = init[i / char_bit] & (1 << (i & (char_bit - 1)));
	}

	// all pid are in use
	if(i + MIN_PID > MAX_PID)
		return -1;
	
	init[i / char_bit] |= 1 << (i & (char_bit - 1));
	return i + MIN_PID;
}

void release_pid(int pid) {
	if(pid < 500 || pid > 3000) {
		std::cout << "invalid pid: it should between 500 and 3000!!!" << std::endl;
		exit(1);
	}
	int i = pid - MIN_PID;
	init[i / char_bit] &= ~(1 << (i & (char_bit - 1)));
	printf("release the %d\n", pid);
}

// thread
void * thread_call(void * data) {
	int thread_init = allocate_pid();
	printf("[allocate] %d\n", thread_init);
	
	// sleep random time
	sleep((rand() % 1000) / 1000.0);

	release_pid(thread_init);
}
