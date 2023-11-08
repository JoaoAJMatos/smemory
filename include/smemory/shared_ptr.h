/**
 * @file shared_ptr.h
 * @brief Shared Pointer
 *          
 * @date 05-11-2023
 * @author JoaoAJMatos
 */

#ifndef SMART_PTR_SHARED_PTR_H
#define SMART_PTR_SHARED_PTR_H

#include "types.h"

/////////////////////////////////////////////////////////////////////////////////////

#define shared_ptr __attribute__((cleanup(shared_ptr_destroy))) shared_ptr_t

/////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Shared pointer structure
 * 
 * @details Shared pointer structure is a smart pointer that retains shared
 *          ownership of an object through a pointer. Several shared_ptr objects
 *          may own the same object. The object is destroyed and its memory
 *          deallocated when either of the following happens:
 * 
 *          - the last remaining shared_ptr owning the object is destroyed
 *          - the last remaining shared_ptr owning the object is assigned another
 *          pointer via operator= or reset().
 * 
 *          The object is destroyed using delete-expression or a custom deleter
 *          that is supplied to shared_ptr during construction.
 * 
 *          The default deleter for shared_ptr is a function object that calls
 *          delete on the pointer to the object.
 */
typedef struct {
    void *ptr;
    destructor_t destructor;
    int *ref_count;
} shared_ptr_t;

/////////////////////////////////////////////////////////////////////////////////////

/** CREATION FUNCTIONS */

/**
 * @brief Creates a new shared pointer
 * 
 * @param ptr Pointer to the object to manage
 * @param destructor Pointer to the destructor function
 * @return shared_ptr_t* Pointer to the new shared pointer
 */
shared_ptr_t *shared_ptr_make(void *ptr, destructor_t destructor);

/////////////////////////////////////////////////////////////////////////////////////

/** COPY AND MOVE FUNCTIONS */

/**
 * @brief Copies a shared pointer
 * 
 * @details Increases the reference count and creates a new reference to the
 *          shared pointer
 * 
 * @param ptr Pointer to the shared pointer to copy
 * @return shared_ptr_t* Pointer to the new shared pointer
 */
shared_ptr_t *shared_ptr_copy(shared_ptr_t *ptr);

/**
 * @brief Moves a shared pointer
 * 
 * @details Moves the ownership from one shared pointer to another
 * 
 * @param ptr Pointer to the shared pointer to move
 * @return shared_ptr_t* Pointer to the new shared pointer
 */
shared_ptr_t *shared_ptr_move(shared_ptr_t *ptr);

/////////////////////////////////////////////////////////////////////////////////////

/** DESTRUCTION FUNCTIONS */

/**
 * @brief Destroys a shared pointer
 * 
 * @param ptr Pointer to the shared pointer to destroy
 */
void shared_ptr_destroy(shared_ptr_t **ptr);

/////////////////////////////////////////////////////////////////////////////////////

/** ACCESSOR FUNCTIONS */

/**
 * @brief Gets the pointer to the object managed by the shared pointer
 * 
 * @param ptr Pointer to the shared pointer
 * @return void* Pointer to the object managed by the shared pointer
 */
void *shared_ptr_get(shared_ptr_t *ptr);

/////////////////////////////////////////////////////////////////////////////////////

/** REFERENCE COUNT FUNCTIONS */

/**
 * @brief Gets the reference count of the shared pointer
 * 
 * @param ptr Pointer to the shared pointer
 * @return int Reference count of the shared pointer
 */
int shared_ptr_get_ref_count(shared_ptr_t *ptr);

/**
 * @brief Increments the reference count of the shared pointer
 * 
 * @param ptr Pointer to the shared pointer
 */
void shared_ptr_increment_ref_count(shared_ptr_t *ptr);

/**
 * @brief Decrements the reference count of the shared pointer
 * 
 * @param ptr Pointer to the shared pointer
 */
void shared_ptr_decrement_ref_count(shared_ptr_t *ptr);

/////////////////////////////////////////////////////////////////////////////////////

#endif // SMART_PTR_SHARED_PTR_H


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
