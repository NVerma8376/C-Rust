#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int countdown(num){
  if (num == 0) {
    printf("%d\n", num);
    return 0 ;
  }
  printf("%d\n",num);
  countdown(num-1);
}

int countup(start, end){
  if (start == end) {
    printf("%d\n",end);
    return 0;
  }
  printf("%d\n", start);
  countup(start+1, end);
}

int main(int argc, char *argv[])
{
  countdown(4);
  printf("\n");
  countup(0,4);
  return 0;
}
