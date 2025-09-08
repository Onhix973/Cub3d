#include <unistd.h>

int	count_fields(const char *s, char c)
{
	int	i;
	int	count;

	if (s == NULL)
		return (0);
	i = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}