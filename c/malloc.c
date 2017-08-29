#include <stdio.h>
#include <unistd.h>

int main()
{
  int *p = NULL;
  size_t s1 = 6*1024*1024*1024;
  printf("s1 : %llu\n", s1);
  p = malloc(s1); 
  if(p)
  {
      printf("6GB memory allocated %llu\n", s1);
  }
  else
  {
      printf("6GB memory NOT allocated\n");
  }

  int *q = NULL;
  size_t s2 = 9*1024*1024*1024;
  printf("s2 : %llu\n", s2);
  q = malloc(s2); 
  if(q)
  {
      printf("9GB memory allocated, %llu\n", s2);
  }
  else
  {
      printf("9GB memory NOT allocated\n");
  }

  int *r = NULL;
  size_t s3 = 12*1024*1024*1024;
  printf("s3 : %llu\n", s3);
  r  = malloc(s3); 
  if(r)
  {
      printf("12GB memory allocated, %llu\n", s3);
  }
  else
  {
      printf("12GB memory NOT allocated\n");
  }

  getchar();
}

