/**
 * @file smart_ptr.h
 * @brief Smart pointer library
 * 
 * @details Smart pointer library provides smart pointer structures and functions
 *          for managing memory in a safe and efficient way.
 * 
 *          Smart pointers are objects that store pointers to dynamically allocated
 *          (heap) objects. They behave much like built-in C pointers except that
 *          they automatically delete the object pointed to at the appropriate time.
 * 
 *          Smart pointers are usually implemented using templates. The C language
 *          does not provide templates, but they can be implemented using void
 *          pointers and function pointers.
 *          
 * @date 05-11-2023
 * @author JoaoAJMatos
 */

#ifndef SMART_POINTER_H
#define SMART_POINTER_H

/////////////////////////////////////////////////////////////////////////////////////

/** Destructor ffunction type */
typedef void (*destructor_t)(void *);

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
typedef struct shared_ptr {
    void *ptr;
    destructor_t destructor;
    int *ref_count;
} shared_ptr_t;

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
 * @brief Copies a unique pointer
 * 
 * @details Moves the ownership from one unique pointer to another
 * 
 * @param source Pointer to the unique pointer to copy
 * @return unique_ptr_t* Pointer to the new unique pointer
 */
unique_ptr_t *unique_ptr_move(unique_ptr_t *source);

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
 * @brief Destroys a unique pointer
 * 
 * @param ptr Pointer to the unique pointer to destroy
 */
void unique_ptr_destroy(unique_ptr_t *ptr);

/**
 * @brief Destroys a shared pointer
 * 
 * @param ptr Pointer to the shared pointer to destroy
 */
void shared_ptr_destroy(shared_ptr_t *ptr);

/////////////////////////////////////////////////////////////////////////////////////

/** ACCESSOR FUNCTIONS */

/**
 * @brief Gets the pointer to the object managed by the unique pointer
 * 
 * @param ptr Pointer to the unique pointer
 * @return void* Pointer to the object managed by the unique pointer
 */
void *unique_ptr_get(unique_ptr_t *ptr);

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

#endif // SMART_POINTER_H


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