//
// Created by JoaoAJMatos on 05-11-2023.
//

/** C Includes */
#include <stdio.h>
#include <stdlib.h>

/** Local Includes */
#include "../include/smart_ptr.h"


/////////////////////////////////////////////////////////////////////////////////////

/** Constructs a new unique_ptr */
unique_ptr_t *unique_ptr_make(void *ptr, destructor_t destructor) 
{
      unique_ptr_t *unique_ptr = malloc(sizeof(unique_ptr_t));
      unique_ptr->ptr = ptr;
      unique_ptr->destructor = destructor;
      return unique_ptr;
}


/** Constructs a new shared_ptr */
shared_ptr_t *shared_ptr_make(void *ptr, destructor_t destructor)
{
      shared_ptr_t *shared_ptr = malloc(sizeof(shared_ptr_t));
      shared_ptr->ptr = ptr;
      shared_ptr->destructor = destructor;
      shared_ptr->ref_count = malloc(sizeof(int));
      *shared_ptr->ref_count = 1;
      return shared_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////

/** Moves ownership of a unique_ptr to another unique_ptr */
unique_ptr_t *unique_ptr_move(unique_ptr_t *source)
{
      if (source == NULL) return NULL;

      unique_ptr_t *unique_ptr = malloc(sizeof(unique_ptr_t));
      if (unique_ptr == NULL) return NULL;

      unique_ptr->ptr = source->ptr;
      unique_ptr->destructor = source->destructor;

      free(source);
      return unique_ptr;
}


/** Copies a shared pointer and increments the reference count */
shared_ptr_t *shared_ptr_copy(shared_ptr_t *source)
{
      if (source == NULL) return NULL;

      shared_ptr_t *shared_ptr = malloc(sizeof(shared_ptr_t));
      if (shared_ptr == NULL) return NULL;

      shared_ptr->ptr = source->ptr;
      shared_ptr->destructor = source->destructor;
      shared_ptr->ref_count = source->ref_count;
      shared_ptr_increment_ref_count(source);

      return shared_ptr;
}


/** Moves ownership of a shared_ptr to another shared_ptr */
shared_ptr_t *shared_ptr_move(shared_ptr_t *ptr)
{
      if (ptr == NULL) return NULL;

      shared_ptr_t *shared_ptr = malloc(sizeof(shared_ptr_t));
      if (shared_ptr == NULL) return NULL;

      shared_ptr->ptr = ptr->ptr;
      shared_ptr->destructor = ptr->destructor;
      shared_ptr->ref_count = ptr->ref_count;

      free(ptr);
      return shared_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////

/** Destroys a unique_ptr */
void unique_ptr_destroy(unique_ptr_t *ptr)
{
      if (ptr == NULL) return;
      if (ptr->destructor != NULL) ptr->destructor(ptr->ptr);
      free(ptr);
}

/** Destroys a shared_ptr */
void shared_ptr_destroy(shared_ptr_t *ptr)
{
      if (ptr == NULL) return;
      shared_ptr_decrement_ref_count(ptr);

      if (shared_ptr_get_ref_count(ptr) <= 0) {
            if (ptr->destructor != NULL) ptr->destructor(ptr->ptr);
      }

      free(ptr);
}

/////////////////////////////////////////////////////////////////////////////////////

/** Gets the pointer from a unique_ptr */
void *unique_ptr_get(unique_ptr_t *ptr)
{
      if (ptr == NULL) return NULL;
      return ptr->ptr;
}

/** Gets the pointer from a shared_ptr */
void *shared_ptr_get(shared_ptr_t *ptr)
{
      if (ptr == NULL) return NULL;
      return ptr->ptr;
}

/////////////////////////////////////////////////////////////////////////////////////

/** Gets the reference count from a shared_ptr */
inline int shared_ptr_get_ref_count(shared_ptr_t *ptr)
{
      if (ptr == NULL) return -1;
      return *ptr->ref_count;
}

/** Increments the ref count of a shared_ptr */
inline void shared_ptr_increment_ref_count(shared_ptr_t *ptr)
{
      if (ptr == NULL) return;
      *ptr->ref_count++;
}

/** Decrements the ref count of a shared_ptr */
void shared_ptr_decrement_ref_count(shared_ptr_t *ptr)
{
      if (ptr == NULL) return;
      *ptr->ref_count--;
}

/////////////////////////////////////////////////////////////////////////////////////

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