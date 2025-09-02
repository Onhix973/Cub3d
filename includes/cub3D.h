#ifndef CUB3D_H
# define CUB3D_H

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define MAP_WIDTH 30
#define MAP_HEIGHT 14
#define TILE_SIZE 64
#define FOV (3.14159265358979323846 / 2)
#define HITBOX_OFFSET 0.2f
#define ROTATION_SPEED 2.0f
#define BASE_MOVE_SPEED 3.0f
#define MOUSE_SENSITIVITY 0.0009f

#define FLOOR_COLOR 0x2F4F4F
#define CEILING_COLOR 0x87CEEB

#define MINIMAP_SCALE 15
#define MINIMAP_X 5
#define MINIMAP_Y 5
#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200
#define MINIMAP_MARGIN 20

#define FS_MAP_SCALE 13
#define FS_MAP_WIDTH (MAP_WIDTH * FS_MAP_SCALE)
#define FS_MAP_HEIGHT (MAP_HEIGHT * FS_MAP_SCALE)
#define FS_MAP_X ((WIN_WIDTH - FS_MAP_WIDTH) / 2)
#define FS_MAP_Y ((WIN_HEIGHT - FS_MAP_HEIGHT) / 2)

#define CROSSHAIR_COLOR 0xFFFFFF
#define CROSSHAIR_SIZE 10

#define N_WALL_TEXTURE "textures/wall.xpm"
#define W_WALL_TEXTURE "textures/portalwall.xpm"
#define E_WALL_TEXTURE "textures/Asset-16_1.xpm"
#define S_WALL_TEXTURE "textures/Asset-17_1.xpm"

#endif