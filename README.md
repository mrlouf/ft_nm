# nm
A recreation in C of the nm command as an introduction to ELF (Executable and Linkable Format) files.

##  Description

The GNU `nm` command is used to list the symbols from object files. For this particular project, we are only dealing with ELF files, whether they are in 32-bit or 64-bit format. The ELF format is a common standard for executable files, object code, shared libraries, and core dumps. It is widely used in Unix-like operating systems such as Linux, Solaris, and FreeBSD.

The implementation of `ft_nm` involves parsing the ELF file format to extract symbol information. This includes reading the ELF header, section headers, and symbol tables to retrieve details about the symbols defined in the object files. In addition, the bonus part requires the handling of various flags that modify the output, whether changing the sorting order or filtering symbols.

##  The ELF Format

The ELF format is a complex binary format that consists of several components, including:
- **ELF Header**: Contains metadata about the file, such as the type of file (executable, shared library, etc.), the architecture (32-bit or 64-bit), endianness, and the entry point address.
- **Program Headers**: Describe how the executable should be loaded into memory.
- **Section Headers**: Describe the various sections of the file, such as the symbol table, string table, and code sections.
- **Symbol Table**: Contains entries for each symbol defined in the file, including its name, value (address), size, type, and binding.

The bulk of the implementation of `ft_nm` involves the following workflow:
1. **Opening the ELF file**: The program will read the specified ELF file into memory. The function `read()` is forbidden, so I use `mmap()` to map the file into memory for easier access without resorting to file descriptors and buffer management.
2. **Parsing the ELF header**: The program will read the ELF header to determine the architecture (32-bit or 64-bit) and endianness. This information is crucial for correctly interpreting the rest of the file or for rejecting unsupported formats (like big-endian files).
3. **Locating the symbol table**: The program will locate the symbol table section using the section headers. It will also locate the associated string table, which contains the names of the symbols.
4. **Extracting symbol information**: The program will iterate through the symbol table entries, extracting the relevant information for each symbol, such as its name, value, size, type, and binding.
5. **Sorting symbols**: Depending on the flags provided, the program will sort the symbols, reverse the order or keep them in original order.
6. **Displaying the symbols**: Finally, the program will format and display the symbol information in a manner similar to GNU's `nm`, showing the symbol's value, type, and name. If flags are used to filter symbols, only the relevant symbols will be displayed.

##  Usage

You may use the Makefile to compile the program. The resulting executable will be named `ft_nm` and the syntax to use it is as follows:

```bash
./ft_nm [options] <file>
```

Just like GNU's `nm`, if no file is specified, `ft_nm` will try and read a file named `a.out` in the current directory.

##  Flags

- `-a` or `--debug-syms`: Display all symbols, including debugging symbols.
- `-g` or `--extern-only`: Display only external symbols.
- `-p` or `--no-sort`: Do not sort the symbols; display them in the order they appear in the symbol table.
- `-r` or `--reverse-sort`: Sort symbols in reverse order.
- `-u` or `--undefined-only`: Display only undefined symbols.

All flags can be combined, for example: `./ft_nm -agp <file>` will display all external symbols without sorting.

##  Testing

I have spent some time creating a comprehensive test suite to ensure the correctness of `ft_nm`. The tests cover various scenarios, including different ELF file formats (32-bit and 64-bit), as well as the various flag combinations. The test files are generated from a Shell script that, among other things, compiles simple C programs into ELF files and compares the output of `ft_nm` with that of the GNU `nm` command.

You may run the test suite by calling the `make test` command, which will execute the test script and report the results in the terminal.

##  Final thoughts

This project has been fun and very educational to work on. Having already touched the ELF format a bit in binary-exploitation or reverse-engineering projects, I did not start entirely from zero, yet I still had to do a lot of research to get a feel for the format and to be able to navigate efficiently through the various headers and sections. Using `mmap()` was a first for me, and I will look forward to using it again in future projects, as it provides a convenient way to access file data without the overhead of manual buffer management.

That approach is slightly more complex though, as it requires careful handling of pointers and offsets to ensure that we do not read beyond the mapped memory, which would cause segmentation faults. After a lot of trial and error, I finally got a working implementation and that was the moment where I realised, I only had the 64-bit part covered and therefore still needed to implement the 32-bit part as well. It was not as difficult as I expected though, since the basic code structure was already in place and the modular design of my code allowed for quick adaptations.

The most complex part was definitely understanding the actual rules for the GNU's `nm` sorting algorithm, which is not as straightforward as it seems at first glance. It is an odd mix of sorting by symbole name, then by symbol type, and then by symbol value, with some special rules for certain types of symbols or characters in the symbol name. I had to do a lot of testing and reverse-engineering of the GNU `nm` output to figure out the exact rules, and even it took a lot of testing to get it right, especially handling the `-a` flag.

### Ressources

- [nm man page](https://www.man7.org/linux/man-pages/man1/nm.1.html)
- [Oracle Documentation about ELF format](https://docs.oracle.com/cd/E19683-01/817-3677/chapter6-46512/index.html)