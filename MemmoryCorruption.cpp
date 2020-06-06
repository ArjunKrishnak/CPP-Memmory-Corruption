
//  Created by Arjun krishna on 06/06/20.
//  Copyright © 2020 Arjun krishna. All rights reserved.

// ===========================================================================
// Common Memory corruption errors in CPP
// ===========================================================================

#include <iostream>
#include <thread>

void HeapBufferOverflow(){
    char* buff = (char*)malloc(10);
    buff[1] = 'h';
    buff[2] = 'i';
    buff[100] = 'a'; // heap-buffer-overflow
    char element = buff[100]; // heap-buffer-overflow
    std::cout<<element<<std::endl;
}

void HeapBufferUnderflow(){
    char* buff = (char*)malloc(10);
    buff[-1] = 'b'; // heap-buffer-underflow
    char element = buff[-1]; // heap-buffer-underflow
    std::cout<<element<<std::endl;
}
    
void HeapAbuse(){
     char* buff = (char*)malloc(1000000000000000); // Allocating large memory
}

void DoubleFree(){
    char* buff = (char*)malloc(10);
    free(buff);
    // dangling pointer
    buff = nullptr;
    free(buff);
}

void HeapUseAfterFree(){
    char* buff = (char*)malloc(10);
    free(buff);
    buff[0] = 'a';
}

// Not detected by Adress sanitizer
void StackOverflow(int x)
{
    StackOverflow(x);
}

void StackAbuse(){
    int buff[1000000000000000];
}

int* StackUseAfterReturn(){
    int element = 1;
    return &element;
}

void MismatchedDealocation(){
    /**
     * For each malloc or calloc, there should be exactly one free.
     * For each new there should be exactly one delete.
     * For each new[] there should be exactly one delete[].
     * For each stack allocation, there should be no explicit freeing or deletion. The destructor is called automatically, where applicable.
     */
    
    char* buff = new char[2];
    buff[0] =  'h';
    buff[1] = 'i';
    free(buff); // Undefined behaviour
    
    buff = (char*)malloc(2);
    buff[0] =  'h';
    buff[1] = 'i';
    delete[] buff; // Undefined behaviour
    
    buff = new char('a');
    delete[] buff; // Undefined behaviour
    
    int stackBuff[10];
    int *ptr = &stackBuff[0];
    free(ptr); // Undefined behaviour
    
}

void Thread1(int *p)
{
    int q[1024];
    p = q;
    q[0] = 1;
}

void Thread2(int *p)
{
    *p = 3;
}

void CrossStackAccess(){
    int *ptr;
    std::thread thread1(Thread1,ptr);
    thread1.join();
    std::thread thread2(Thread2,ptr);
    thread2.join();
}

int main(int argc, const char * argv[]) {
    std::cout<<"Program started"<<std::endl;
    
    HeapBufferOverflow();
    HeapBufferUnderflow();
    HeapAbuse();
    DoubleFree();
    HeapUseAfterFree();
    
    StackOverflow(1);
    StackAbuse();
    int* element = StackUseAfterReturn();
    std::cout<<*element<<std::endl;

    MismatchedDealocation();
    CrossStackAccess();
    
    return 0;
}


/**
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

The Address Sanitizer cannot detect memory leaks, access to uninitialized memory, or integer overflow
 
Reference :
 https://developer.apple.com/documentation/code_diagnostics/address_sanitizer
 http://www.yolinux.com/TUTORIALS/C++MemoryCorruptionAndMemoryLeaks.html

*/


