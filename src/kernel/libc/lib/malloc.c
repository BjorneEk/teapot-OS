
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/malloc.h"


static uint8_t mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static mem_block_t * mem_head;
static uint8_t has_been_initialized = false;

void malloc_init() {

	/**
	 *   initialize mem_head to a block the size of
	 *   the entire dynamic memory region minus the size of the node itself;
	 **/
	mem_head = (mem_block_t *) mem_area;
	mem_head->size = DYNAMIC_MEM_TOTAL_SIZE - BLOCK_DESCRIPTOR_SIZE;
	mem_head->next = NULL_POINTER;
	mem_head->prev = NULL_POINTER;

	/**
	 * make shure we dont initialize twice and lose data
	 **/
	has_been_initialized = true;
}

void * best_available_block(mem_block_t * mem_head, size_t size) {

	/**
	 *   initialize block to invalid results;
	 **/
	mem_block_t * best_block = (mem_block_t *) NULL_POINTER;
	size_t best_block_size = DYNAMIC_MEM_TOTAL_SIZE + 1;

	/**
	 *   start looking for the best (smallest unused) block at the head;
	 **/
	for (mem_block_t * c = mem_head; c != NULL_POINTER; c = c->next) {

		/**
		 *   check if it is not occupied, large enough and smaller
		 *   than the current best_block;
		 **/
		if ((!c->is_allocated) && (c->size >= (size + BLOCK_DESCRIPTOR_SIZE)) &&
			 (c->size <= best_block_size)) {
			best_block = c;
			best_block_size = c->size;
		}
	}
	return best_block;
}





void * malloc(size_t size) {

	/**
	 *   check if malloc has been initialized by setting the head of
	 *   the list, if not then initialize it
	 **/
	if(!has_been_initialized) malloc_init();

	/**
	 *   try to get best available memory block and check if one was found
	 *   if no block was found return NULL_POINTER
	 **/
	mem_block_t * best_avail_block = best_available_block(mem_head, size);

	if (best_avail_block == NULL_POINTER) return NULL_POINTER;


	/**
	 *   subtract total size of the block we are going to create from the free
	 *   block we found
	 **/
	best_avail_block->size = best_avail_block->size - size - BLOCK_DESCRIPTOR_SIZE;

	/**
	 *   create the new block after the one we found
	 *   descriptor_size myst be added since best_avail->size only represents
	 *   the size of the data and not the data and descriptor;
	 **/
	mem_block_t * allocated_block = (mem_block_t *)(((uint8_t *)best_avail_block)
																 + BLOCK_DESCRIPTOR_SIZE + best_avail_block->size);

	/**
	 *   connect up the allocated block to the doubly linked list
	 *   inbetween best_avail_block and best_avail_block->next or if
	 *   best_avail_block->next = NULL_POINTER simply after best_avail_block
	 **/
	allocated_block->size = size;
	allocated_block->is_allocated = true;
	allocated_block->prev = best_avail_block;
	allocated_block->next = best_avail_block->next;

	if (best_avail_block->next != NULL_POINTER)
		allocated_block->next->prev = allocated_block;

	best_avail_block->next = allocated_block;

	return (void *) allocated_block;
}

void * merge_next(mem_block_t * block) {
	/**
	 *   check wheter a merge is possible, of not return block
	 */
	if (block->next->is_allocated || block->next == NULL_POINTER) return block;

	/**
	 *   merge block with block->next by adding the size of next and the
	 *   descriptor aswell as connecting the pointers and removing next;
	 **/
	block->size += (block->next->size + BLOCK_DESCRIPTOR_SIZE);
	block->next = block->next->next;

	if (block->next != NULL_POINTER) block->next->prev = block;

	return block;
}
void * merge_prev(mem_block_t * block) {
	/**
	 *   check wheter a merge is possible, of not return block
	 */
	if (block->prev->is_allocated || block->prev == NULL_POINTER) return block;

	/**
	*   merge block with block->prev by adding the size of prev and the
	*   descriptor aswell as connecting the pointers and removing next;
	**/
	mem_block_t * prev = block->prev;

	prev->size += (block->size + BLOCK_DESCRIPTOR_SIZE);
	prev->next = block->next;

	if (block->next != NULL_POINTER) block->next->prev = prev;

	return prev;
}

void free(void * mem) {

	if (mem == NULL_POINTER) return;

	/**
	 *   get the mem_block_t descriptor by subtracting the descriptor_size
	 *   from the pointer;
	 **/
	mem_block_t * block = (mem_block_t *) (((uint8_t *) mem) - BLOCK_DESCRIPTOR_SIZE);
	if (block == NULL_POINTER) return;

	/**
	 *   set as unused;
	 **/
	block->is_allocated = false;

	/**
	 *   try mergeing into possible adjacent free nodes;
	 **/
	block = merge_next(block);
	merge_prev(block);
}
