/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:14:42 by niceguy           #+#    #+#             */
/*   Updated: 2023/04/10 22:20:29 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <stdint.h>

typedef struct
{
	int32_t		x;
	int32_t		y;
}	ivec_t;

typedef struct
{
	uint32_t	x;
	uint32_t	y;
}	uvec_t;

typedef struct
{
	double	x;
	double	y;
}	dvec_t;

typedef struct
{
	float	x;
	float	y;
}	fvec_t;

#endif