#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main(void) {
	int inFile, outFile;
	ssize_t inChar, outChar;
	char *buf, inputBuf[100], outputBuf[100];

	// open the input file with read only
	printf("Please enter a file name or path you want to copy from: ");
	scanf("%s", inputBuf);
	inFile = open(inputBuf, O_RDONLY);

	// check if the file was successfully opened
	if(inFile == -1) {
		perror("Error: ");
		exit(1);
	}

	printf("Please enter a file name which you want to write\n");
	printf("if this file doesn't exist, We will create it~\n");
	scanf("%s", outputBuf);
	// 0644=>Authority	-rw-r--r--
	outFile = open(outputBuf, O_WRONLY|O_CREAT, 0644);

	if(outFile == -1) {
		perror("Error: ");
		exit(1);
	}

	// set the buffer to store the file content
	buf = (char*)malloc(1024 * (sizeof(char*)));
	memset(buf, 0, 1024);

	while(inChar = read(inFile, buf, 1024)) {
		outChar = write(outFile, buf, (ssize_t)inChar);
		if(inChar != outChar) {
			perror("error: ");
			exit(1);
		}
		else {
			printf("copy the file successfully~~~\n");
		}
	}

	free(buf);
	close(inFile);
	close(outFile);

	return 0;
}
