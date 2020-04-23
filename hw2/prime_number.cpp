#include <unistd.h>
#include <iostream>

int num;

void * thread_child(void * data);

int main(void) {
	pthread_t thread;

	std::cout << "this program is used to output all prime number which smaller than the input number or equal the input number~~~" << std::endl;
	std::cout << "please input the number: ";
	std::cin >> num;

	pthread_create(&thread, NULL, thread_child, NULL);
	pthread_join(thread, NULL);
}

void * thread_child(void * data) {
	int flag = 0;
	int prime_num[num] = {0};
	int count = 0;

	std::cout << num << std::endl;
	std::cout << "the answer is: " << std::endl;

	for (int i = 2; i <= num; i++) {
		flag = 0;
		for (int j = 2; j <= i/2; ++j) {
			if (i % j == 0) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			prime_num[count] = i;
			count++;
		}
	}

	std::cout << prime_num[0];
	for (int i = 1; i < num; i++) {
		if (prime_num[i] > 1 && prime_num[i] <= num) {
			std::cout << ", " << prime_num[i];
		}
	}
	std::cout << "" << std::endl;
}
