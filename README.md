# My_library
My Custom Allocators, Math, Utils library. Stuff I use for private and public projects

## Math
Custom SIMD optimized (when it makes sense) library tailored for 3D and 2D graphics usage. Matrix & vector operations and some util math functions (ceil, floor etc.)
Fast 4x4 matrix implementations based on various resources that I found and then adjusted/reimplemented myself. 

## Allocators
Small and fast allocators that are used to manage pre-allocated memory on a low level. 
VM are direct virtual memory allocators for windows can be used directly or to pre-allocate memory to be further used by other allocators or Views.

## Views
Are not owned Data Structures. POD types are assumed for them. Mostly array based, strong emphasis on reusing memory and creating/using generational handles instead of pointers.
Hash map is using linear probing Robin Hood hashing with backward shift deletion for efficeint removal of tombstones.
