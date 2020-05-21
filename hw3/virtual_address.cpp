#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

int main(int argc, char **argv) {
	unsigned int address;
	unsigned int page_number;
	unsigned int offset;

	if(argc < 2) {
		printf("please enter the address behind the execution file name!!!\n");
		exit(-1);
	}

	address = atoi(argv[1]);
	page_number = address / PAGE_SIZE;
	offset = address % PAGE_SIZE;

	printf("The address %u contains: \n", address);
	printf("page number = %u\n", page_number);
	printf("offset = %u\n", offset);
}
