#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

char	*ft_strnchr(const char *s, int c, int size)
{
	int				flag;
	int				i;
	unsigned char	ch;

	flag = 1;
	ch = (unsigned char)c;
	i = 0;
	while (*s != '\0' && flag)
	{
		if (*s == ch)
			flag = 0;
		s++;
		i++;
	}
	if (flag && ch != '\0')
		return (0);
	if (ch == '\0' && i < size)
		return ((char *)s);
	if (ch == '\0' && i == size)
		return (0);
	s--;
	return ((char *)s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0 && (src || dest))
	{
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	dest = malloc(sizeof(*dest) * (len + 1));
	if (!dest)
		return (0);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		len1;
	int		len2;

	s = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		s = malloc(sizeof(char) * (len1 + len2 + 1));
		if (s)
		{
			ft_memcpy(s, s1, len1);
			ft_memcpy(s + len1, s2, len2);
			s[len1 + len2] = '\0';
		}
	}
	else if (!s1)
		s = ft_strdup(s2);
	else if (!s2)
		s = ft_strdup(s1);
	return (s);
}
