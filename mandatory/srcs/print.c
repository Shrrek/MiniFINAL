#include "../incs/minishell.h"

void	ft_putstr_fd(int fd, char *str, int mode)
{
	char	*nl_str;

	if (str)
	{
		if (mode == 1)
		{
			nl_str = ft_strjoin(str, "\n");
			write(fd, nl_str, ft_strlen(nl_str));
			free(nl_str);
		}
		else
			write(fd, str, ft_strlen(str));
	}
}

void	ft_print3dstr(char ***str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
		{
			printf("cadena %d\n", i);
			ft_print2dstr(str[i]);
		}
		printf("-----\n");
	}
}

void	ft_print2dstr(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			printf("%s>\n", str[i]);
	}
}
