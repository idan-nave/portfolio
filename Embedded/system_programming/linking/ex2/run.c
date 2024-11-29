
int main(int argc, char const *argv[])
{
	Foo(5);
	return 0;
}

/*
gcc -c -fPIC foo.c
gcc -shared -o libfoo.so foo.o
gcc -o dynamic.out run.c -L. -lfoo

	gcc -o dynamic.out run.c -Wl,-rpath,. -lfoo

	 gcc -o dynamic.out run.c -L. -Wl,-rpath=. -lfoo

 gcc -o dynamic.out run.c -L/home/idan/Documents/Dev/Git_WD/system_programming/Exercises/linking/EX4 -Wl,-rpath=/home/idan/Documents/Dev/Git_WD/system_programming/Exercises/linking/EX4 -lfoo

LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH
./dynamic.out
*/

/*
"error while loading shared libraries: libfoo.so: cannot open shared object file: No such file or directory," indicates that the dynamic linker (ld-linux.so) cannot find the shared library libfoo.so when trying to run the dynamic.out executable. To resolve this issue, you need to make sure that the dynamic linker can locate and load the shared library. Here are steps to help you resolve the problem:

Library Path (LD_LIBRARY_PATH):

Ensure that the directory containing libfoo.so is included in your system's library search path. You can do this by setting the LD_LIBRARY_PATH environment variable.
For example, if libfoo.so is in the current directory, you can add it to the LD_LIBRARY_PATH temporarily:
	export LD_LIBRARY_PATH=.
	./dynamic.out
System-wide Library Installation (Recommended):

A more robust and recommended approach is to install your shared library system-wide so that it can be found by the dynamic linker without needing to modify LD_LIBRARY_PATH.
Use the install command or manually copy libfoo.so to a standard library directory like /usr/local/lib.

	sudo install -m 644 libfoo.so /usr/local/lib
Update Library Cache (ldconfig):

After installing the shared library system-wide, you may need to update the library cache using the ldconfig command:

	sudo ldconfig
Recompile Your Program.

################### implicit declaration: ###############

The `-Wl` flag in GCC is used to pass options directly to the linker (in your case, `ld`) when compiling and linking your program. It's typically used to specify linker options, and you can use it to specify the library path.

Here's how you can use the `-Wl` flag to specify the library path:

	gcc -o my_program my_program.c -Wl,-rpath,/path/to/library/directory -lmylibrary
	gcc -o dynamic.out run.c -Wl,-rpath,. -lfoo

In the above command:

- `-Wl` tells GCC to pass options to the linker.
- `-rpath,/path/to/library/directory` specifies the runtime library search path (rpath) where the dynamic linker (`ld-linux.so`) should look for shared libraries.
- `-lmylibrary` specifies that your program uses the library `libmylibrary.so`.

Replace `/path/to/library/directory` with the actual path where your library (`libmylibrary.so`) is located.

This approach allows you to specify the library path as a linker option without modifying the `LD_LIBRARY_PATH` environment variable or installing the library system-wide. It can be useful in cases where you want to control the library search path for a specific program without affecting the system-wide library paths.
*/
