#include "structs.h"
#include "raycast.h"
#include "cub3D.h"
#include <math.h>


typedef struct s_ray_hit
{
	t_double_vector	origin;
	t_double_vector	dir;
	t_double_vector	hit_pos;
	double			len_a;
	double			len_b;
	int				tile_x;
	int				tile_y;
	int				wall_side;
	double			tex_u;
	bool			is_portal;
	t_portal		*portal;
	int				screen_top;
	int				screen_bottom;
	int				clip_top;
	int				clip_bottom;
}	t_ray_hit;

typedef struct s_raybuffer
{
	t_ray_hit	hits[MAX_PORTAL_RECURSION];
	int			count;
}	t_raybuffer;


void	ray_buffer_push(t_raybuffer *buffer, t_ray_hit *hit)
{
	if (buffer->count >= MAX_PORTAL_RECURSION)
		return ;
	buffer->hits[buffer->count++] = *hit;
}

bool	check_portal_hit(t_portal *portal, t_ray *ray, t_hit *hit_data)
{
	if (!portal->active)
		return (false);		
	if (ray->map_tile.x != portal->map_x || ray->map_tile.y != portal->map_y)
		return (false);
	if (hit_data->wall_tile_hit_side != portal->side)
		return (false);
	if (portal->side == HORIZONTAL_HIT)
		return ((portal->graphical_facing == WEST && ray->dir.x < 0) || (portal->graphical_facing == EAST && ray->dir.x > 0));
	else
		return ((portal->graphical_facing == NORTH && ray->dir.y < 0) || (portal->graphical_facing == SOUTH && ray->dir.y > 0));
}

t_double_vector	transform_through_portal(t_portal *in, t_portal *out, t_double_vector hit_pos)
{
	t_double_vector	new_origin;
	t_vector		relative_pos;

	relative_pos.x = hit_pos.x - in->segment_start.x;
	relative_pos.y = hit_pos.y - in->segment_start.y;
	new_origin.x = out->segment_start.x + relative_pos.x;
	new_origin.y = out->segment_start.y + relative_pos.y;
	return (new_origin);
}

float	get_angle_between_portals(t_portal *in, t_portal *out)
{
	t_vector	in_dir;
	t_vector	out_dir;

	facing_to_vector(in->facing, &in_dir);
	in_dir.x = -in_dir.x;
	in_dir.y = -in_dir.y;
	facing_to_vector(out->facing, &out_dir);
	return (compute_rotation_angle(&in_dir, &out_dir));
}

void	cast_ray_buffer(t_data *game, t_raybuffer *buffer, t_ray *ray, int screenx, int depth)
{
	t_hit	hit_data;
	t_ray_hit	ray_hit;

	if (depth >= MAX_PORTAL_RECURSION)
		return ;
	hit_data = cast_ray(game->map, ray);
	ray_hit.origin = ray->origin;
	ray_hit.dir = ray->dir;
	ray_hit.hit_pos = ray->pos;
	ray_hit.tile_x = ray->map_tile.x;
	ray_hit.tile_y = ray->map_tile.y;
	ray_hit.wall_side = hit_data.wall_tile_hit_side;
	ray_hit.screen_top = 0;
	ray_hit.screen_bottom = 0;
	if (check_portal_hit(&game->portals.a, ray, &hit_data))
	{
		ray_hit.is_portal = true;
		ray_hit.portal = &game->portals.a;
	}
	else if (check_portal_hit(&game->portals.b, ray, &hit_data))
	{
		ray_hit.is_portal = true;
		ray_hit.portal = &game->portals.b;
	}
	else
	{
		ray_hit.is_portal = false;
		ray_hit.portal = NULL;
	}
	ray_buffer_push(buffer, &ray_hit);
	if (ray_hit.is_portal && ray_hit.portal && depth < MAX_PORTAL_RECURSION)
	{
		t_double_vector	new_origin = ray->origin;
		t_double_vector	new_dir = ray->dir;
		t_ray	new_ray = *ray;
		if (ray_hit.portal == &game->portals.a)
		{
			new_origin = transform_through_portal(&game->portals.a, &game->portals.b, ray_hit.hit_pos);
			rotate_dvector(&new_dir, get_angle_between_portals(&game->portals.a, &game->portals.b));
			new_ray.origin = new_origin;
			new_ray.pos = new_origin;
			new_ray.dir = new_dir;
			new_ray.map_tile.x = (int)new_origin.x;
			new_ray.map_tile.y = (int)new_origin.y;
		}
		else if (ray_hit.portal == &game->portals.b)
		{
			new_origin = transform_through_portal(&game->portals.b, &game->portals.a, ray_hit.hit_pos);
			rotate_dvector(&new_dir, get_angle_between_portals(&game->portals.b, &game->portals.a));
			new_ray.origin = new_origin;
			new_ray.pos = new_origin;
			new_ray.dir = new_dir;
			new_ray.map_tile.x = (int)new_origin.x;
			new_ray.map_tile.y = (int)new_origin.y;
		}
		cast_ray_buffer(game, buffer, &new_ray, screenx, depth + 1);
	}
}


void	render_raybuffer(t_raybuffer *raybuffer)
{
	int	i;

	i = raybuffer->count - 1;
	while (i >= 0)
	{
		if (raybuffer->hits[i].is_portal)
			draw_portal_column(hit);
		else
			draw_wall_column(hit);
		i--;
	}

}

// typedef struct s_ray_segment
// {
// 	bool	active;
// 	t_ray	ray;
// 	t_hit	hit;
// }	t_ray_segment;

// t_ray_segment	buffer[WIN_WIDTH][MAX_PORTAL_RECURSION];
// int		segment_count;

// void	clear_buffer(void)
// {
// 	memset(buffer, 0, sizeof(buffer));
// }

// void	portal_builder_wrapper(t_data *game, int x)
// {
// 	if (buffer[x][0].active)
// 		portal_builder(game, &buffer[x][0].ray, &buffer[x][0].hit, x);
// }
// // INIT_RAY********************************************************************/
// void	init_ray_step_and_dist_new(t_ray *ray)
// {
// 	if (ray->dir.x < 0)
// 	{
// 		ray->tile_step.x = -1;
// 		ray->dist_next_hgrid = (ray->pos.x - ray->map_tile.x) \
// 		* ray->delta_dist.x;
// 	}
// 	else
// 	{
// 		ray->tile_step.x = 1;
// 		ray->dist_next_hgrid = (ray->map_tile.x + 1.0 - ray->pos.x) \
// 		* ray->delta_dist.x;
// 	}
// 	if (ray->dir.y < 0)
// 	{
// 		ray->tile_step.y = -1;
// 		ray->dist_next_vgrid = (ray->pos.y - ray->map_tile.y) \
// 		* ray->delta_dist.y;
// 	}
// 	else
// 	{
// 		ray->tile_step.y = 1;
// 		ray->dist_next_vgrid = (ray->map_tile.y + 1.0 - ray->pos.y) \
// 		* ray->delta_dist.y;
// 	}
// }

// void	init_ray_new(t_ray *ray, t_player *player, int screen_x)
// {
// 	ray->win_x_pos = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
// 	ray->dir.x = player->dir.x + player->camera_plane.x * ray->win_x_pos;
// 	ray->dir.y = player->dir.y + player->camera_plane.y * ray->win_x_pos;
// 	ray->origin.x = player->pos.x;
// 	ray->origin.y = player->pos.y;
// 	ray->pos.x = ray->origin.x;
// 	ray->pos.y = ray->origin.y;
// 	ray->map_tile.x = (int)ray->pos.x;
// 	ray->map_tile.y = (int)ray->pos.y;
// 	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
// 	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
// 	ray->cos_view_angle = ray->dir.x * player->dir.x + ray->dir.y \
// 	* player->dir.y;
// 	init_ray_step_and_dist_new(ray);
// }
// //*************************************************************************** */

// #include <stdio.h>
// bool	ray_segment_intersection(t_ray *ray, t_portal *portal, double *t, double *u)
// {
// 	t_double_vector	v1;
// 	t_double_vector	v2;
// 	t_double_vector	v3;
// 	double			cross1;
// 	double			cross2;
// 	double			denom;

// 	v1.x = portal->segment_start.x - ray->origin.x;
// 	v1.y = portal->segment_start.y - ray->origin.y;
// 	v2.x = portal->segment_end.x - portal->segment_start.x;
// 	v2.y = portal->segment_end.y - portal->segment_start.y;
// 	v3.x = -ray->dir.x;
// 	v3.y = -ray->dir.y;
// 	denom = v2.x * v3.y - v3.y * v2.x;
// 	if (fabs(denom) < 0.0001)
// 		return (false);
// 	cross1 = v2.x * v1.y - v2.y * v1.x;
// 	*t = cross1 / denom;
// 	cross2 = v1.x * ray->dir.y - v1.y * ray->dir.x;
// 	*u = -cross2 / denom;
// 	if (*t >= 0 && *u >=0 && *u <= 1)
// 		return (true);
// 	return (false);
// }

// void transform_ray_through_portal(t_ray *ray, t_portal *src, t_portal *dest, double u)
// {
// 	t_double_vector	src_relative;
// 	t_double_vector	dest_relative;
// 	double			src_angle;
// 	double			dest_angle;
// 	double			delta_angle;
// 	double			dir_angle;

// 	src_relative.x = src->segment_end.x - src->segment_start.x;
// 	src_relative.y = src->segment_end.y - src->segment_start.y;
// 	dest_relative.x = dest->segment_end.x - dest->segment_start.x;
// 	dest_relative.y = dest->segment_end.y - dest->segment_start.y;
// 	ray->origin.x = dest->segment_start.x + u * dest_relative.x;
// 	ray->origin.y = dest->segment_start.y + u * dest_relative.y;
// 	ray->pos = ray->origin;
// 	src_angle = atan2(src_relative.y, src_relative.x);
// 	dest_angle = atan2(dest_relative.y, dest_relative.x);
// 	delta_angle = dest_angle - src_angle;
// 	dir_angle = atan2(ray->dir.y, ray->dir.x);
// 	dir_angle += delta_angle;
// 	ray->dir.x = cos(dir_angle);
// 	ray->dir.y = sin(dir_angle);
// 	ray->map_tile.x = (int)ray->pos.x;
// 	ray->map_tile.y = (int)ray->pos.y;
// 	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
// 	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
// 	init_ray_step_and_dist_new(ray);
// }

// int		check_portal_intersection(t_data *game, t_ray *ray, double *out_u, t_portal **hit_portal)
// {
// 	t_portal	*a = &game->portals.a;
// 	t_portal	*b = &game->portals.b;
// 	double	t;
// 	double	u;

// 	if (!game->portals.linked)
// 		return (-1);
// 	if (a->active && ray_segment_intersection(ray, a, &t, &u))
// 	{
// 		*out_u = u;
// 		*hit_portal = a;
// 		return (0);
// 	}
// 	if (b->active && ray_segment_intersection(ray, b, &t, &u))
// 	{
// 		*out_u = u;
// 		*hit_portal = b;
// 		return (1);
// 	}
// 	return (-1);
// }

// t_hit	cast_ray_segment(t_data *game, t_ray *ray, t_portal **hit_portal_out, double *portal_u)
// {
// 	t_hit	hit_data;

// 	*hit_portal_out = NULL;
// 	while (1)
// 	{
// 		if (ray->dist_next_hgrid < ray->dist_next_vgrid)
// 		{
// 			ray->dist_next_hgrid += ray->delta_dist.x;
// 			ray->map_tile.x += ray->tile_step.x;
// 			hit_data.wall_tile_hit_side = HORIZONTAL_HIT;
// 		}
// 		else
// 		{
// 			ray->dist_next_vgrid += ray->delta_dist.y;
// 			ray->map_tile.y += ray->tile_step.y;
// 			hit_data.wall_tile_hit_side = VERTICAL_HIT;
// 		}
// 		if (game->map[ray->map_tile.y][ray->map_tile.x] == '1')
// 		{
// 			if (check_portal_intersection(game, ray, portal_u, hit_portal_out) >= 0)
// 			{
// 				hit_data.proj_wall_hit_dist = compute_projected_wall_dist(ray, hit_data.wall_tile_hit_side);
// 				return (hit_data);
// 			}
// 			else
// 			{
// 				hit_data.proj_wall_hit_dist = compute_projected_wall_dist(ray, hit_data.wall_tile_hit_side);
// 				return (hit_data);
// 			}
// 		}
// 	}
// }

// void cast_ray_recursive(t_data *game, t_ray *ray, int x, int depth)
// {
// 	t_portal	*hit_portal = NULL;
// 	t_hit	hit_data;
// 	double u;

// 	if (depth >= MAX_PORTAL_RECURSION)
// 		return ;
// 	hit_data = cast_ray_segment(game, ray, &hit_portal, &u);
// 	buffer[x][depth].ray = *ray;
// 	buffer[x][depth].active = true;
// 	buffer[x][depth].hit = hit_data;
// 	if (hit_portal)
// 	{
// 		t_portal	*dest;
// 		t_ray new_ray = *ray;
// 		if (hit_portal == &game->portals.a)
// 			dest = &game->portals.b;
// 		else
// 			dest = &game->portals.a;
// 		transform_ray_through_portal(&new_ray, hit_portal, dest, u);
// 		cast_ray_recursive(game, &new_ray, x, depth + 1);
// 	}
// }

// void	render_from_buffer(t_data *game, t_player *player)
// {
// 	int	x;
// 	int	depth;

// 	x = 0;
// 	while (x < WIN_WIDTH)
// 	{
// 		depth = MAX_PORTAL_RECURSION - 1;
// 		while (depth >= 0)
// 		{
// 			if (buffer[x][depth].active)
// 			{
// 				t_ray_segment *segment =  &buffer[x][depth];
// 				draw_wall_slice(x, game, &segment->ray, &segment->hit, player);
// 			}
// 			depth--;
// 		}
// 		x++;
// 	}
// }