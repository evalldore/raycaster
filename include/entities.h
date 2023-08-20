#ifndef ENTITIES_H
#define ENTITIES_H

#include "ecs.h"
#include "vector.h"

enum	comp_e
{
	COMP_NONE,
	COMP_POS,
	COMP_SPRITE
};

typedef struct comp_pos
{
	fvec_t	current;
	fvec_t	last;
}	comp_pos_t;

typedef struct comp_sprite
{
	uint32_t	index;
}	comp_sprite_t;

void	comp_sprite_register(void);
void	comp_position_register(void);

void		ents_register(void);
uint32_t	ents_sprite(fvec_t pos);

#endif