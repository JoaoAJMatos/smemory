//
// Description: Example of shared_ptr usage.
//

/** C Includes */
#include <stdio.h>
#include <stdlib.h>

/** Smart Ptr Lib */
#include <smart_ptr.h>


// Define a product type
typedef struct {
    char *name;
    int price;
} product_t;

// Define a product constructor
product_t *product_make(char *name, int price)
{
    product_t *product = malloc(sizeof(product_t));
    product->name = name;
    product->price = price;
    return product;
}

// Define a product destructor
void product_destroy(void *product)
{
    free(product);
}

int main(void)
{
      // Create a shared_ptr
      shared_ptr_t *ptr1 = shared_ptr_make(product_make("Product 1", 100), product_destroy);

      // Copy the shared_ptr to another shared_ptr
      shared_ptr_t *ptr2 = shared_ptr_copy(ptr1);

      // Print the product name
      printf("Ptr 1: %s\n", ((product_t *)shared_ptr_get(ptr1))->name);
      printf("Ptr 2: %s\n", ((product_t *)shared_ptr_get(ptr2))->name);

      // Destroy the shared_ptr
      shared_ptr_destroy(ptr1);

      // Print the product name of ptr2
      printf("Ptr 2: %s\n", ((product_t *)shared_ptr_get(ptr2))->name);

      // Destroy the shared_ptr
      shared_ptr_destroy(ptr2);

      return 0;
}