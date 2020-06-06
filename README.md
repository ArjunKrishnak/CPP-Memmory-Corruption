# CPP-Memmory-Corruption
Various common scenarios of memory corruption in C++

Memory errors:

Heap memory errors:

    Attempting to free memory already freed.
    Freeing memory that was not allocated.
    Attempting to read/write memory already freed.
    Attempting to read/write to memory which was never allocated.
    Memory allocation error.
    Reading/writing to memory out of the bounds of a dynamically allocated array

Stack (local variables) memory errors:

    Reading/writing to memory out of the bounds of a static array. (array index overflow - index too large/underflow - negative index)
    Function pointer corruption: Invalid passing of function pointer and thus a bad call to a function.
    VTable corruption
    Cross stack access in multithreaded scenarios

The Xcode Address Sanitizer cannot detect memory leaks, access to uninitialized memory, or integer overflow
 
Reference :
https://developer.apple.com/documentation/code_diagnostics/address_sanitizer
http://www.yolinux.com/TUTORIALS/C++MemoryCorruptionAndMemoryLeaks.html
