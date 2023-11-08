//
// Created by JoaoAJMatos on 06-11-2023.
//

/** Lib Includes */
#include <smemory/mempool.h>


/** Inits a mempool */
void mempool_init(mempool_t* mempool, size_t block_size, size_t initial_capacity)
{
      mempool->block_size = block_size;
      mempool->capacity = initial_capacity;
      mempool->blocks = malloc(sizeof(void*) * initial_capacity);
      mempool->count = 0;
      pthread_mutex_init(&mempool->mutex, NULL);
}


/** Destroys a mempool */
void mempool_destroy(mempool_t* mempool)
{
      for (size_t i = 0; i < mempool->count; i++) {
            free(mempool->blocks[i]);
      }

      free(mempool->blocks);
      pthread_mutex_destroy(&mempool->mutex);
}


/** Allocates a new block of memory */
void* mempool_alloc(mempool_t* mempool)
{
      pthread_mutex_lock(&mempool->mutex);

      /** No available blocks */
      if (mempool->count == 0) {
            void *block = malloc(mempool->block_size);
            pthread_mutex_unlock(&mempool->mutex);
            return block;
      }

      /** Get the last block */
      void *block = mempool->blocks[mempool->count - 1];
      mempool->count--;

      pthread_mutex_unlock(&mempool->mutex);
      return block;
}


/** Frees a block of memory */
void mempool_free(mempool_t* mempool, void* block)
{
      pthread_mutex_lock(&mempool->mutex);

      if (mempool->count < mempool->capacity) {
            mempool->blocks[mempool->count] = block;
            mempool->count++;
            pthread_mutex_unlock(&mempool->mutex);
      } else {
            /** Dynamically grow the mempool */
            size_t new_capacity = mempool->capacity * 2;
            void **new_blocks = realloc(mempool->blocks, sizeof(void*) * new_capacity);

            if (new_blocks == NULL) {
                  pthread_mutex_unlock(&mempool->mutex);
                  free(block);
                  return;
            }

            mempool->blocks = new_blocks;
            mempool->blocks[mempool->count] = block;
            mempool->count++;
            mempool->capacity = new_capacity;
            pthread_mutex_unlock(&mempool->mutex);
      }
}



