void	rgb_to_hex(int rgb[3], int *hex)
{
	*hex = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}
