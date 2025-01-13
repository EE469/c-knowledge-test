## Buffer Overflow
### 1.1 Basic Stack Buffer Overflow
Consider the following code:
```c
void basic_overflow() {
    char buffer[5];  // Can hold 4 chars + null terminator
    char guard = 'X';  // Variable right after buffer in memory
    
    printf("Before overflow:\n");
    printf("Guard value: %c\n", guard);
    
    strcpy(buffer, "123456");  
    
    printf("After overflow:\n");
    printf("Guard value: %c\n", guard);
}
```
What will be the value of `guard` after the strcpy operation?

<details>
<summary><b>HINT</b></summary>
Consider the memory layout from the pointer_manipulation exercise and how many characters are being written.
</details>

---
### 1.2 Memory Layout
Given this memory layout diagram:

| High Address |              |
|--------------|--------------|
|              | guard = 'X'  |
|--------------|--------------|
|              | buffer[4]    |
|              | buffer[3]    |
|              | buffer[2]    |
|              | buffer[1]    |
|              | buffer[0]    |
| Low Address  |              |

After writing "HELLO" to the buffer:
- Which character will overwrite the guard value?
- What makes this a buffer overflow vulnerability?

---
### 1.3 Struct Buffer Overflow
```c
struct {
    int nums1[3];
    int nums2[2];
} arrays = {
    .nums1 = {0, 0, 0},
    .nums2 = {111, 222}
};

for(int i = 0; i < 5; i++) {
    arrays.nums1[i] = i * 100;
}
```
What will be the values of:
- arrays.nums2[0]
- arrays.nums2[1]
After the loop completes?

---
### 1.4 Safe Programming
Given this vulnerable code:
```c
char buffer[5];
strcpy(buffer, user_input);  // user_input is a string from user
```
What are two ways to make this code safer?
<details>
<summary><b>HINT</b></summary>
Think about bounds checking and safer string functions.
</details>

---
### 1.5 Buffer Overflow Prevention
Consider this code:
```c
void copy_string(char *dest, const char *src) {
    while(*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
```
What security issues exist in this function and how would you fix them?

---
### 1.6 Memory Corruption
```c
int main() {
    int important_value = 42;
    char small_buffer[4];
    scanf("%s", small_buffer);
    printf("Important value: %d\n", important_value);
    return 0;
}
```
If a user inputs "12345678", what might happen to `important_value`?


### 1.7 

Find all the problems with the following code.

```c
void copy_name(char* dest) {
    char name[] = "Alice";
    int i;
    
    for(i = 0; name[i]; i++) {
        dest[i] = name[i];
    }
}

int main() {
    char short_buffer[4];
    copy_name(short_buffer);
    printf("%s\n", short_buffer);
}
```