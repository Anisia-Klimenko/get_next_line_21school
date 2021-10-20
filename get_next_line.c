#include "get_next_line.h"

char	*ft_check_save(char *str, char **save, char *p, char *tmp)
{
	if (ft_strlen(tmp) == 2 && tmp[1] == '\n')
	{
		str = malloc(sizeof(char) * 2);
		str[0] = tmp[0];
		str[1] = '\0';
		*save = ft_strdup(p);
		// printf("ok\n");
	}
	else
	{
		// printf("okkk\n");
		*p++ = '\0';
		str = ft_strjoin(str, tmp);
		*save = ft_strdup(p);
		// printf("STR (CHECK) -> %s\n", str);
		// printf("SAVE (CHECK) -> %s\n", tmp);
	}
	return (str);
}

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
	// printf("P (SAVE) -> %s\n", p);
	// printf("SAVE (SAVE) -> %s\n", tmp);
	if (p)
	{
		str = ft_check_save(str, save, p, tmp);
		// if (ft_strlen(tmp) == 2 && tmp[1] == '\n')
		// 	tmp[2] = '\n';
		// *p++ = '\0';
		// str = ft_strjoin(str, tmp);
		// tmp = ft_strdup(p);
		// *save = ft_strdup(p);
	}
	else
	{
		str = ft_strjoin(str, tmp);
		*save = NULL;
	}
	// printf("SAVE (SAVE) -> %s\n", *save);
	// printf("STR (SAVE) -> %s\n", str);
	return (str);
}

char	*ft_no_save(int fd, char **save, char *str)
{
	int		rt;
	char	buf[BUFFER_SIZE + 1];
	char	*p;

	p = NULL;
	// printf("STR (NO SAVE BW) -> %s\n", str);
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
		// printf("STR (NO SAVE IW) -> %s\n", str);
		if (!p)
			rt = read(fd, buf, BUFFER_SIZE);
	}
	// printf("SAVE (NO SAVE) -> %s\n", *save);
	// printf("STR (NO SAVE) -> %s\n", str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*str;

	str = NULL;
	if (fd < 0)
		return (NULL);
	// printf("SAVE -> %s\n", save);
	if (save)
		str = ft_save(&save, str);
	if (!save)
		str = ft_no_save(fd, &save, str);
	if (!str && !save)
		return (0);
	return (str);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*s;

// 	fd = open("test.txt", O_RDONLY);
// 	s = NULL;
// 	if (fd >= 0)
// 	{
// 		s = get_next_line(fd);
// 		while (s)
// 		{
// 			printf("STR IN MAIN -> %s\n\n", s);
// 			free(s);
// 			s = get_next_line(fd);
// 		}
// 		close(fd);
// 	}
// 	return (0);
// }
