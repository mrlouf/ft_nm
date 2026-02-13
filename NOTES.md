# Global notes about the project

- 'nm' stands for 'name list' according to Wikipedia, which was the name used before 'symbol table' became the standard term. 
- nm handles unlimited number of files, and should not crash if a file is not valid.
- if a file is not valid, an error message should be printed to stderr, and the program should continue with the next file. The return value should be 1 if at least one file is not valid, and 0 otherwise.

- The `.symtab` section is the regular symbol table, and is used as a sort of dictionnary to resolve symbol names to their types and values, using a "name <-> address" mapping. This is used by the linker to resolve symbol references between object files and libraries.

## Bonus

The following flags are supported:

- `-a` : Display all symbols, even debugger-only symbols; normally these are not listed.
- `-g` : Display only external symbols.
- `-u` : Display only undefined symbols (those external to each object file). By default both defined and undefined symbols are displayed.
- `-r` : Reverse the order of the sort (whether numeric or alphabetic); let the last come first.
- `-p` : Do not bother to sort the symbols in any order; print them in the order encountered.
