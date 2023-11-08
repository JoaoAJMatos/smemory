//
// Description: Example of shared_ptr usage.
//

/** C Includes */
#include <stdio.h>
#include <stdlib.h>

/** Smart Ptr Lib */
#include <smemory/unique_ptr.h>

typedef struct {
    char *name;
    int price;
} product_t;

product_t *product_make(char *name, int price)
{
    product_t *product = malloc(sizeof(product_t));
    product->name = name;
    product->price = price;
    return product;
}

void product_destroy(void *product)
{
      if (product == NULL) return;
      printf("Destroying product: %s\n", ((product_t *)product)->name);
      free(product);
}

int main(void) 
{
      // Create a unique_ptr
      unique_ptr *ptr1 = unique_ptr_make(product_make("Product 1", 100), product_destroy);

      // Move ownership of ptr1 to ptr2
      unique_ptr *ptr2 = unique_ptr_move(&ptr1);

      // Change the name
      ((product_t *)unique_ptr_get(ptr2))->name = "Product 2";

      // Print the product name
      printf("Ptr 2: %s\n", ((product_t *)unique_ptr_get(ptr2))->name);
      
      return 0;
}

