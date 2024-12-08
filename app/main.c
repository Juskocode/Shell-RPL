#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ft_strscpy(char *src, char *dst, int n) {
	char *srcs = src + n;
	strcpy(dst, srcs);

}

int main() {
  
  char input[100];

  while (1) {
	
	printf("$ "); 
  	fflush(stdout);

	fgets(input, 100, stdin);	

	input[strlen(input) - 1] = '\0';	
	if (!strcmp(input, "exit 0")) {	
		exit(0);
	}
	else if (!strncmp(input, "echo ", 5)) {
		char echo[95];
		ft_strscpy(input, echo, 5);
		printf("%s\n", echo);
	}
	else {
		printf("%s: not found\n", input);
	}
  }
  return 0;
}
