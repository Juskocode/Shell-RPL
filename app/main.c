#include <stdio.h>

int main() {
  
  printf("$ ");
  fflush(stdout);

  char input[100];
  if (fgets(input, 100, stdin) != NULL) {
	printf("$ %s: not found", input);
  }
  else {
	perror("$ invalid input");
  }
  return 0;
}
