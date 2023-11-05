//
// Description: Example of shared_ptr usage.
//

/** C Includes */
#include <stdio.h>
#include <stdlib.h>

/** Smart Ptr Lib */
#include <smart_ptr.h>


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
      free(product);
}

int main(void)
{
      // Create a unique_ptr
      unique_ptr_t *ptr1 = unique_ptr_make(product_make("Product 1", 100), product_destroy);

      // Move the unique_ptr to another unique_ptr
      unique_ptr_t *ptr2 = unique_ptr_move(ptr1);

      // Print the product name
      printf("Ptr 2: %s\n", ((product_t *)unique_ptr_get(ptr2))->name);

      // Destroy the unique_ptr
      unique_ptr_destroy(ptr2);

      // Print the product name of ptr1
      printf("Ptr 1: %s\n", ((product_t *)unique_ptr_get(ptr1))->name); // Segmentation fault

      return 0;
}