#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

char transform(char ch);

int main(void) {
	pid_t pid;
	char buf[1024];		// string size 4096
	int p1[2];		// p[0] for reading
	int p2[2];		// p[1] for writing

	if(pipe(p1) == -1) {
		cerr << "pipe one failed!!!";
		exit(1);
	}

	if(pipe(p2) == -1) {
		cerr << "pipe two failed!!!";
		exit(1);
	} 	

	pid = fork();
	if(pid < 0) {
		cerr << "fork failed!!!";
		exit(1);
	}
	// fork returns the child pid to parent
	else if(pid > 0) {
		close(p1[1]);		// close the first pipe write
		read(p1[0], buf, sizeof(buf));		// read from first pipe

		// transform the character
		for(int i = 0; i < strlen(buf); i++) {	
			buf[i] = transform(buf[i]);
		}

		write(p2[1], buf, strlen(buf) + 1);		//write to second pipe
		wait(NULL);		// wait for child to send the string
	}
	else {
		close(p1[0]);		// close the first pipe read
		cout << "Please input the string to transform the character: " << endl;
		cin >> buf;		// input
		cout << "the original string is " << buf << endl;

		write(p1[1], buf, strlen(buf) + 1);		// write to the first pipe
		read(p2[0], buf, sizeof(buf));			// read from second pipe
		cout << "the transform string is " << buf << endl;	// result

		exit(0);
	}

	return 0;
}

char transform(char ch) {
	ch = ch ^ 0x20;
	return ch;
}
