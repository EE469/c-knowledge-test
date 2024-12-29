#include <stdio.h>
#include <string.h>

void basic_overflow(void) {
    printf("\n1. Basic Stack Buffer Overflow:\n");
    printf("------------------------------\n");

    /*
     * Stack Memory Layout (grows downward):
     *
     * Before overflow:
     *
     * High Address
     *     ┌──────────────┐
     *     │ guard = 'X'  │ <- Will be corrupted
     *     ├──────────────┤
     *     │ buffer[4]    │ 
     *     │ buffer[3]    │
     *     │ buffer[2]    │ <- 5-char buffer
     *     │ buffer[1]    │
     *     │ buffer[0]    │
     *     └──────────────┘
     * Low Address
     */
    
    char buffer[5];  // Can hold 4 chars + null terminator
    char guard = 'X';  // Variable right after buffer in memory
    
    printf("Before overflow:\n");
    printf("Guard value: %c\n", guard);
    
    // Overflow happens here!
    strcpy(buffer, "123456");  // Writing 6 chars + null into 5-char buffer
    
    /*
     * After overflow:
     *
     * High Address
     *     ┌──────────────┐
     *     │ guard = '6'  │ <- Corrupted!
     *     ├──────────────┤
     *     │ '5'          │ 
     *     │ '4'          │
     *     │ '3'          │ <- Buffer overflow
     *     │ '2'          │
     *     │ '1'          │
     *     └──────────────┘
     * Low Address
     */
    
    printf("After overflow:\n");
    printf("Guard value: %c\n", guard);
}


// Similar setting as above but a different
// type used to show overflows in structs.
void array_overflow(void) {
    printf("\n2. Array Buffer Overflow:\n");
    printf("------------------------\n");
    
    // Define arrays in a struct.
    // Elements of structs are always placed
    // together.
    struct {
        int nums1[3];
        int nums2[2];
    } arrays = {
        .nums1 = {0, 0, 0},
        .nums2 = {111, 222}
    };

    printf("Before overflow:\n");
    printf("nums2: [%d, %d]\n", arrays.nums2[0], arrays.nums2[1]);

    // Overflow nums1 
    printf("\nWriting values: ");
    for(int i = 0; i < 5; i++) {
        arrays.nums1[i] = i * 100;
        printf("%d ", i * 100);
    }
    printf("\n");

    printf("\nAfter overflow:\n");
    printf("nums2: [%d, %d]\n", arrays.nums2[0], arrays.nums2[1]);
}


int main(void) {
    printf("Stack Buffer Overflows\n");

    basic_overflow();
    array_overflow();
    
    return 0;
}
