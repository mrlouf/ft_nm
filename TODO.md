- Handle file permissions and errors gracefully, ensuring that the program continues processing subsequent files even if one fails.
- Check return values against the real nm
- Check leaks with valgrind

- checks to implement in process_file regarding ELF file validation:
// 1. Vérifier taille minimale
// 2. Vérifier magic number
// 3. Vérifier classe (32/64 bit)
// 4. Vérifier que e_shoff ne dépasse pas la taille du fichier

Fichier corrompu?

- Investigate whether flag -a needs to print the value or not, and if nameless symbols should be printed as well.
- flag a: need to extract all symbols greedily

- use ft_printf or write instead of printf, as required by the subject