# SPIRV Bundle
The SPIRV Bundle can be used to put spirv files directly into a C file, so you can compile it and link against your program, so you can acess the binary without using I/O.

## How to compile
- You can just type `m̀ake`
- You can configure the compiler by setting the CC variable `CC=msvc make`, by default it uses clang
- You can configure the compile/link flags by setting the Flags variable `Flags=-l... make`, by default it uses `-Wall -Werror`

## How to use
- `<path to bundle binary> <one or more input files> -o <output file>`
- Example: `./bundle triangle_fragment.spv triangle_vertex.spv -o shaders.c`
