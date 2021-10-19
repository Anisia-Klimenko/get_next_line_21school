#include "get_next_line.h"

char	*ft_save(char **save, char *str)
{
	char	*tmp;
	char	*p;
	int		len;

	tmp = *save;
	while (*tmp == '\n')
		tmp++;
	len = ft_strlen(tmp);
	p = ft_strnchr(tmp, '\n', len);
	if (p)
	{
		*p = '\0';
		p++;
		tmp = ft_strdup(p);
	}
	str = ft_strjoin(str, *save);
	*save = tmp;
	return (str);
}

char	*ft_no_save(int fd, char **save, char *str)
{
	int		rt;
	char	buf[BUFFER_SIZE + 1];
	char	*p;

	p = NULL;
	rt = read(fd, buf, BUFFER_SIZE);
	while (rt && !p)
	{
		buf[rt] = '\0';
		p = ft_strnchr(buf, '\n', rt);
		if (p)
		{
			*p++ = '\0';
			*save = ft_strdup(p);
		}
		str = ft_strjoin(str, buf);
		rt = read(fd, buf, BUFFER_SIZE);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*str;

	str = NULL;
	if (fd < 0)
		return (NULL);
	if (save)
		str = ft_save(&save, str);
	if (!save)
		str = ft_no_save(fd, &save, str);
	if (!str && !save)
		return (0);
	return (str);
}

int	main(void)
{
	int		fd;
	char	*s;

	fd = open("test.txt", O_RDONLY);
	s = NULL;
	if (fd >= 0)
	{
		s = get_next_line(fd);
		if (s)
		{
			printf("STR IN MAIN -> %s\n", s);
			free(s);
			s = get_next_line(fd);
			printf("STR IN MAIN -> %s\n", s);
			free(s);
			s = get_next_line(fd);
			printf("STR IN MAIN -> %s\n", s);
			if (s)
				printf("S\n");
			free(s);
			s = get_next_line(fd);
			printf("STR IN MAIN -> %s\n", s);
			free(s);
			if (s)
				printf("S\n");
		}
		close(fd);
	}
	return (0);
}
