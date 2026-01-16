#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "nanoshell.h"
#include <sys/wait.h>
#include <string.h>
int main(void){
	char line[TAILLE_LIGNE] = {0};
	char* av[] = {"ls", NULL};
	//char* env[] = {NULL};
	int pid = 0;

	while (1) {
		printf("?>");
		fgets(line, TAILLE_LIGNE, stdin);
		line[strlen(line) - 1] = 0;
		if (strcmp(line,"exit") == 0)
			{
			exit(0);
		}
		pid = fork();
		if (pid == 0) {
			execvp(line, av);
			exit(-1);
		}
	waitpid(pid, NULL, 0);
	}
	return 0;
}

