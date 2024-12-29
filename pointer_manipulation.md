## Endianness

### 1.1
The following function is supposed to test if the machine running is [little endian](https://wiki.osdev.org/Endianness) or not.
What should A be replaced with to make the following code work? 

<details>
<summary> <b>HINT</b> </summary>
It should be a simple comparison.
</details>

```c
bool is_little_endian() {
    int value = 0x01020304;

    char *ptr = (char*)&value;
    
    return <A>
}
```
---

### 1.2

```c
int x = 0xAABBCCDD;
uint8_t* bytes = (uint8_t*)&x;
```

What value would bytes[0] contain on:
a) Little-endian system
b) Big-endian system

---

### 1.3
What would be the output of the code at Line A, B, C;

```c
void print_bytes(uint8_t* bytes, int n) {
    for (int i = 0; i < n; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("\n");
}

int main() {
    int integer = 0xAABBCCDD;
    uint8_t* bytes = (uint8_t*)&integer;

    printf("Before: 0x%08x\n", integer); // LINE A
    printf("Bytes : ");
    print_bytes(bytes, 4);  // Line B

    bytes[0] = 0x11;
    bytes[1] = 0x22;
    bytes[2] = 0x33;
    bytes[3] = 0x44;
    printf("After: 0x%08x\n", integer);  // Line C
}
```

## Type Casting & Pointer Arithmetic

### 2.1
What would the output of the following code be?
```c
#include <stdio.h>
int main() {
    int array[3] = {0x38394041, 0x22222222, 0x33333333};

    int *ptr = (int *)&array;
    char *char_ptr = (char *)&array;
    short *short_ptr = (short *)&array;

    printf("Before: %x\n", *ptr);

    ptr = ptr + 1;

    printf("After: %x\n", *ptr);

    printf("Before: %02x\n", *char_ptr);

    char_ptr = char_ptr + 1;

    printf("After: %02x\n", *char_ptr);

    printf("Before: %04hx\n", *short_ptr);

    short_ptr = short_ptr + 1;

    printf("After: %04hx\n", *short_ptr);

    return 0;
}

```

---

### 2.2

- How many bytes are occupied by the following matrix?
- How can the 7 in the matrix be accessed using the following methods 
    - Array notation (i.e using matrix variable only)
    - Pointer notation (i.e using a ptr variable only)
```c
int main() { 
   int matrix[3][4] = {
       {1, 2, 3, 4},
       {5, 6, 7, 8},
       {9, 10, 11, 12}
   };
   
   int *ptr = &matrix[0][0];
}
```

---

### 2.3
```c
int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    printf("*ptr = %d\n", *ptr);
    printf(" ptr = %p\n", ptr);

    int *start = arr;
    int *end = arr + 5;

    int diff = end - start;

    printf("%d\n", diff);

    return 0;
}
```
- What would the value of diff be in the following code? Assume ptr = 0x7fffa08d3b40.

---

### 2.4

Given the following code that demonstrates pointer increment/decrement operations:

```c
void pointer_increment(void) {
    double arr[] = {1.1, 2.2, 3.3, 4.4};
    double *ptr = arr;
    
    // Pre-increment
    printf("\tInitial: *ptr = %.1f\n", *ptr);                    // Line 1
    printf("\tPre-increment: *++ptr = %.1f\n", *++ptr);          // Line 2
    
    // Post-increment
    printf("\tPost-increment: *ptr++ = %.1f\n", *ptr++);         // Line 3
    printf("\tAfter post-increment: *ptr = %.1f\n", *ptr);       // Line 4
    
    // Pre-decrement
    printf("\tPre-decrement: *--ptr = %.1f\n", *--ptr);         // Line 5
    
    // Post-decrement
    printf("\tPost-decrement: *ptr-- = %.1f\n", *ptr--);         // Line 6
    printf("\tAfter post-decrement: *ptr = %.1f\n\n", *ptr);     // Line 7
}
```

Fill the following table.

Line | ptr points to | Output value
-----|--------------|-------------
1    |              |
2    |              |
3    |              |
4    |              |
5    |              |
6    |              |
7    |              |

---

### 2.5

Guess the output of the following code.
- Architecture is little-endian
- Assume int_ptr = 0x7fffa08d3b40.

```c
int main() {
    
    int value = 0x12345678;
    int *int_ptr = &value;

    char *char_ptr = (char*)int_ptr;
    
    printf("\tOriginal value: 0x%08X\n", value);

    for(int i = 0; i < 4; i++) {
        printf("\tByte %d: 0x%02X\n", i, (unsigned char)char_ptr[i]);
    }
    
    uintptr_t addr = (uintptr_t)int_ptr;
    printf("\tAddress as integer: %lx\n", addr);
    int_ptr = (int*)addr;
    printf("\tValue after casting back: 0x%08X\n\n", *int_ptr);
}
```
---

### 2.6

```c
struct Point {
    int x;
    int y;
};

struct Point points[3] = {{1,1}, {2,2}, {3,3}};

int main() {
    struct Point *ptr = points;
    // A
    printf("x: %d, y: %d\n", ptr->x, ptr->y);
}
```
What should line A be replaced with using pointer arithmetic to print the x and y values of the second point?

---

### Void pointers 

### 3.1

```c
#include <stdio.h>
int main() {
    int i = 37;
    float f = 3.14;
    void *ptr;
    
    ptr = &i;
    printf("char: %c\n", <A>ptr);
    
    ptr = &f;
    printf("float: %f\n", <B>ptr);
}
```
What should A and B be replaced with to make the code work?

---

### Function pointers

### 4.1

```c
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {

    operation = add;
    printf("Result: %d\n", operation(5, 3));
    operation = subtract;
    printf("Result: %d\n", operation(5, 3));
}
```

What should be the type of operation variable?