#include "../incs/minishell.h"

int	ft_treat_fds(int *infd, int *outfd, char *rest, char **here_doc)
{
	*infd = ft_search_infd(rest);
	if (*infd > 0)
	{
		printf("fd de entda \n");
		if (*infd == 2)
		{
			*infd = 0; //temporal
			*here_doc = ft_get_here_doc(rest);
		}
		else
			*infd = ft_set_infd(rest);
	}
	if (*infd == -1)
	{
		printf("Invalid file\n");
		free(rest);
		return (-1);
	}
	*outfd = ft_set_outfd(rest);
	if (*outfd == -1)
	{
		printf("Invalid file\n");
		free(rest);
		return (-1);
	}
	free(rest);
	return (0);
}
