#include "../incs/minishell.h"

void	ft_check_fd(int fd1, int fd2)
{
	if (fd1 != 0)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
}

int	ft_treat_fds(int *infd, int *outfd, char *rest, char **here_doc)
{
	*infd = ft_search_infd(rest);
	if (*infd > 0)
	{
		if (*infd == 2)
		{
			*infd = 0;
			*here_doc = ft_get_here_doc(rest);
		}
		else
			*infd = ft_set_infd(rest);
	}
	if (*infd == -1)
		printf("Invalid file\n");
	*outfd = ft_set_outfd(rest);
	if (*outfd == -1)
		printf("Invalid file\n");
	free(rest);
	return (0);
}
