# SPIRV Bundle
The SPIRV Bundle can be used to put spirv files directly into a C file, so you can compile it and link against your program, so you can acess the binary without using I/O.

## How to compile
- You can just type `m̀ake`
- You can configure the compiler by setting the Compiler variable `Compiler=msvc make`, by default it uses clang
- You can configure the compile flags by setting the CompileFlags variable `CompileFlags=-Wextra make`, by default it uses `-Wall -Werror`
- You can configure the linker by setting the Linker variable `Linker=lld make`, by default it uses clang

## How to use
- `<path to bundle binary> <one or more input files> -o <output file>`
- Example: `./bundle triangle_fragment.spv triangle_vertex.spv -o shaders.c`
