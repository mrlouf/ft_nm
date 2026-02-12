#   Glossary of symbol values

As per the nm manpage, the symbol values are as follows:

"A" : The symbol's value is absolute, and will not be changed by further linking.

"B" / "b" : The symbol is in the uninitialized data section (known as BSS ).

"C" : The symbol is common. Common symbols are uninitialized data. When linking, multiple common symbols may appear with the same name. If the symbol is defined anywhere, the common symbols are treated as undefined references.

"D" / "d" : The symbol is in the initialized data section.

"G" / "g" : The symbol is in an initialized data section for small objects. Some object file formats permit more efficient access to small data objects, such as a global int variable as opposed to a large global array.

"i" : For PE format files this indicates that the symbol is in a section specific to the implementation of DLLs. For ELF format files this indicates that the symbol is an indirect function. This is a GNU extension to the standard set of ELF symbol types. It indicates a symbol which if referenced by a relocation does not evaluate to its address, but instead must be invoked at runtime. The runtime execution will then return the value to be used in the relocation.

"N" : The symbol is a debugging symbol.

"p" : The symbols is in a stack unwind section.

"R" / "r" : The symbol is in a read only data section.

"S" / "s" : The symbol is in an uninitialized data section for small objects.

"T" / "t" : The symbol is in the text (code) section.

"U" : The symbol is undefined.

"u" : The symbol is a unique global symbol. This is a GNU extension to the standard set of ELF symbol bindings. For such a symbol the dynamic linker will make sure that in the entire process there is just one symbol with this name and type in use.

"V" / "v" : The symbol is a weak object. When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is used with no error. When a weak undefined symbol is linked and the symbol is not defined, the value of the weak symbol becomes zero with no error. On some systems, uppercase indicates that a default value has been specified.

"W" / "w" : The symbol is a weak symbol that has not been specifically tagged as a weak object symbol. When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is used with no error. When a weak undefined symbol is linked and the symbol is not defined, the value of the symbol is determined in a system-specific manner without error. On some systems, uppercase indicates that a default value has been specified.

"-" : The symbol is a stabs symbol in an a.out object file. In this case, the next values printed are the stabs other field, the stabs desc field, and the stab type. Stabs symbols are used to hold debugging information.

"?" : The symbol type is unknown, or object file format specific.

Note: The case of the symbol type character indicates whether the symbol is local (lowercase) or global (uppercase). For example, "t" indicates a local symbol in the text section, while "T" indicates a global symbol in the text section.