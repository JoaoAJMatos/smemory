# C smart_ptr

This library provides a "smart pointer" implementation for C.

## Features

- Unique pointers
- Shared pointers

## Installing

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
#include <smart_ptr.h>

#include "product.h"

int main(void) {
      // Create a unique pointer
      unique_ptr_t *product = unique_ptr_make(product_make(1, "Product 1", 1.99), product_destroy);

      // Use unique_ptr_get to access the pointer's data
      printf("Product id: %d\n", unique_ptr_get(product)->id);

      // Move ownership to another unique pointer
      // The original pointer can no longer be used
      unique_ptr_t *product2 = unique_ptr_move(product);

      printf("Product id: %d\n", unique_ptr_get(product2)->id);
      printf("Product id: %d\n", unique_ptr_get(product)->id); // This segfaults
}
```

### Shared pointers

```c
#include <stdio.h>
#include <smart_ptr.h>

#include "product.h"

int main(void) {
      // Create a shared_ptr 
      shared_ptr_t *product = shared_ptr_make(product_make(1, "Product 1", 1.99), product_destroy);

      // Create a copy of the shared_ptr
      shared_ptr_t *product2 = shared_ptr_copy(product);

      // Use shared_ptr_get to access the pointer's data
      printf("Product id: %d\n", shared_ptr_get(product)->id);
      printf("Product id: %d\n", shared_ptr_get(product2)->id);

      // Destroy the original shared_ptr
      shared_ptr_destroy(product);

      // The data is still accessible through the copy
      printf("Product id: %d\n", shared_ptr_get(product2)->id);

      // Destroy the copy
      shared_ptr_destroy(product2);

      // The data is no longer accessible
      printf("Product id: %d\n", shared_ptr_get(product2)->id); // This segfaults
}
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
