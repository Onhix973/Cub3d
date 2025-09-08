#include "libft.h"

char	*ft_strjoin_re(char *s1, char const *s2)
{
	char	*old;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	old = s1;
	s1 = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1)
	{
		free(old);
		return (NULL);
	}
	while (++i < ft_strlen(old))
		s1[i] = old[i];
	while (++j < ft_strlen(s2))
	{
		s1[i] = s2[j];
		i++;
	}
	free(old);
	s1[i] = '\0';
	return (s1);
}
