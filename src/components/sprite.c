#include "entities.h"

void	sprite_new(void *comp, va_list args)
{
	comp_sprite_t *sprite = comp;
	sprite->index = va_arg(args, uint32_t);
}

void	comp_sprite_register()
{
	ecs_comp_register(COMP_SPRITE, sizeof(comp_sprite_t), sprite_new, NULL);
}