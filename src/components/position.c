#include "entities.h"

void	position_new(void *comp, va_list args)
{
	comp_pos_t *pos = comp;
	pos->current.x = (float)va_arg(args, double);
	pos->current.y = (float)va_arg(args, double);
}

void	comp_position_register()
{
	ecs_comp_register(COMP_POS, sizeof(comp_pos_t), position_new, NULL);
}