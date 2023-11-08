# smemory

The `smemory` library provides smart pointer structures and functions
for managing memory in a safe and efficient way in C.

Smart pointers are objects that store pointers to dynamically allocated (heap) objects. They behave much like built-in C pointers except that they automatically delete the object pointed to at the appropriate time.

## Features

- Unique pointers
- Shared pointers
- Memory pool

## Download

#### Clone the repository

```bash
git clone https://www.github.com/JoaoAJMatos/smart_ptr.git
```

#### Build the library

```bash
cd smart_ptr
./build.sh
```

#### Install the library (optional)

```bash
cd build
make install
```

## Usage

Suppose we have the following struct with the following functions:
      
```c
typedef struct {
      int id;
      char *name;
      float price;
} product_t;

product_t *product_make(int id, char *name, float price) {
    product_t *product = malloc(sizeof(product_t));

    product->id = id;
    product->name = name;
    product->price = price;

    return product;
}

void product_destroy(void *product) {
    free(product);
}
```

### Unique pointers

```c
#include <stdio.h>
#include <smart_ptr/unique_ptr.h>

#include "product.h"

int main(void) {
      // Create a unique pointer
      unique_ptr *product = unique_ptr_make(product_make(1, "Product 1", 1.99), product_destroy);

      // Use unique_ptr_get to access the pointer's data
      printf("Product id: %d\n", unique_ptr_get(product)->id);

      // Move ownership to another unique pointer
      // The original pointer can no longer be used
      unique_ptr *product2 = unique_ptr_move(product);

      printf("Product id: %d\n", unique_ptr_get(product2)->id);
      printf("Product id: %d\n", unique_ptr_get(product)->id); // This segfaults

      // All memory is automatically dealocated once the smart pointers
      // go out of scope
}
```

### Shared pointers

```c
#include <stdio.h>
#include <smart_ptr/shared_ptr.h>

#include "product.h"

int main(void) {
      // Create a shared_ptr 
      shared_ptr *product = shared_ptr_make(product_make(1, "Product 1", 1.99), product_destroy);

      // Create a copy of the shared_ptr
      shared_ptr *product2 = shared_ptr_copy(product);

      // Use shared_ptr_get to access the pointer's data
      printf("Product id: %d\n", shared_ptr_get(product)->id);
      printf("Product id: %d\n", shared_ptr_get(product2)->id);

      // The data is still accessible through the copy
      printf("Product id: %d\n", shared_ptr_get(product2)->id);

      // All memory is automatically dealocated once the smart pointers
      // go out of scope
}
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
