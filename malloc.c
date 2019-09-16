#include "malloc.h"

void		*glob = NULL;

t_block		*call_space(size_t size)
{
  t_block	*tmp;
  t_block	*block;

  block = sbrk(0);
  block = sbrk(size + sizeof(t_block));
  if (block == (void *) - 1)
    return (NULL);

  block->size = size;
  block->next = NULL;
  block->free = 0;

  if (glob != NULL)
    {
      tmp = glob;
      while (tmp->next)
	{
	  tmp = tmp->next;
	}
      tmp->next = block;
    }
  else
    glob = block;
  
  return (block);
}

t_block		*search_block(size_t size)
{
  t_block	*first;

  first = glob;
  while (first)
    {
      if(first->free && first->size >= size)
	{
	  first->free = 0;

	  return(first);
	}
      first = first->next;
    }

  return (NULL);
}

void		cut_block(t_block  *free_one, size_t size)
{
  t_block	*other_block;

  other_block = (void *)free_one + sizeof(t_block) + (sizeof(char) *size);
  other_block->size = free_one->size - size - sizeof(t_block);
  other_block->next = free_one->next;
  other_block->free = 1;
  free_one->size = (void *)other_block - (void *)free_one + sizeof(t_block);
  free_one->next = other_block;
}

void		*malloc(size_t size)
{
  t_block	*block;

  if (size <= 0)
    return (NULL);
  if (glob != NULL)
    {
      block = search_block(size);
      if (block && block->size > size)
	cut_block(block, size);
      else if (!block)
	block = call_space(size);
    }
  else
    block = call_space(size);
  if (!block)
    return (NULL);

  return ((void *)block + sizeof(t_block));
}

void		free(void *pointer)
{
  t_block	*block;

  block = glob;
  if (!pointer)
    return ;

  while (block && pointer != block)
    {
      block = block->next;
    }

  if (!block)
    return ;

  block->free = 1;
}