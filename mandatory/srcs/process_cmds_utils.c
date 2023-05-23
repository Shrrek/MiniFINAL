/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:11:32 by jperales          #+#    #+#             */
/*   Updated: 2023/05/23 18:11:34 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*ft_access_command(char **env_path, char *cmd)
{
	ssize_t	i;
	int		j;
	char	*dst;
	char	*dst2;

	i = -1;
	while (env_path[++i])
	{
		dst2 = ft_strjoin(env_path[i], "/");
		dst = ft_strjoin(dst2, cmd);
		free(dst2);
		j = access(dst, F_OK);
		if (j == 0)
			return (dst);
		free(dst);
	}
	return (NULL);
}

char	*ft_get_command_path(char **cmd, char **env, t_mini *minishell)
{
	char	*cmd_path;
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) && env[i])
		i++;
	if (!env[i])
		return (NULL);
	env_path = ft_split(env[i], ':');
	tmp = ft_substr(env_path[0], 5, ft_strlen(env_path[0]) - 5);
	free(env_path[0]);
	env_path[0] = ft_strdup(tmp);
	free(tmp);
	cmd_path = ft_access_command(env_path, cmd[0]);
	if (!cmd_path)
	{
		ft_putstr_fd(minishell->or_outfd, "invalid command\n", 0);
		ft_free_2dstr(env_path);
		return (NULL);
	}
	ft_free_2dstr(env_path);
	return (cmd_path);
}
