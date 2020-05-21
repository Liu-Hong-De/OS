#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <deque>

#define REFERENCE_LENGTH 20

int * referenceString;

void generateString();
int * frameInitial(int frame_size);
int FIFO(int frame_size);
int LRU(int frame_size);
int findNext(int location, int value);
int opt(int frame_size);

using namespace std;

int main() {
	int frame_size;

	printf("please enter the number of page frame: ");
	scanf("%d", &frame_size);
	
	generateString();
	printf("FIFO page fault number: %d\n\n", FIFO(frame_size));
	printf("LRU page fault number: %d\n\n", LRU(frame_size));
	printf("optimal page fault number: %d\n\n", opt(frame_size));
}

// generate the random reference string
void generateString() {
	srand(time(NULL));	// random seed
	referenceString = (int*)malloc(sizeof(int) * REFERENCE_LENGTH);
	printf("The randomized reference string: ");
	for(int i = 0; i < REFERENCE_LENGTH; i++) {	// random range 0-9
		referenceString[i] = rand() % 10;
		printf("%d ", referenceString[i]);
	}
	printf("\n");
}

// FIFO
int FIFO(int frame_size) {
	deque<int> frame;
	bool hit;	
	int page_fault = 0;

	frame.push_back(referenceString[0]);	// push first element into the deque
	page_fault++;
	printf("%d\n", frame[0]);

	for(int i = 1; i < REFERENCE_LENGTH; i++) {
		hit = false;
		for(auto it = frame.begin(); it != frame.end(); ++it) {		// this page is already in the frame
			if(*it == referenceString[i]) {
				hit = true;
			}
		}
		
		if(hit == false) {
			if(frame.size() < frame_size) {		// the frame is not full
				frame.push_back(referenceString[i]);
			}
			else {		// pop the first entry page
				frame.pop_front();
				frame.push_back(referenceString[i]);
			}
			page_fault++;
		}

		for(auto it = frame.begin(); it != frame.end(); ++it) {
			printf("%d ", *it);
		}
		printf("\n");
	}
	return page_fault;
}

// LRU
int LRU(int frame_size) {
	deque<int> frame;
	bool hit;
	int page_fault = 0;

	frame.push_back(referenceString[0]);	// put first page into frame
	page_fault++;
	printf("%d\n", frame[0]);

	for(int i = 1; i < REFERENCE_LENGTH; i++) {
		hit = false;
		for(int j = 0; j < frame_size; j++) {
			if(referenceString[i] == frame[j]) {	// this page is already in the frame
				hit = true;
				frame.erase(frame.begin()+j);	// put this frame to the first element
				frame.push_back(referenceString[i]);	// first element represent this page be used recently
			}
		}

		if(hit == false) {
			if(frame.size() < frame_size) {
				frame.push_back(referenceString[i]);
			}
			else {
				frame.pop_front();
				frame.push_back(referenceString[i]);
			}
			page_fault++;
		}

		for(auto it = frame.begin(); it != frame.end(); ++it) {
			printf("%d ", *it);
		}
		printf("\n");
	}

	return page_fault;
}

// this function is for the optimal to find the next page location
int findNext(int location, int value) {
	for(int i = location+1; i < REFERENCE_LENGTH; i++) {
		if(value == referenceString[i]) {
			return i;
		}
	}
	return 100;
}

// optimal
int opt(int frame_size) {
	deque<int> frame, num;		// num store the location of this page will access again
	int page_fault = 0;
	bool hit;
	int max;
	int max_loc = -1;

	frame.push_back(referenceString[0]);	// put first page into the frame
	num.push_back(findNext(0, referenceString[0]));
	page_fault++;
	printf("%d\n", frame[0]);

	for(int i = 1; i < REFERENCE_LENGTH; i++) {
		hit = false;
		max = -1;
		for(int j = 0; j < frame.size(); j++) {		// this page is already in the frame
			if(referenceString[i] == frame[j]) {
				hit = true;
			}
		}

		if(hit == false) {
			if(frame.size() < frame_size) {
				frame.push_back(referenceString[i]);
			}
			else {
				for(int j = 0; j < frame_size; j++) {
					if(num[j] > max) {
						max = num[j];
						max_loc = j;
					}
				}
				frame.erase(frame.begin()+max_loc);	// pop the page which will be used after the other pages in the frame
				frame.push_back(referenceString[i]);
			}
			page_fault++;
		}

		// update the num
		num.clear();
		for(int j = 0; j < frame.size(); j++) {
			num.push_back(findNext(i, frame[j]));
		}

		for(auto it = frame.begin(); it != frame.end(); ++it) {
			printf("%d ", *it);
		}
		printf("\n");
	}
	return page_fault;
}
