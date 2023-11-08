//
// Description: Example of shared_ptr usage.
//

/** C Includes */
#include <stdio.h>
#include <stdlib.h>

/** Smart Ptr Lib */
#include <smemory/shared_ptr.h>


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
      printf("Product");
      free(product);
}

int main(void)
{
      // Create a shared_ptr
      shared_ptr *ptr1 = shared_ptr_make(product_make("Product 1", 100), product_destroy);

      // Copy the shared_ptr to another shared_ptr
      shared_ptr *ptr2 = shared_ptr_copy(ptr1);

      // Change the name
      ((product_t *)shared_ptr_get(ptr2))->name = "Product 2";

      // Print the product name
      printf("Ptr 2: %s\n", ((product_t *)shared_ptr_get(ptr2))->name);

      return 0;
}
