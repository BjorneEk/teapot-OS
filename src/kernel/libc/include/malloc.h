#ifndef MALLOC_H
#define MALLOC_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "int.h"

#define NULL_POINTER ((void *) 0)
#define DYNAMIC_MEM_TOTAL_SIZE 0x10000 // 4K or 4096 b

/**
 *   Memory block descriptor node for dynamic memmory management
 *   implemented usiing a doubly linked list with the nunction malloc()
 **/
typedef struct mem_block {

	size_t size;  /**
                  *  size in bytes of the available space in a block
                  *  the total size is 16 bytes larger since this descriptor
                  *  is itself a part of the block
                  **/

	uint8_t is_allocated;  /**
                           *  if this block is allocated or not
                           **/

	struct mem_block * prev;  /**
                              *  previous block if there is one else NULL_POINTER;
                              *  previous block (used to merge blocks when they are freed)
                              **/

	struct mem_block * next;   /**
                              *  next block if there is one else NULL_POINTER;
                              **/
} mem_block_t;


#define BLOCK_DESCRIPTOR_SIZE sizeof(mem_block_t) // 16


/**
 *   @breif function that initializes dynammicaly allocated memory
 *
 *   sets the first element of the doubly linked list used to manage
 *   the dynamic memory in order to initialize the list.
 **/
void malloc_init();

/**
 *   @breif function that frees dynammicaly allocated memory
 *
 *   also tries to merge freed blocks with adjacent free memory blocks;
 **/
void free(void * mem);

/**
 *   @breif malloc function implemented using doubly linked list;
 *
 *   @see docs/ for examples;
 **/
void * malloc(size_t size);

#endif /* MALLOC_H */
