#include "../incs/minishell.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	new_len;
	char	*dst;

	if (!str)
		return (NULL);
	if (start > ft_strlen((char *)str))
		return (ft_strdup(""));
	str = str + start;
	new_len = ft_strlen((char *)str);
	if (len > new_len)
		len = new_len;
	dst = ft_strndup(str, len);
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (NULL);
	ft_strncpy(dest, s1, s1_len + 1);
	ft_strlcat(&dest[s1_len], s2, s2_len + 1);
	return (dest);
}

char	*ft_join_chr(char *str, int c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!new_str)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
	}
	new_str[i] = c;
	new_str[++i] = '\0';
	return (new_str);
}
