#include "parsing.h"
#include "gnl_noleak.h"

static int	read_file(int fd, char **out_buf)
{
	char *acc;
	char *line;

	*out_buf = NULL;
	acc = (char *)malloc(1);
	if (!acc)
		return (write_error(MALLOC_ERR));
	acc[0] = '\0';
	line = gnl_noleak(fd);
	while (line)
	{
		acc = ft_strjoin_re(acc, line);
		free(line);
		if (!acc)
			return (write_error(MALLOC_ERR));
		line = gnl_noleak(fd);
	}
	*out_buf = acc;
	return (1);
}

int	load_lines(int fd, char ***out_lines)
{
	char *buf;
	char	**lines;

	*out_lines = NULL;
	if (read_file(fd, &buf) == 0)
		return (write_error("Error:\n reading file\n"));
	lines = split_with_sep(buf, '\n');
	free(buf);
	if (lines == NULL)
		return (write_error("Error:\n splitting lines\n"));
	*out_lines = lines;
	return (1);
}