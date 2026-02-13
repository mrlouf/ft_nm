# Global notes about the project

- 'nm' stands for 'name list' according to Wikipedia, which was the name used before 'symbol table' became the standard term. 
- nm handles unlimited number of files, and should not crash if a file is not valid.
- if a file is not valid, an error message should be printed to stderr, and the program should continue with the next file. The return value should be 1 if at least one file is not valid, and 0 otherwise.

- The `.symtab` section is the regular symbol table, and is used as a sort of dictionnary to resolve symbol names to their types and values, using a "name <-> address" mapping. This is used by the linker to resolve symbol references between object files and libraries.

## Bonus

- the following flags are supported:
  - `-a` to show all symbols, including local and debugging symbols.
  - `-g` to show only debugging symbols.
  - `-u` to show only undefined symbols.
  - `-r` to show in the reverse order they are found.
  - `-p` to show symbols in the order they appear in the symbol table (ie. no sorting).
