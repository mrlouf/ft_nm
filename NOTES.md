# Global notes about the project

- 'nm' stands for 'name list' according to Wikipedia, which was the name used before 'symbol table' became the standard term. 
- nm handles unlimited number of files, and should not crash if a file is not valid.
- if a file is not valid, an error message should be printed to stderr, and the program should continue with the next file. The return value should be 1 if at least one file is not valid, and 0 otherwise.

- The `.symtab` section is the regular symbol table, and is used as a sort of dictionnary to resolve symbol names to their types and values, using a "name <-> address" mapping. This is used by the linker to resolve symbol references between object files and libraries.

- By default, the `t` and `T` symbols are printed out even though they have a value of 0.

- Obviously, the program should be able to handle both 32-bit and 64-bit ELF files, and possibly even little-endian and big-endian files. The program should be able to handle both executable files and shared libraries, as well as object files.
This gives us two options: use void pointers and cast them to the appropriate types, or use a separate struct for each type of file (union?) and use a common struct to hold the common fields. The first option is more flexible, but the second option is more type-safe and easier to read.

## Bonus

The following flags are supported:

- `-a` : Display all symbols, even debugger-only symbols; normally these are not listed.
- `-g` : Display only external symbols.
- `-u` : Display only undefined symbols (those external to each object file). By default both defined and undefined symbols are displayed.
- `-r` : Reverse the order of the sort (whether numeric or alphabetic); let the last come first.
- `-p` : Do not bother to sort the symbols in any order; print them in the order encountered.
