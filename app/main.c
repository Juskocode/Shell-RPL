#include <stdio.h>
#include <string.h>

int main() {
  
  char input[100];

  printf("$ ");
  fflush(stdout);

  while (fgets(input, 100, stdin) != NULL) {
	input[strlen(input) - 1] = '\0';	
	printf("%s: not found\n", input);
	printf("$ "); 
  	fflush(stdout);
  }
  return 0;
}
