#include "entities.h"
#include "assets.h"

uint32_t	ents_sprite(fvec_t pos)
{
	uint32_t id = ecs_create();
	ecs_comp_add(id, COMP_POS, 2, pos.x, pos.y);
	ecs_comp_add(id, COMP_SPRITE, 1, ASSET_SPRITE);
	return (id);
}

void	ents_register()
{
	comp_position_register();
	comp_sprite_register();
}