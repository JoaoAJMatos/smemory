/**
 * @file unique_ptr.h
 * @brief Unique pointer
 *          
 * @date 05-11-2023
 * @author JoaoAJMatos
 */

#ifndef SMART_PTR_UNIQUE_PTR_H
#define SMART_PTR_UNIQUE_PTR_H

#include "types.h"

/////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Unique pointer structure
 * 
 * @details Unique pointer structure is a smart pointer that owns and manages
 *          another object through a pointer and disposes of that object when
 *          the unique pointer goes out of scope. The object is disposed of,
 *          using the associated deleter when either of the following happens:
 * 
 *          - the managing unique pointer object is destroyed
 *          - the managing unique pointer object is assigned another pointer via
 *          operator= or reset().
 * 
 *          The object is destroyed using delete-expression or a custom
 *          deleter that is supplied to unique_ptr during construction.
 * 
 *          The default deleter for unique_ptr is a function object that calls
 *          delete on the pointer to the object.
 */
typedef struct unique_ptr {
    void *ptr;
    destructor_t destructor;
} unique_ptr_t;

/////////////////////////////////////////////////////////////////////////////////////

/** CREATION FUNCTIONS */

/**
 * @brief Creates a new unique pointer
 * 
 * @param ptr Pointer to the object to manage
 * @param destructor Pointer to the destructor function
 * @return unique_ptr_t* Pointer to the new unique pointer
 */
unique_ptr_t *unique_ptr_make(void *ptr, destructor_t destructor);


/////////////////////////////////////////////////////////////////////////////////////

/** COPY AND MOVE FUNCTIONS */

/**
 * @brief Copies a unique pointer
 * 
 * @details Moves the ownership from one unique pointer to another
 * 
 * @param source Pointer to the unique pointer to copy
 * @return unique_ptr_t* Pointer to the new unique pointer
 */
unique_ptr_t *unique_ptr_move(unique_ptr_t *source);

/////////////////////////////////////////////////////////////////////////////////////

/** DESTRUCTION FUNCTIONS */

/**
 * @brief Destroys a unique pointer
 * 
 * @param ptr Pointer to the unique pointer to destroy
 */
void unique_ptr_destroy(unique_ptr_t *ptr);

/////////////////////////////////////////////////////////////////////////////////////

/** ACCESSOR FUNCTIONS */

/**
 * @brief Gets the pointer to the object managed by the unique pointer
 * 
 * @param ptr Pointer to the unique pointer
 * @return void* Pointer to the object managed by the unique pointer
 */
void *unique_ptr_get(unique_ptr_t *ptr);

/////////////////////////////////////////////////////////////////////////////////////

#endif // SMART_PTR_UNIQUE_PTR_H


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