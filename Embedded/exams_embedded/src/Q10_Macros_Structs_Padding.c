###################### Questions ######################
1. Write a macro MAX3 (a, b, c) for the maximum value between numbers a, b and c.
2. Write a macro TO_LOWER (a) that receives a char and returns its lower case counterpart, in case it is an upper case ascii, otherwise it returns the char itself.
3. Write a macro OFFSET(s, f) that receives some struct type s and a field name f, and returns the offset of that field in the struct.
4. Consider the following struct:
a. What is the sizeof this struct (on a 32 bit machine)? Draw the paddings.
b. When declaring a variable of this type, what can you say about its address?
    struct s
    {
        int num;
        char ch1;
        int* ptr;
        char ch2;
    };

5. What is s1?
    typedef struct
    {
        int num;
        char ch1;
    } s1;
6. What is s1?
    struct
    {
        int num;
    } s1;

7. What is the sizeof u1 (on a 64 bit machine)?
    union u
    {
        int num;
        char arr[5];
    } ul;


8. Besides trying to minimize paddings for space saving, what other considerations would you have in deciding the order of fields in a struct?

###################### Answers ######################
1. **Macro MAX3:**
#define MAX3(a, b, c) ((a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c))

2. **Macro TO_LOWER:**
#define TO_LOWER(a) (((a) >= {A} && (a) <= {Z}) ? ((a) + ({a} - {A})) : (a))
                                                 /* origin+<range>*/
3. **Macro OFFSET:**
#define OFFSET(s, f) ((size_t)&((s *)0)->f)

4. **Struct and Pointers:**
a. The struct s contains:

    int num: 4 bytes
    char ch1: 1 byte
    int* ptr: 4 bytes (assuming a 32-bit machine)
    char ch2: 1 byte
    Total: 16 bytes, on a 32-bit machine:
    +------+------+------+------+
    | num  | ch1  |      | ch2  |
    +------+------+------+------+
b. When declaring a variable of type struct s, the address of the variable will be the address of its first member (num). Since the members are stored in memory in the order theyre defined, the address of the variable will be the same as the address of its first member (num).

5. s1 is a typedef for a struct with members num and ch1. It defines a new data type s1 that has the same structure as the defined struct.
    typedef struct
    {
        int num;
        char ch1;
    } s1;

    
6. `This is an anonymous struct with a single member num. Its not assigned to any variable or typedef. The member num is of type int.
    struct
    {
        int num;
    } s1;

7. The sizeof u1 is the size of the largest member of the union, which is int num. On a 64-bit machine, the size would be 4 bytes (assuming an int is 4 bytes). The char arr[5] doesnt contribute to the size of the union as its not the largest member.
    union u
    {
        int num;
        char arr[5];
    } ul;

8. Besides minimizing paddings for space saving, other considerations for deciding the order of fields in a struct might include:
   - **Memory alignment and cache considerations:** Placing larger data types first may help with memory alignment and cache access patterns.
   - **Field grouping:** Grouping related fields together can improve code readability and maintainability.
   - **Access patterns:** Fields that are frequently accessed together should be placed close to each other to optimize memory access.
   - **Memory usage:** Placing smaller fields before larger ones may reduce memory fragmentation.
   - **Compatibility:** When designing structs for serialization or interprocess communication, consider data compatibility and byte order.

These considerations help ensure efficient memory usage, access, and maintenance of the struct.