/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:14:52 by niceguy           #+#    #+#             */
/*   Updated: 2023/05/24 00:46:37 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ecs.h"

static t_component	g_components[MAX_COMP];

void	*ecs_comp_add(uint32_t ent_id, int comp, int argc, ...)
{
	void	*ptr;
	va_list	args;

	if (ent_id >= ecs_num() || ent_id >= MAX_ENTS || comp >= MAX_COMP)
		return (NULL);
	if (!g_components[comp].new)
		return (NULL);
	va_start(args, argc);
	ptr = malloc(g_components[comp].size);
	g_components[comp].new(ptr, args);
	va_end(args);
	g_components[comp].ptrs[ent_id] = ptr;
	return (ptr);
}

void	ecs_comp_remove(uint32_t ent_id, int comp_idx)
{
	if (ent_id >= ecs_num() || ent_id >= MAX_ENTS || comp_idx >= MAX_COMP)
		return ;
	if (!g_components[comp_idx].ptrs[ent_id])
		return ;
	if (g_components[comp_idx].dest)
		g_components[comp_idx].dest(g_components[comp_idx].ptrs[ent_id]);
	free(g_components[comp_idx].ptrs[ent_id]);
	g_components[comp_idx].ptrs[ent_id] = NULL;
}

void	*ecs_comp_get(uint32_t ent_id, int comp)
{
	if (ent_id >= ecs_num() || ent_id >= MAX_ENTS || comp >= MAX_COMP)
		return (NULL);
	return (g_components[comp].ptrs[ent_id]);
}

void	ecs_comp_register(int comp, size_t s, t_const c, t_dest d)
{
	if (comp >= MAX_COMP || !c)
		return ;
	g_components[comp].size = s;
	g_components[comp].new = c;
	g_components[comp].dest = d;
}
