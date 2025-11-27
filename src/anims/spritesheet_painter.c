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

static void	blit_frame(t_img *sheet, int sx, int sy, int w, int h, t_img *trg, 
	int dx, int dy)
{
	char	*data_sheet;
	int		x;
	int		y;
	int		src_pos;
	unsigned int pixel_color;
	int		dst_pos;

	y = 0;
	data_sheet = mlx_get_data_addr(sheet->ptr, &sheet->bpp, &sheet->size_line, 
		&sheet->endian);
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			src_pos = (sy + y) * sheet->size_line + (sx + x) * (sheet->bpp / 8);
			dst_pos = (dy + y) * trg->size_line + (dx + x) * (trg->bpp / 8);
			pixel_color = *(unsigned int *)(data_sheet + src_pos);
			if ((pixel_color & 0xFFFFFF) != 0)
				*(unsigned int *)(trg->data + dst_pos) = pixel_color;
			x++;
		}
		y++;
	}
}

void	draw_sprite_sheet_anim(t_sprite_sheet *anim, t_img *screen)
{
	int	frame_x;	
	int	frame_y;

	frame_x = (anim->curr_frame % anim->frames_per_row) * anim->frame_w;
	frame_y = (anim->curr_frame / anim->frames_per_row) * anim->frame_h;
	blit_frame(&anim->sheet, frame_x, frame_y, anim->frame_w, anim->frame_h, 
	screen, anim->x, anim->y);
}
