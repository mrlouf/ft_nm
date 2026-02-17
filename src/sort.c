/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:35:53 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/17 16:05:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm.h"

static t_symbol_node **create_array(t_symbol_list *list)
{
    t_symbol_node **array = malloc((list->count * sizeof(t_symbol_node *)) + 1);
    if (!array)
        return NULL;

    t_symbol_node *current = list->head;
    for (size_t i = 0; i < list->count; i++) {
        array[i] = current;
        current = current->next;
    }
    array[list->count] = NULL;
    return array;
}

static void rebuild_list_from_array(t_symbol_list *list, t_symbol_node **array)
{
    list->head = NULL;
    t_symbol_node *current = NULL;

    for (size_t i = 0; i < list->count; i++) {
        if (list->head == NULL) {
            list->head = array[i];
            current = list->head;
        } else {
            current->next = array[i];
            current = current->next;
        }
    }
    if (current)
        current->next = NULL;
}

static int compare_symbols(const void *a, const void *b)
{
    t_symbol_node *sym_a = *(t_symbol_node **)a;
    t_symbol_node *sym_b = *(t_symbol_node **)b;

/*     int a_no_addr = (sym_a->symbol.type == 'U' || sym_a->symbol.type == 'u' ||
                     sym_a->symbol.type == 'w' || sym_a->symbol.type == 'W' ||
                     sym_a->symbol.type == 'N');
    int b_no_addr = (sym_b->symbol.type == 'U' || sym_b->symbol.type == 'u' ||
                     sym_b->symbol.type == 'w' || sym_b->symbol.type == 'W' ||
                     sym_b->symbol.type == 'N');

    // Les symboles sans adresse viennent en premier
    if (a_no_addr != b_no_addr)
        return a_no_addr - b_no_addr; */
    
    // Trim leading underscores for comparison
    char *name_a = ft_strtrim(sym_a->symbol.name, "_.");
    char *name_b = ft_strtrim(sym_b->symbol.name, "_.");
    if (!name_a || !name_b)
        nm_error("memory allocation failed");

    int result = ft_strcasecmp(name_a, name_b);
    if (result == 0)
        result = ft_strcmp(sym_a->symbol.name, sym_b->symbol.name);

    free(name_a);
    free(name_b);

    if (result == 0) {
        if (sym_a->symbol.type > sym_b->symbol.type)
            return 1;
        else if (sym_a->symbol.type <= sym_b->symbol.type)
            return -1;
    }

    return result;
}

static int compare_symbols_reverse(const void *a, const void *b)
{
    return compare_symbols(b, a); // Reverse the order of comparison
}

static void sort_symbols_in_array(t_symbol_node ***array, size_t count, unsigned char flags)
{
    int (*cmp)(const void *, const void *);
    
    cmp = (flags & FLAG_R) ? compare_symbols_reverse : compare_symbols;
    
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = i + 1; j < count; j++)
        {
            if (cmp(&(*array)[i], &(*array)[j]) > 0)
            {
                t_symbol_node *tmp = (*array)[i];
                (*array)[i] = (*array)[j];
                (*array)[j] = tmp;
            }
        }
    }
}

void nm_sort_symbols(t_symbol_list *list, unsigned char flags)
{
    if (list->count <= 1 || (flags & FLAG_P))
        return; // No need to sort if 0 or 1 symbol, or if -p flag is set

    t_symbol_node **array = NULL;

    array = create_array(list);
    if (!array)
        nm_error("Failed to create array");

    sort_symbols_in_array(&array, list->count, flags);
    rebuild_list_from_array(list, array);

    free(array);
}