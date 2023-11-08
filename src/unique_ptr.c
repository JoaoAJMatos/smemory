//
// Created by JoaoAJMatos on 05-11-2023.
//

/** C Includes */
#include <stdio.h>
#include <stdlib.h>

/** Lib Includes */
#include <smemory/unique_ptr.h>


/** Constructs a new unique_ptr */
unique_ptr_t *unique_ptr_make(void *ptr, destructor_t destructor) 
{
      unique_ptr_t *_unique_ptr = malloc(sizeof(unique_ptr_t));
      _unique_ptr->ptr = ptr;
      _unique_ptr->destructor = destructor;
      return _unique_ptr;
}


/** Moves ownership of a unique_ptr to another unique_ptr */
unique_ptr_t *unique_ptr_move(unique_ptr_t **source)
{
      if (source == NULL) return NULL;
      if (*source == NULL) return NULL;

      unique_ptr_t *_unique_ptr = malloc(sizeof(unique_ptr_t));
      if (_unique_ptr == NULL) return NULL;

      _unique_ptr->ptr = (*source)->ptr;
      _unique_ptr->destructor = (*source)->destructor;

      free(*source);
      *source = NULL;

      return _unique_ptr;
}


/** Destroys a unique_ptr */
void unique_ptr_destroy(unique_ptr_t **ptr)
{
      if (ptr == NULL) return;
      if (*ptr == NULL) return;

      if ((*ptr)->destructor != NULL) {
            (*ptr)->destructor((*ptr)->ptr);
      }

      free(*ptr);
      *ptr = NULL;
}


/** Gets the pointer from a unique_ptr */
void *unique_ptr_get(unique_ptr_t *ptr)
{
      if (ptr == NULL) return NULL;
      return ptr->ptr;
}


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
