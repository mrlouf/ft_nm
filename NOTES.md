# Global notes about the project

- nm handles unlimited number of files, and should not crash if a file is not valid.
- if a file is not valid, an error message should be printed to stderr, and the program should continue with the next file. The return value should be 1 if at least one file is not valid, and 0 otherwise.

## Bonus

- the following flags are supported:
  - `-a` to show all symbols, including local and debugging symbols.
  - `-g` to show only debugging symbols.
  - `-u` to show only undefined symbols.
  - `-r` to show only defined symbols.
  - `-p` to show only the symbol names, without addresses or types.
