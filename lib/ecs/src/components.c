/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:14:52 by niceguy           #+#    #+#             */
/*   Updated: 2023/04/02 06:50:08 by niceguy          ###   ########.fr       */
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
	ptr = g_components[comp].new(args);
	va_end(args);
	g_components[comp].ptrs[ent_id] = ptr;
	return (ptr);
}

void	ecs_comp_remove(uint32_t ent_id, int comp)
{
	if (ent_id >= ecs_num() || ent_id >= MAX_ENTS || comp >= MAX_COMP)
		return ;
	if (!g_components[comp].ptrs[ent_id])
		return ;
	if (!g_components[comp].dest)
		return ;
	g_components[comp].dest(g_components[comp].ptrs[ent_id]);
	g_components[comp].ptrs[ent_id] = NULL;
}

void	*ecs_comp_get(uint32_t ent_id, int comp)
{
	if (ent_id >= ecs_num() || ent_id >= MAX_ENTS || comp >= MAX_COMP)
		return (NULL);
	return (g_components[comp].ptrs[ent_id]);
}

void	ecs_comp_register(int comp, t_constructor c, t_destructor d)
{
	if (comp >= MAX_COMP || !c || ! d)
		return ;
	g_components[comp].new = c;
	g_components[comp].dest = d;
}
