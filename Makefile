Compiler ?= clang
CompileFlags ?= -Wall -Werror

Linker ?= clang

compile: bundle.o
	$(Linker) -o bundle bundle.o

%.o: %.c
	$(Compiler) -c -o bundle.o bundle.c $(CompileFlags)
