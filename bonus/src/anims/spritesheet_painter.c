/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritesheet_painter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:02:51 by tlutz             #+#    #+#             */
/*   Updated: 2025/11/28 15:02:52 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "mlx.h"

void	update_sprite_sheet(t_sprite_sheet *anim, float delta_time)
{
	anim->elapsed_time += delta_time;
	if (anim->elapsed_time >= anim->frame_time)
	{
		if (anim->looped)
			anim->curr_frame = (anim->curr_frame + 1) % anim->num_frames;
		else
		{
			if (anim->curr_frame < anim->num_frames - 1)
				anim->curr_frame++;
		}
		anim->elapsed_time = 0;
	}
}

static void	blit_frame(t_img *sheet, t_blit_data *data, t_img *trg)
{
	char			*data_sheet;
	t_int_vector	count;
	int				src_pos;
	unsigned int	pixel_color;
	int				dst_pos;

	count.y = 0;
	data_sheet = mlx_get_data_addr(sheet->ptr, &sheet->bpp, &sheet->size_line,
			&sheet->endian);
	while (count.y < data->img_size.y)
	{
		count.x = 0;
		while (count.x < data->img_size.x)
		{
			src_pos = (data->frame_coords.y + count.y) * sheet->size_line
				+ (data->frame_coords.x + count.x) * (sheet->bpp / 8);
			dst_pos = (data->anim_coords.y + count.y) * trg->size_line
				+ (data->anim_coords.x + count.x) * (trg->bpp / 8);
			pixel_color = *(unsigned int *)(data_sheet + src_pos);
			if ((pixel_color & 0xFFFFFF) != 0)
				*(unsigned int *)(trg->data + dst_pos) = pixel_color;
			count.x++;
		}
		count.y++;
	}
}

void	draw_sprite_sheet_anim(t_sprite_sheet *anim, t_img *screen)
{
	t_blit_data	data;

	data.frame_coords.x = (anim->curr_frame % anim->frames_per_row)
		* anim->frame_w;
	data.frame_coords.y = (anim->curr_frame / anim->frames_per_row)
		* anim->frame_h;
	data.img_size.x = anim->frame_w;
	data.img_size.y = anim->frame_h;
	data.anim_coords.x = anim->x;
	data.anim_coords.y = anim->y;
	blit_frame(&anim->sheet, &data, screen);
}
