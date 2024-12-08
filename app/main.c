#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  
  char input[100];

  while (1) {
	
	printf("$ "); 
  	fflush(stdout);

	fgets(input, 100, stdin);	

	input[strlen(input) - 1] = '\0';	
	if (1) {	
		printf("%s: not found\n", input);
		printf("$ exit 0\n");	
		exit(0);
	}
  }
  return 0;
}
