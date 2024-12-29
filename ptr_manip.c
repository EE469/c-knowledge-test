#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void pointer_arithmetic(void);
void pointer_casting(void);
void pointer_indexing(void);
void pointer_increment(void);
void uninitialized_pointers(void);

int main(int argc, char **argv) {
    printf(" * Pointer Manipulation Demo * \n\n");
    
    pointer_arithmetic();
    pointer_casting();
    pointer_indexing();
    pointer_increment();
    uninitialized_pointers();
    
    return 0;
}

void pointer_arithmetic(void) {
    printf("1. Pointer Arithmetic:\n");
    
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    /*
     *  Basic pointer arithmetic
     *  +---+---+---+---+---+
     *  | 10| 20| 30| 40| 50|
     *  +---+---+---+---+---+
     *    ^
     *    ptr
     */
    printf("\tOriginal value: *ptr = %d\n", *ptr);
    
    /*  (void *) is a generic pointer type
     *  
     *  +----------------+
     *  |    void *      |  <- Type-agnostic container
     *  +----------------+
     *  
     *  Why?:
     *  ┌─────────────────────────────────┐
     *  │ * Ensures code portability      │
     *  │ * Prevents pointer arithmetic   │
     *  │ * Forces explicit type casting  │
     *  └─────────────────────────────────┘
     */
    printf("\tAddress: ptr = %p\n", (void *)ptr);

    /*  Adding to pointer
     *  
     *  Before:
     *  +---+---+---+---+---+
     *  | 10| 20| 30| 40| 50|
     *  +---+---+---+---+---+
     *    ^
     *    ptr
     *  
     *  After ptr + 2:
     *  +---+---+---+---+---+
     *  | 10| 20| 30| 40| 50|
     *  +---+---+---+---+---+
     *            ^
     *            ptr
     *  
     *  Note: Compiler automatically adjusts offset based on int size!
     */
    ptr = ptr + 2;  
    printf("\tAfter ptr + 2: *ptr = %d\n", *ptr);
    printf("\tNew address: ptr = %p\n", (void*)ptr);
    
    /*  Subtracting from pointer
     *  
     *  +---+---+---+---+---+
     *  | 10| 20| 30| 40| 50|
     *  +---+---+---+---+---+
     *        ^
     *        ptr (after ptr - 1)
     */
    ptr = ptr - 1;
    printf("\tAfter ptr - 1: *ptr = %d\n", *ptr);
    
    /*  Pointer difference
     *  
     *  +---+---+---+---+---+
     *  | 10| 20| 30| 40| 50|
     *  +---+---+---+---+---+
     *    ^           ^
     *    start       end
     *    |___________|
     *     4 elements
     *  
     *  Note: Difference is in elements, not bytes!
     */
    int *start = arr;
    int *end = arr + 4;
    int diff = end - start;
    printf("\tPointer difference: end - start = %d elements\n\n", diff);
}

void pointer_casting(void) {
    printf("2. Pointer Casting:\n");
    
    int value = 0x12345678;
    int *int_ptr = &value;
    
    /*  Cast to different pointer types
     *  
     *  Memory Layout of 0x12345678:
     *  +------+------+------+------+
     *  | 0x78 | 0x56 | 0x34 | 0x12 |  <- Little Endian
     *  +------+------+------+------+
     *  ^      ^      ^      ^
     *  |      |      |      |
     *  char_ptr[0]   |      char_ptr[3]
     *         char_ptr[1]   char_ptr[2]
     */
    char *char_ptr = (char*)int_ptr;
    uint16_t *short_ptr = (uint16_t*)int_ptr;
    
    /*  Byte-by-byte access
     *  
     *  Different pointer views of same memory:
     *  
     *  As int:
     *  +--------------------------------+
     *  |           0x12345678           |  <- int_ptr
     *  +--------------------------------+
     *  
     *  As bytes:
     *  +------+------+------+------+
     *  | 0x78 | 0x56 | 0x34 | 0x12 |  <- char_ptr[0..3]
     *  +------+------+------+------+
     *  
     *  As uint16_t:
     *  +---------------+---------------+
     *  |     0x5678    |    0x1234     |  <- short_ptr[0..1]
     *  +---------------+---------------+
     */
    printf("\tOriginal value: 0x%08X\n", value);
    printf("\tByte access (little endian):\n");
    for(int i = 0; i < 4; i++) {
        printf("\tByte %d: 0x%02X\n", i, (unsigned char)char_ptr[i]);
    }
    
    /*  Integer manipulation through casting */
    uintptr_t addr = (uintptr_t)int_ptr;
    printf("\tAddress as integer: %lx\n", addr);
    int_ptr = (int*)addr;  // Cast back to pointer
    printf("\tValue after casting back: 0x%08X\n\n", *int_ptr);
}


void pointer_indexing(void) {
   printf("3. Pointer Indexing:\n");
   
   int matrix[3][4] = {
       {1, 2, 3, 4},
       {5, 6, 7, 8},
       {9, 10, 11, 12}
   };
   
   int *ptr = &matrix[0][0];
   
   /*  Matrix Memory Layout:
    *  
    *  matrix[row][col]:
    *  
    *       col0   col1   col2   col3
    *       +------+------+------+------+
    * row0  |  1   |  2   |  3   |  4   |
    *       +------+------+------+------+
    * row1  |  5   |  6   |  7   |  8   |
    *       +------+------+------+------+
    * row2  |  9   |  10  |  11  |  12  |
    *       +------+------+------+------+
    *
    *  Linear Memory View (ptr[index]):
    *  
    *  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
    *  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | 10  | 11  | 12   |
    *  +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
    *  ^     ^     ^     ^     ^     ^     ^     ^     ^     ^     ^      ^
    *  |     |     |     |     |     |     |     |     |     |     |      |
    *  0     1     2     3     4     5     6     7     8     9     10     11
    *  
    *  Access Methods:
    *  +-------------------------------------------+
    *  | 1. matrix[1][2] = 7                       |
    *  |    row1 -> offset 4                       |
    *  |    col2 -> offset 2                       |
    *  |    +-----+-----+-----+-----+              |
    *  |    |  5  |  6  |  7  |  8  |              |
    *  |    +-----+-----+-----+-----+              |
    *  |                  ^                        |
    *  +-------------------------------------------+
    *  
    *  +-------------------------------------------+
    *  | 2. *(ptr + 1*4 + 2) = 7                   |
    *  |    Formula: base + (row * cols) + col     |
    *  |    = ptr + (1 * 4) + 2                    |
    *  |    = ptr + 4 + 2                          |
    *  |    = ptr + 6                              |
    *  +-------------------------------------------+
    *  
    *  +-------------------------------------------+
    *  | 3. ptr[6] = 7                             |
    *  |    Direct linear access:                  |
    *  |    +---+---+---+---+---+---+->7+---+      |
    *  |    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |      |
    *  |    +---+---+---+---+---+---+---+---+      |
    *  +-------------------------------------------+
    */

   printf("\tUsing array indexing: matrix[1][2] = %d\n", matrix[1][2]);
   printf("\tUsing pointer arithmetic: *(ptr + 1*4 + 2) = %d\n", *(ptr + 1*4 + 2));
   printf("\tUsing linear indexing: ptr[6] = %d\n\n", ptr[6]);
}

void pointer_increment(void) {
    printf("4. Pointer Increment/Decrement:\n");
    
    double arr[] = {1.1, 2.2, 3.3, 4.4};
    double *ptr = arr;
    
    // Pre-increment
    printf("\tInitial: *ptr = %.1f\n", *ptr);
    printf("\tPre-increment: *++ptr = %.1f\n", *++ptr);
    
    // Post-increment
    printf("\tPost-increment: *ptr++ = %.1f\n", *ptr++);
    printf("\tAfter post-increment: *ptr = %.1f\n", *ptr);
    
    // Pre-decrement
    printf("\tPre-decrement: *--ptr = %.1f\n", *--ptr);
    
    // Post-decrement
    printf("\tPost-decrement: *ptr-- = %.1f\n", *ptr--);
    printf("\tAfter post-decrement: *ptr = %.1f\n\n", *ptr);
}

void uninitialized_pointers(void) {
    printf("5. Uninitialized Pointers (Dangerous!):\n");

    int *dangerous_ptr;  // Could point anywhere in memory
    // DON'T do this! Will show random address can point to 
    // anywhere.
    printf("\tDangerous: %p\n", (void*)dangerous_ptr);  
    
    int *ptr_array[3];  // Array of uninitialized pointers
    printf("2. Multiple uninitialized pointers in array:\n");
    for (int i = 0; i < 3; i++) {
        printf("\tptr_array[%d] points to: %p\n", i, (void*)ptr_array[i]);
    }
    printf("\tNOTE: Each contains random garbage address\n\n");

    void (*func_ptr)();  // Uninitialized function pointer
    printf("5. Uninitialized function pointer:\n");
    printf("   Points to: %p\n", (void*)func_ptr);
    printf("   WARNING: Calling this would jump to random memory!\n\n");

    // Safe initialization examples
    int *safe_ptr1 = NULL;  // Explicitly set to NULL
    int *safe_ptr2 = malloc(sizeof(int));  // Dynamically allocated
    
    printf("\tSafe pointer (NULL): %p\n", (void*)safe_ptr1);
    printf("\tSafe pointer (malloc): %p\n", (void*)safe_ptr2);
    
    // Cleanup
    free(safe_ptr2);
}
