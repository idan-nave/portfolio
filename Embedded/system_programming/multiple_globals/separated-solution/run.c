
int main(int argc, char const *argv[])
{
	Foo(1);
/*	Foo2(2);
*/	return 0;
}

/*
########### EX 1########
gcc mul_globals.c -c 
ar rcs libmul.a mul_globals.o
gcc -o mul.out mul_globals.c -L. -lmul

########### EX 2########
gcc -c -fPIC mul_globals.c -o mul_globals_PIC.o
ar rcs libmul_PIC.a mul_globals_PIC.o
gcc -c -fPIC foo.c -o foo.o
gcc -shared -o libfoo.so foo.o libmul_PIC.a mul_globals.h
gcc -o dynamic_pic.out run.c -L. -Wl,-rpath=. -lfoo
./dynamic_pic.out 
nm libfoo.so
bjdump -t dynamic_pic.out 

######### EX 2b - X2 dynamic libs########

######### DONT FORGET TO ENABLE FOO2-CALL FROM MAIN########

gcc -c -fPIC foo.c -L. -lmul
gcc -shared -o libfoo.so foo.o libmul_PIC.a mul_globals.h
gcc -c -fPIC foo2.c -L. -lmul
gcc -shared -o libfoo2.so foo2.o libmul_PIC.a mul_globals.h

gcc -o dynamic2.out run.c -L. -Wl,-rpath=. -lfoo -lfoo2
./dynamic2.out 


Inside Foo 1var x=1 in 0x7f275685f018
and also num=1
Inside Foo 2var x=1 in 0x7f275685f018
and also num=2

both addresses printed are the same because both `libfoo.so` and `libfoo2.so` are using the same `libmul_PIC.a` archive, which contains the `mul_globals_PIC.o` object file. This object file contains the definition of the global variable `x`, and since both shared libraries link to it, they end up sharing the same instance of `x`. This behavior is expected because shared libraries, by design, allow multiple processes to share the same code and data.


########### EX 3 ########
SEE LOAD & STATIC FILES

################# post-exercise questions: ###############


1. **Why was the global variable "duplicated"?**
   
   The global variable `x` was not duplicated; it was shared between the two shared libraries (`libfoo.so` and `libfoo2.so`). When you linked both libraries against the same `libmul_PIC.a`, they both referenced the same `mul_globals_PIC.o`, which contains the definition of `x`. This is how shared libraries work; they allow multiple programs to share the same code and data to reduce memory usage.

2. **If you would link the executable to the libraries implicitly, and not explicitly, what would the result be? Would the global variable still be "duplicated"?**

   If you link the executable to the libraries implicitly, the result would still be the same. The global variable `x` would not be duplicated; it would be shared among the shared libraries. Implicit linking (e.g., using `-lfoo` and `-lfoo2` without specifying the full library path) would still result in the same behavior because the linker would resolve the library dependencies, and both libraries would end up using the same `libmul_PIC.a`.

In summary, the issue of symbol "duplication" does not occur in these scenarios. The global variable is not duplicated; it is shared among shared libraries. This behavior is a fundamental aspect of shared libraries, allowing efficient code and data sharing between processes.


3. In this exercise, we've "duplicated" a global symbol using a
static library linked into dynamic ones, which in turn were
loaded explicitly by an executable. Let us examine several more
scenarios. Would the issue of symbol "duplication" also occur in
Eee


###################Scenario A:########################
- A header file contains a global variable declaration only: `extern int x;`
- A library includes the header and defines the variable in a C file: `int x;`
- An executable includes the same header and also defines `x`.
- The executable explicitly loads the library.

In this scenario, you will likely encounter a linker error because the symbol `x` is defined in both the library and the executable. When the executable is linked, it will find multiple definitions of `x`, and the linker will complain about symbol duplication.

###################Scenario B:###################
- A header file declares a global weak symbol: `int x` (typically defined as `__attribute__((weak)) int x;`).
- A library includes this header but does not define `x`, and it uses `x`.
- An executable includes the same header, does not define `x`, and uses it.

In this scenario, it may work if the symbol `x` is weakly defined in the library. Weak symbols are symbols that can have multiple definitions without causing linker errors. When the executable is linked, it may find a reference to `x` in the library, but since it's a weak symbol and not strongly defined in the library, the linker will allow it to remain unresolved. At runtime, if the library with the actual definition of `x` is loaded, it will resolve the reference.


4. Note that both libraries are identical in this exercise. If you
would print the global variable’s address and dlclose() the
first library, then dlopen() the second library and print the
global variable’s address, what would happen?


**If you would print the global variable’s address and `dlclose()` the first library, then `dlopen()` the second library and print the global variable’s address, what would happen?**

If you print the global variable's address, `dlclose()` the first library, and then `dlopen()` the second library, the behavior would depend on whether the second library defines the global variable `x` and whether it's the same as the one defined in the first library.

1. If the second library also defines `x`, and it's different from the first one, then the global variable's address will change to the new library's `x`.

2. If the second library defines `x`, and it's the same as the one defined in the first library, the address may remain the same if both libraries are loaded at the same memory location (shared address space). However, this behavior can be platform-dependent.

3. If the second library doesn't define `x`, and you access `x` after `dlopen()` the second library, you may encounter a runtime error because `x` may become undefined if the first library that defined it is no longer loaded.

In any case, the behavior might vary depending on the system's dynamic linker/loader and the specific circumstances. It's generally best to avoid situations where multiple libraries define the same global variable to ensure predictable behavior.


*/