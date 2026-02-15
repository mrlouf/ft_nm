/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:35:53 by nicolas           #+#    #+#             */
/*   Updated: 2026/02/15 15:01:01 by nicolas          ###   ########.fr       */
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

    // Trim leading underscores for comparison
    char *name_a = ft_strtrim(sym_a->symbol.name, "_");
    char *name_b = ft_strtrim(sym_b->symbol.name, "_");

    name_a = ft_strtolower(name_a);
    name_b = ft_strtolower(name_b);

    int result = ft_strcmp(name_a, name_b);
    free(name_a);
    free(name_b);
    return result;
}

static int compare_symbols_reverse(const void *a, const void *b)
{
    return compare_symbols(b, a); // Reverse the order of comparison
}

static void sort_symbols_in_array(t_symbol_node ***array, size_t count, unsigned char flags)
{
    qsort(*array, count, sizeof(t_symbol_node *), (flags & FLAG_R) ? compare_symbols_reverse : compare_symbols);
}

void sort_symbols(t_symbol_list *list, unsigned char flags)
{
    t_symbol_node **array = NULL;

    array = create_array(list);
    if (!array)
        nm_error("Failed to create array");

    sort_symbols_in_array(&array, list->count, flags);
    rebuild_list_from_array(list, array);

    free(array);
}