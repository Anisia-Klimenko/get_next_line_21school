#include "get_next_line.h"

int	ft_check_endl(char *buf, int fd)
{
	int	i;
	int	endl;
	int	len;

	endl = 0;
	len = 0;
	while (!endl)
	{
		i = 0;
		read(fd, buf, BUFFER_SIZE);
		while (i < BUFFER_SIZE - 1 && buf[i] != '\0' && buf[i] != '\n')
			i++;
		len += i + 1;
		if (buf[i] == '\0' || buf[i] == '\n')
			endl = 1;
	}
	return (len - 1);
}

char	*ft_copy(char *s, char *buf, int fd)
{
	int	len;
	int	i;

	len = ft_check_endl(buf, fd);
	printf("buf - %s\n", buf);
	i = 0;
	while (i < len)
	{
		read(fd, buf, 1);
		s[i] = buf[0];
		i++;
	}
	printf("---%s\n", s);
	return (s);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	char		*s;
	int static	index = 0;
	int			count;
	// int			rt;

	if (fd < 0)
		return (0);
	count = 0;
	while (read(fd, buf, 1) && count < index)
	{
		if (buf[0] == '\n' && buf[0] == '\0')
			count++;
	}
	s = malloc(sizeof(char) * (ft_check_endl(buf, fd) + 1));
	if (!s)
		return (0);
	index++;
	printf("%d - ", index);
	s = ft_copy(s, buf, fd);
	return (s);
}

int	main(void)
{
	int		fd;
	// char	buf[BUFFER_SIZE];

	fd = open("test.txt", O_RDONLY);
	// printf("\nline len - %d\n", ft_check_endl(buf, fd));
	if (fd >= 0)
	{
		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
		close(fd);
	}
	return (0);
}
