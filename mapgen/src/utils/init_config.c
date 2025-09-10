#include "mapgen.h"
#include <stdlib.h>

void init_config(t_mapgen *config)
{
	config->map = NULL;
	config->width = 0;
	config->height = 0;
}