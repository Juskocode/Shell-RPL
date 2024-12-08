#include <stdio.h>
#include <string.h>

int main() {
  
  printf("$ ");
  fflush(stdout);

  char input[100];
  if (fgets(input, 100, stdin) != NULL) {
	input[strlen(input) - 1] = '\0';	
	printf("%s: not found\n", input);
  }
  else {
	perror("invalid input");
  }
  return 0;
}
