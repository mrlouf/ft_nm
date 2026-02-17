/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:05:55 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/17 11:58:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static int	parse_elf_headers(t_file *file)
{
/* 	ft_putstr_fd(BLUE, 1);
	ft_printf("[DEBUG] Parsing mapping of file: %s\n", file->filename);
	ft_printf("[DEBUG] Mapped at %p\n", file->data); */

	unsigned char *e_ident = (unsigned char *)file->data;

	if (e_ident[EI_CLASS] == ELFCLASS32) {

		file->elf_class = ELFCLASS32;
		file->u.file32.ehdr = (Elf32_Ehdr *)file->data;
		
	} else if (e_ident[EI_CLASS] == ELFCLASS64) {
		
		file->elf_class = ELFCLASS64;
		file->u.file64.ehdr = (Elf64_Ehdr *)file->data;
	}
	else {
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(file->filename, 2);
		ft_putendl_fd(": file format not recognized", 2);
		ft_putstr_fd(RESET, 1);
		return (1);
	}

	if (check_elf_magic(file) != 0) {
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("ft_nm: ", 2);
		ft_putstr_fd(file->filename, 2);
		ft_putendl_fd(": file format not recognized", 2);
		ft_putstr_fd(RESET, 1);
		return (1);
	}

/* 	ft_printf("[DEBUG] ELF file detected: %s of type: ", file->filename);
	switch (file->ehdr->e_type) {
		case ET_REL:    // Relocatable file (.o)
			printf("Object file\n");
			break;
		case ET_EXEC:   // Executable file
			printf("Executable\n");
			break;
		case ET_DYN:    // Shared object (.so) ou PIE executable
			printf("Shared library or PIE executable\n");
			break;
		case ET_CORE:   // Core dump
			printf("Core file\n");
			break;
		default:
			fprintf(stderr, "Unknown ELF type\n");
			return (1);
	} */
	
/* 	printf("[DEBUG] Entry point: 0x%lx\n", file->ehdr->e_entry);
	ft_putstr_fd(RESET, 1);
 */
	return (0);
}

static int	extract_file_data(t_file *file)
{
	int	fd;
	struct stat	st;

	fd = open(file->filename, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			nm_warning(file->filename, ": No such file or directory");
		else if (errno == EACCES)
			nm_warning(file->filename, ": Permission denied");
		else
			nm_warning(file->filename, ": Unable to open file");
		return (1);
	}

	if (fstat(fd, &st) < 0)
	{
		close(fd);
		nm_error("fstat failed");
	}

	if (!S_ISREG(st.st_mode))	// Skip non regular files (directories, device files)
	{
		close(fd);
		nm_warning(file->filename, " is a folder");
		return (1);
	}

	file->size = st.st_size;

	if (file->size == 0)
	{
		close(fd);
		return (1);
	}

	if (file->size < sizeof(Elf64_Ehdr) && file->size < sizeof(Elf32_Ehdr))
	{
		close(fd);
		nm_warning(file->filename, ": file format not recognized");
		return (1);
	}

	file->data = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (file->data == MAP_FAILED)
		nm_error("mmap failed");

	return (0);
}

static void find_symtab(t_file *file)
{
	if (file->elf_class == ELFCLASS32) {

		file->u.file32.shdr = (Elf32_Shdr *)(file->data + file->u.file32.ehdr->e_shoff);
		file->u.file32.strtab = (char *)(file->data + file->u.file32.shdr[file->u.file32.ehdr->e_shstrndx].sh_offset);
	
		int i = 0;
		while (i < file->u.file32.ehdr->e_shnum)
		{
			// const char *section_name = file->strtab + file->shdr[i].sh_name;
			//ft_printf("[DEBUG] Section %d: %s\n", i, section_name);
			if (file->u.file32.shdr[i].sh_type == SHT_SYMTAB) { 
				// ft_printf("%s[DEBUG] Found symbol table in section: %s%s\n", GREEN, section_name, RESET);
				file->u.file32.symtab = (Elf32_Sym *)(file->data + file->u.file32.shdr[i].sh_offset);
				file->u.file32.symtab_size = file->u.file32.shdr[i].sh_size / sizeof(Elf32_Sym);
				file->u.file32.strtab = (char *)(file->data + file->u.file32.shdr[file->u.file32.shdr[i].sh_link].sh_offset);
				return;
			}
			i++;
		}
	
	} else if (file->elf_class == ELFCLASS64) {

		file->u.file64.shdr = (Elf64_Shdr *)(file->data + file->u.file64.ehdr->e_shoff);
		file->u.file64.strtab = (char *)(file->data + file->u.file64.shdr[file->u.file64.ehdr->e_shstrndx].sh_offset);
	
		int i = 0;
		while (i < file->u.file64.ehdr->e_shnum)
		{
			// const char *section_name = file->strtab + file->shdr[i].sh_name;
			//ft_printf("[DEBUG] Section %d: %s\n", i, section_name);
			if (file->u.file64.shdr[i].sh_type == SHT_SYMTAB) { 
				// ft_printf("%s[DEBUG] Found symbol table in section: %s%s\n", GREEN, section_name, RESET);
				file->u.file64.symtab = (Elf64_Sym *)(file->data + file->u.file64.shdr[i].sh_offset);
				file->u.file64.symtab_size = file->u.file64.shdr[i].sh_size / sizeof(Elf64_Sym);
				file->u.file64.strtab = (char *)(file->data + file->u.file64.shdr[file->u.file64.shdr[i].sh_link].sh_offset);
				return;
			}
			i++;
		}
	}

/* 	ft_putstr_fd(YELLOW, 1);
	ft_printf("[DEBUG] No symbol table found in file: %s%s\n", file->filename, RESET); */
}

static void add_symbol_to_file(t_file *file, t_symbol *symbol)
{
	t_symbol_node *new_node = malloc(sizeof(t_symbol_node));
	if (!new_node)
		nm_error("malloc failed");

	new_node->symbol = *symbol;
	new_node->next = NULL;
	
	if (file->symbols.head == NULL)	{
		file->symbols.head = new_node;
	}
	else {
		t_symbol_node *current = file->symbols.head;

		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_node;
	}
	file->symbols.count++;
}

static char get_symbol32_type(Elf32_Sym *sym, Elf32_Shdr *shdr_table, Elf32_Ehdr *ehdr) {

    unsigned char bind = ELF32_ST_BIND(sym->st_info);
    unsigned char type = ELF32_ST_TYPE(sym->st_info);
    Elf32_Half shndx = sym->st_shndx;
    char c;
    
    if (shndx == SHN_UNDEF && bind != STB_WEAK)
        return 'U';
    if (shndx == SHN_ABS)
        c = 'A';
    else if (shndx == SHN_COMMON)
        c = 'C';
    else if (shndx < ehdr->e_shnum) {
        Elf32_Shdr *section = &shdr_table[shndx];
        if (section->sh_type == SHT_NOBITS)
            c = 'B';
        else if (section->sh_flags & SHF_EXECINSTR)
            c = 'T';
        else if (section->sh_flags & SHF_WRITE)
            c = 'D';
        else if (section->sh_flags & SHF_ALLOC)
            c = 'R';
        else
            c = 'N';
    }
    else {
        c = '?';
    }
    if (bind == STB_WEAK) {
        if (shndx == SHN_UNDEF)
            c = 'w';
        else if (type == STT_OBJECT)
            c = 'V';
        else
            c = 'W';
    }
    
    if (bind == STB_LOCAL && c != 'U' && c != 'w' && c != 'N')
        c = ft_tolower(c);
    
    return c;
}

static char get_symbol64_type(Elf64_Sym *sym, Elf64_Shdr *shdr_table, Elf64_Ehdr *ehdr) {

    unsigned char bind = ELF64_ST_BIND(sym->st_info);
    unsigned char type = ELF64_ST_TYPE(sym->st_info);
    Elf64_Half shndx = sym->st_shndx;
    char c;
    
    if (shndx == SHN_UNDEF && bind != STB_WEAK)
        return 'U';
    if (shndx == SHN_ABS)
        c = 'A';
    else if (shndx == SHN_COMMON)
        c = 'C';
    else if (shndx < ehdr->e_shnum) {
        Elf64_Shdr *section = &shdr_table[shndx];
        if (section->sh_type == SHT_NOBITS)
            c = 'B';
        else if (section->sh_flags & SHF_EXECINSTR)
            c = 'T';
        else if (section->sh_flags & SHF_WRITE)
            c = 'D';
        else if (section->sh_flags & SHF_ALLOC)
            c = 'R';
        else
            c = 'N';
    }
    else {
        c = '?';
    }
    if (bind == STB_WEAK) {
        if (shndx == SHN_UNDEF)
            c = 'w';
        else if (type == STT_OBJECT)
            c = 'V';
        else
            c = 'W';
    }
    
    if (bind == STB_LOCAL && c != 'U' && c != 'w' && c != 'N')
        c = ft_tolower(c);
    
    return c;
}

static void extract_symbols(t_file *file, unsigned char flags)
{
    find_symtab(file);
    if ((file->elf_class == ELFCLASS64 && file->u.file64.symtab == NULL)
	|| (file->elf_class == ELFCLASS32 && file->u.file32.symtab == NULL)) {
        ft_printf("ft_nm: %s: no symbol\n", file->filename);
        return;
    }

	if (file->elf_class == ELFCLASS32) {
		for (int i = 0; i < file->u.file32.symtab_size; i++)
		{
			Elf32_Sym *sym32 = &file->u.file32.symtab[i];
			char *name;
			
	/*      // Pour les symboles de type SECTION, récupérer le nom depuis shstrtab
			if (ELF64_ST_TYPE(sym->st_info) == STT_SECTION || ELF64_ST_TYPE(sym->st_info) == STT_FILE) {
				if (sym->st_shndx < file->ehdr->e_shnum) {
					Elf64_Shdr *section = &file->shdr[sym->st_shndx];
					name = file->strtab + section->sh_name;
				} else {
					name = "";
				}
			} else {
				// Cas normal : nom dans strtab
				name = file->strtab + sym->st_name;
			} */

			name = file->u.file32.strtab + sym32->st_name;
			
			if (name[0] == '\0' && !(flags & FLAG_A))
				continue;
				
			t_symbol symbol;
			symbol.value = sym32->st_value;
			symbol.name = name;
			symbol.type = get_symbol32_type(sym32, file->u.file32.shdr, file->u.file32.ehdr);
			symbol.size = sym32->st_size;
			symbol.bind = ELF32_ST_BIND(sym32->st_info);
			symbol.sym_type = ELF32_ST_TYPE(sym32->st_info);
			add_symbol_to_file(file, &symbol);
		}
	} else if (file->elf_class == ELFCLASS64) {
		for (int i = 0; i < file->u.file64.symtab_size; i++)
		{
			Elf64_Sym *sym64 = &file->u.file64.symtab[i];
			char *name;
			
	/*      // Pour les symboles de type SECTION, récupérer le nom depuis shstrtab
			if (ELF64_ST_TYPE(sym->st_info) == STT_SECTION || ELF64_ST_TYPE(sym->st_info) == STT_FILE) {
				if (sym->st_shndx < file->ehdr->e_shnum) {
					Elf64_Shdr *section = &file->shdr[sym->st_shndx];
					name = file->strtab + section->sh_name;
				} else {
					name = "";
				}
			} else {
				// Cas normal : nom dans strtab
				name = file->strtab + sym->st_name;
			} */

			name = file->u.file64.strtab + sym64->st_name;
			
			if (name[0] == '\0' && !(flags & FLAG_A))
				continue;
				
			t_symbol symbol;
			symbol.value = sym64->st_value;
			symbol.name = name;
			symbol.type = get_symbol64_type(sym64, file->u.file64.shdr, file->u.file64.ehdr);
			symbol.size = sym64->st_size;
			symbol.bind = ELF64_ST_BIND(sym64->st_info);
			symbol.sym_type = ELF64_ST_TYPE(sym64->st_info);
			add_symbol_to_file(file, &symbol);
		}
	}

}

static int symbol_should_be_skipped(t_symbol *sym, unsigned char flags)
{
/* 	if (sym->type == 't')
		return 0; */
	if (sym->type == 'U' && sym->name[0] == '\0')
		return 1; // Skip symbols with null name
	if (!(flags & FLAG_A) && (sym->type == 'a' || sym->type == 'N'))
		return 1; // Skip debugger-only symbols if -a is not set
	if (flags & FLAG_U && sym->type != 'U' && sym->type != 'w')
		return 1; // Only allow undefined symbols if -u is set
	if (flags & FLAG_G && !(sym->bind == STB_GLOBAL || sym->bind == STB_WEAK))
		return 1;
	
	return 0;
}

static void print_values(t_file *file, t_symbol *sym)
{
	char *padding = NULL;
	(void)file;
	(void)padding;
	
	if (sym->value != 0 || sym->type == 'T' || sym->type == 't') {
		
 		printf("%016lx", sym->value);
		fflush(stdout);

	}
	else if (sym->type == 'a') {
		ft_printf("%s", "0000000000000000");
	}
	else {
		ft_printf("%s", "                ");
	}

		ft_printf(" %c %s\n", sym->type, sym->name);
}

static void print_symbols(t_file *file, unsigned char flags)
{
	t_symbol_node *current = file->symbols.head;

	while (current != NULL) {

		t_symbol *sym = &current->symbol;

		if (!symbol_should_be_skipped(sym, flags))
		{
			print_values(file, sym);
		}
		current = current->next;
	}
}

void nm_process_files(t_nm *nm)
{
	int i;

	i = 0;
	while (nm->files[i].filename != NULL)
	{
		if (extract_file_data(&nm->files[i]) != 0 || parse_elf_headers(&nm->files[i]) != 0)
		{
			if (nm->files[i].data != NULL)
				nm_unmap_file(&nm->files[i]);
			nm->exit_code = 1;
			i++;
			continue;
		}

		extract_symbols(&nm->files[i], nm->flags);
		sort_symbols(&nm->files[i].symbols, nm->flags);
		print_symbols(&nm->files[i], nm->flags);
		nm_unmap_file(&nm->files[i]);
		i++;
	}
}