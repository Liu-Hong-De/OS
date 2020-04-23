#include <iostream>
#include <limits.h>

using namespace std;

#define MIN_PID 500
#define MAX_PID 3000
#define char_bit CHAR_BIT

unsigned char *init;

int allocate_map();
int allocate_pid();
void release_pid(int pid);

int main(void) {
	int val, p_num, release_id;
	char release_flag;
	bool flag = false;

	cout << "input the process number you want to create: ";
	cin >> p_num;
	
	int amap = allocate_map();

	if(amap == 1) {
		cout << "Data structure initialized successful~~~" << endl;
		int id = 0;
		
		for(int i = 0; i < p_num; i++) {
			val = allocate_pid();
			cout << "Process: " << i+1 << "\tpid: " << val << endl;
		}

		while(!flag) {
			cout << "Do you want to release the process (Y/N): ";
			cin >> release_flag;

			if(release_flag == 'Y' || release_flag == 'y') {
				cout << "please enter the process id which you want to release: ";
				cin >> release_id;
			
				release_pid(release_id);
				cout << "Process " << release_id << " released!!!" << endl;
			
				val = allocate_pid();
				p_num++;
				cout << "Process " << p_num << "\tpid: " << val << endl;
			}
			else {
				flag = true;
			}
		}
	}
	else {
		cout << "Data structure initialized failed!!!" << endl;
	}
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
		cout << "invalid pid: it should between 500 and 3000!!!" << endl;
		exit(1);
	}
	int i = pid - MIN_PID;
	init[i / char_bit] &= ~(1 << (i & (char_bit - 1)));
}
