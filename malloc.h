#ifndef __malloc__
#define __malloc__

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	*malloc(size_t size);
void	free(void *pointer);

typedef struct  s_block
{
  size_t        size;
  struct        s_block *next;
  int           free;
}               t_block;

#endif