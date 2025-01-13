## Integer Overflow & Underflow
### 1.1 Basic Integer Overflow
```c
uint8_t counter = 250;
for(int i = 0; i < 10; i++) {
    counter++;
    printf("%d ", counter);
}
```
What will be the sequence of numbers printed? Why?
<details>
<summary><b>HINT</b></summary>
uint8_t has a maximum value of 255. What happens after that?
</details>

---
### 1.2 Signed Integer Overflow
```c
int main() {
    int8_t x = INT8_MAX;
    printf("Before: %d\n", x);
    x = x + 1;
    printf("After: %d\n", x);
    return 0;
}
```
- What is the value of INT8_MAX?
- What will be printed as the "After" value?
- Why does this behavior occur?

---
### 1.3 Integer Underflow
```c
uint8_t value = 0;
printf("Before: %u\n", value);
value--;
printf("After: %u\n", value);
```
What will be printed as the "After" value and why?
<details>
<summary><b>HINT</b></summary>
Think about what happens when you subtract 1 from the minimum possible value of a variable.
</details>

---
### 1.4 Integer Overflow in Calculations
```c

uint64_t calculate_buffer_size(uint64_t num_elements, uint64_t element_size) {
    return num_elements * element_size;
}

int main() {
    uint64_t elements = UINT64_MAX;
    printf("Elements %zu\n", elements);
    uint64_t elem_size = 2;
    uint64_t buf_size = calculate_buffer_size(elements, elem_size);

    void* buf = malloc(buf_size);
    // ...
}
```
- What would the size of the buffer allocated be?

<details>
<summary><b>HINT</b></summary>
Same as previous exercise think about what happens when you multiply the maximum size possible for a variable.</details>

---
### 1.5
```c
void process_data(unsigned int length) {
    unsigned int buf_size = length + 20;  // Add 20 bytes for header
    char* buffer = (char*)malloc(buf_size);
    // ... use buffer ...
}
```
- At what size of length would there be a problem?
- How would you modify this code to make it secure?

---
### 1.6 Arithmetic Operations
Complete the following function to safely add two integers without overflow, bool should indicate success or failure of the operation.
```c
bool safe_add(int a, int b, int* result) {
    // Your code here
}
```

<details>
<summary><b>HINT</b></summary>
Use the max variables for each type.
</details>

---
### 1.7 Loop Conditions
What's wrong with this loop and how would you fix it?
```c
uint16_t i;
for(i = 1; i <= 65535; i++) {
    // Process something
}
```

<details>
<summary><b>HINT</b></summary>
This is a very subtle bug, please look at how the loop operates with the maximum value of i.
</details>
