CC ?= clang
Flags ?= -Wall -Werror

compile:
	$(CC) -o bundle bundle.c $(Flags)
