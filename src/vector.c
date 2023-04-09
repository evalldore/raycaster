/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:13:07 by evallee-          #+#    #+#             */
/*   Updated: 2023/03/28 03:28:49 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vec_add(void *dest, void *src1, void *src2)
{
	((t_ivec *)dest)->x = ((t_ivec *)src1)->x + ((t_ivec *)src2)->x;
}

void	vec_sub(void *dest, void *src1, void *src2)
{
	((t_ivec *)dest)->x = ((t_ivec *)src1)->x - ((t_ivec *)src2)->x;
}
