# Simple linked list serializer (Test assignment)

This little linked list serializer in C++11 is designed by me, built, by me, and pointed at getting me to Saber Interactive.

Contains code to create, serialize, and deserialize doubly linked lists with additional random links in a *very primitive* human readable format.

## How to use 

Comple the `TestListSerializer.cpp` file and run it. This will launch the demo code and print out 
results in your terminal. Otherwise, you can just copy the code. No dynamic libraries, sorry!
*Note* that it will create a *.txt file* called `list_serialization_test.txt` inside the project folder.

## How to build

Windows:
Use MSVC to compile for Win, tested with VS2019

Linux  
Can be compiled with GCC, tested with G++ 11.3.0

```
g++ TestListSerializer.cpp -o test
```
## Caveats

- When serializing into a file, overrides its content!
- Behaves badly with special characters (\n, \0) in data