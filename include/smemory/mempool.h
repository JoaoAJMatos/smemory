/**
 * @file mempool.h
 * @brief Memory pool
 *          
 * @date 05-11-2023
 * @author JoaoAJMatos
 */

#ifndef SMEMORY_UNIQUE_PTR_H
#define SMEMORY_UNIQUE_PTR_H

#include <stdlib.h>
#include <pthread.h>

/////////////////////////////////////////////////////////////////////////////////////

typedef struct mempool {
      size_t block_size;
      size_t capacity;
      void** blocks;
      unsigned int count;
      pthread_mutex_t mutex;
} mempool_t;

/////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes a memory pool
 *
 * @param mempool Pointer to the memory pool
 * @param block_size Size of each block
 * @param initial_capacity Number of blocks
 */
void mempool_init(mempool_t* mempool, size_t block_size, size_t initial_capacity);


/**
 * @brief Cleans up a memory pool
 *
 * @param mempool Pointer to the memory pool
 */
void mempool_destroy(mempool_t* mempool);


/**
 * @brief Allocates a block of memory from the memory pool
 *
 * @param mempool Pointer to the memory pool
 * @return void* Pointer to the allocated block
 */
void* mempool_alloc(mempool_t* mempool);


/**
 * @brief Frees a block of memory from the memory pool
 *
 * @param mempool Pointer to the memory pool
 * @param ptr Pointer to the block to free
 */
void mempool_free(mempool_t* mempool, void* ptr);


#endif //SMEMORY_UNIQUE_PTR_H

// MIT License
// 
// Copyright (c) 2023 João Matos
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
