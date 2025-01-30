#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char user[100];
  printf("your turn: ");
  scanf("%s", user);
  printf("%s\n", user);
  if(strcmp(user, "hello")==0){
    printf("hi\n");
  }
  return 0;
}
