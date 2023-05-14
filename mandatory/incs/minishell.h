/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:48 by jperales          #+#    #+#             */
/*   Updated: 2023/05/11 11:09:52 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define QUOTES_ERROR 1
# define EXIT_PROGRAM 2

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
// # include <dirent.h>

typedef struct s_mini
{
	char	**mini_env;
	char	**input_split;
	char	*input;
	char	*curr_path;
	char	*mini_home;
	char	**input_pipes;
	char	***cmds;
	char	**cmd_path;
	char	**env_path;
	int		fd[2];
	int		or_infd;
	int		fdaux;
}	t_mini;

/* PROCESS_HERE-DOC FUNCTIONS */
char	*ft_get_here_doc(char *str);
void	ft_process_here_doc(char *delimiter);

/* TREAT_INFD FUNCTIONS */
int		ft_set_infd(char *str);
int		ft_search_infd(char *str);

/* TREAT_OUTFD FUNCTIONS */
int		ft_set_outfd(char *str);

int		ft_treat_fds(int *infd, int *outfd, char *rest, char **here_doc);
void	ft_process_one_cmd1(t_mini *minishell, int i);
void	ft_process_redir(t_mini *minishell, int cmd);
int		ft_treat_fds(int *infd, int *outfd, char *rest, char **here_doc);
char	*ft_get_here_doc(char *str);
int		ft_get_redir(char *str, char redir);
/* BUILTIN FUNCTIONS */
void	ft_env(char **env, int outfd);
void	ft_process_builtin(t_mini *minishell, int i, int outfd);

void	ft_unset(t_mini *minishell, int cmd);
void	ft_export(t_mini *minishell, int i);
void	ft_cd(t_mini *minishell, int cmd);
void	ft_echo(t_mini *minishell, int cmd, int fd);
int		*ft_get_2dstr_order(const char **str);
void	ft_putstr_fd(int fd, char *str, int mode);
bool	ft_search_redir(char **cmd);
bool	ft_is_builtin(t_mini *minishell, int i);
void	ft_process_one_cmd(t_mini *minishell);
void	ft_process_heredoc(char *delimiter);
void	ft_process_multiple_cmds(t_mini *minishell, int i);

/* COPY FUNCTIONS */
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	**ft_2dstrdup(const char **str);

/* COMPARE FUNCTIONS */
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, int n);
int		ft_strchr(const char *str, int c);

/* CONVERT FUNCTIONS */
char	*ft_2dtostr(char **str);

/* ERROR FUNCTIONS */
void	ft_process_error(int type, t_mini *minishell);

/* FREE FUNCTIONS */
void	ft_general_free(t_mini *minishell);
void	ft_free_str(char *str);
void	ft_free_2dstr(char **str);
void	ft_free_3dstr(char ***str);

/* MINISHELL FUNCTIONS */
void	ft_process_input(t_mini *minishell);
void	ft_process_expand(char **str, char **env);
void	ft_signal_handler(int signal);
void	ft_child_signal_handler(int signal);

/* PARSE FUNCTIONS */
char	**ft_split_input(char *str, char c);
char	**ft_split_pipes(char *str);
// char	**ft_split(const char *s, char c);
bool	ft_parse_pipes(char *str);
char	**ft_split(char *str, char c);
bool	ft_parse_redir(t_mini *minishell);
void	ft_delete_quotes(char *str);

/* PRINT FUNCTIONS */
void	ft_print2dstr(char **str);
void	ft_print3dstr(char ***str);

/* QUOTES FUNCTIONS */
bool	ft_quote_pairs(char *str);
void	ft_pass_quotes(char *str, int *i);

/* SIZE FUNCTIONS */
size_t	ft_strlen(const char *str);
size_t	ft_2dstrlen(const char **str);
size_t	ft_3dstrlen(char ***str);
int		ft_get_chrlen(const char *str, int c);

void	*ft_calloc(size_t count, size_t size);
char	*ft_var_not_found(char *str, char *var);
char	*ft_expand(char *var, char *var_value, char *str);
void	ft_process_cmds(t_mini *minishell);
//int 	ft_get_commands_path(t_mini *minishell);
char	*ft_get_command_path(char **cmd, char **env);

/* STRING FUNCTIONS */
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_join_chr(char *str, int c);

#endif
