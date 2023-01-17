# Simple linked list serializer (Test assignment)
*v 1.1*

This little linked list serializer in C++11 is designed by me, built, by me, and pointed at getting me to Saber Interactive.

Contains code to create, serialize, and deserialize doubly linked lists with additional random links in a *very primitive* human readable format.

## How to use 

Comple the `TestListSerializer.cpp` file and run it. This will launch the demo code and print out results in your terminal. Otherwise, you can just copy the code. No dynamic libraries, sorry!
*Note* that it will create a *.txt file* called `list_serialization_test.txt` inside the project folder.

## How to build

Windows:
Use MSVC to compile for Win, tested with VS2019

Linux:
Can be compiled with GCC, tested with G++ 11.3.0

```
g++ TestListSerializer.cpp -o test
```

## Data structure 
/relevant for v 1.1/

The text structure of a serialized file consists of three parts: a header, a payload, and an index list. As you can see, the structure is vaguely inspired by HTTP packages and OpenGL buffers.

- The *header* holds the number of elements in the list
- The *payload* is a list of lines with data
- The *index list* is a list of *random links* between nodes, every link is written in two lines

There is also an *empty string* as a visual divider between data and indices.

An example of a structure with 10 elements and a link from element *Head* to element *Tail*:
```
10
tail_data
some_data
some_data
some_data
some_data
some_data
some_data
some_data
some_data
head_data

9
0
```
Note that a) the first element is Tail b) Indices are 0-based.

## Caveats and known issues

- When serializing into a file, overrides its content!
- Behaves badly with special characters (\n, \0) in data
- Tested only with ascii, may not support extended UTF