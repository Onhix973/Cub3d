#include "structs.h"
#include "raycast.h"
#include "cub3D.h"
#include <math.h>

void	update_ray_step_and_dist(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->tile_step.x = -1;
		ray->dist_next_hgrid = (ray->pos.x - ray->map_tile.x) \
		* ray->delta_dist.x;
	}
	else
	{
		ray->tile_step.x = 1;
		ray->dist_next_hgrid = (ray->map_tile.x + 1.0 - ray->pos.x) \
		* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->tile_step.y = -1;
		ray->dist_next_vgrid = (ray->pos.y - ray->map_tile.y) \
		* ray->delta_dist.y;
	}
	else
	{
		ray->tile_step.y = 1;
		ray->dist_next_vgrid = (ray->map_tile.y + 1.0 - ray->pos.y) \
		* ray->delta_dist.y;
	}
}

void	update_ray(t_ray *ray, t_player *player)
{
	(void)player;
	ray->map_tile.x = (int)ray->pos.x;
	ray->map_tile.y = (int)ray->pos.y;
	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	ray->cos_view_angle = ray->dir.x * player->dir.x + ray->dir.y * player->dir.y;
	update_ray_step_and_dist(ray);
}

void	teleport_ray(t_ray *ray, t_portal *in, t_portal *out, t_player *player)
{
	t_vector	in_facing_vec;
	t_vector	out_facing_vec;
	t_vector	in_dir;
	t_vector	out_dir;
	t_vector	relative_pos;
	float		angle;

	relative_pos.x = ray->pos.x - in->world_x;
	relative_pos.y = ray->pos.y - in->world_y;
	facing_to_vector(in->facing, &in_facing_vec);
	facing_to_vector(out->facing, &out_facing_vec);
	in_dir.x = -in_facing_vec.x;
	in_dir.y = -in_facing_vec.y;
	out_dir.x = out_facing_vec.x;
	out_dir.y = out_facing_vec.y;
	angle = compute_rotation_angle(&in_dir, &out_dir);
	rotate_dvector(&ray->dir, angle);
	rotate_vector(&relative_pos, angle);
	ray->pos.x = out->world_x + relative_pos.x;
	ray->pos.y = out->world_y + relative_pos.y;
	update_ray(ray, player);
}

// t_hit	cast_ray_segment(t_data *game, t_double_vector origin, t_double_vector dir)
// {
// 	//Raycast standard
// 	//Si portail trouvé, transformation du rayon dans l'espace du portail de sortie
// 	//Si mur simple, calcul distance projetée et renvoi standard 
// }

// double	cast_ray_recursive(t_data *game, t_ray *ray, t_hit *hit_data, int depth)
// {
// 	t_ray	new_ray;
// 	double	rest_dist;

// 	if (depth > MAX_PORTAL_RECURSION)
// 		return (-1);
// 	*hit_data = cast_ray_segment();
// 	if (check_for_portal(&game->portals.a, ray, hit_data))
// 	{
// 		if (!game->portals.linked)
// 			return (hit_data->proj_wall_hit_dist);
// 		new_ray = *ray;
// 		teleport_ray(&new_ray, &game->portals.a, &game->portals.b, game->player);
// 		rest_dist = cast_ray_recursive(game, &new_ray, hit_data, depth + 1);
// 		return (hit_data->proj_wall_hit_dist + rest_dist);
// 	}
// 	if (check_for_portal(&game->portals.b, ray, hit_data))
// 	{
// 		if (!game->portals.linked)
// 			return (hit_data->proj_wall_hit_dist);
// 		new_ray = *ray;
// 		teleport_ray(&new_ray, &game->portals.b, &game->portals.a, game->player);
// 		rest_dist = cast_ray_recursive(game, &new_ray, hit_data, depth + 1);
// 		return (hit_data->proj_wall_hit_dist + rest_dist);
// 	}
// 	return (hit_data->proj_wall_hit_dist);
// }