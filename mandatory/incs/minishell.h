/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:19:48 by jperales          #+#    #+#             */
/*   Updated: 2023/05/23 19:09:52 by jperales         ###   ########.fr       */
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

typedef struct s_mini
{
	int		exit_status;
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
	int		or_outfd;
	int		fdaux;
	char	*here_doc;
}	t_mini;

/* BUILTIN FUNCTIONS */
bool	ft_is_builtin(t_mini *minishell, int i);
int		ft_process_builtin(t_mini *minishell, int i, int outfd);

/* CD FUNCTIONS */
void	ft_cd(t_mini *minishell, int cmd);

/* COMPARE FUNCTIONS */
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, int n);

/* CONVERT UTILS FUNCTIONS */
char	*ft_itoa(int n);

/* CONVERT FUNCTIONS */
char	*ft_2dtostr(char **str);
int		ft_atoi(const char *str);

/* COPY FUNCTIONS */
char	*ft_strncpy(char *dst, const char *src, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	**ft_2dstrdup(const char **str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strdup(const char *str);

/* ECHO FUNCTIONS */
void	ft_echo(t_mini *minishell, int cmd, int fd);

/* ENV FUNCTIONS */
void	ft_env(char **env, int outfd);

/* EXIT FUNCTIONS */
int		ft_exit(t_mini *minishell, int i);

/* EXPORT UTILS FUNCTIONS */
int		*ft_get_2dstr_order(const char **str);

/* EXPORT FUNCTIONS */
void	ft_export(t_mini *minishell, int i);

/* FREE FUNCTIONS */
void	ft_free_str(char *str);
void	ft_free_2dstr(char **str);
void	ft_free_3dstr(char ***str);
void	ft_general_free(t_mini *minishell);

/* MEMORY FUNCTIONS */
void	*ft_calloc(size_t count, size_t size);

/* PARSE PIPES UTILS FUNCTIONS */
char	**ft_split_pipes(char *str);

/* PARSE PIPES FUNCTIONS */
bool	ft_parse_pipes(char *str);

/* PARSE QUOTES UTILS */
char	**ft_split_input(char *str, char c);
void	ft_process_quote(const char *str, int *i, char quote);
void	ft_process_spaces(const char *str, int *i, int *start, char c);

/* PARSE QUOTES */
bool	ft_quote_pairs(char *str);
void	ft_pass_quotes(char *str, int *i);
void	ft_delete_quotes(char *str);

/* PARSE REDIR */
bool	ft_parse_redir(t_mini *minishell);

/* PRINT FUNCTIONS */
void	ft_putstr_fd(int fd, char *str, int mode);
void	ft_print3dstr(char ***str);
void	ft_print2dstr(char **str);

/* PROCESS CMDS UTILS */
char	*ft_get_command_path(char **cmd, char **env, t_mini *minishell);

/* PROCESS EXPAND UTILS */
char	*ft_var_not_found(char *str, char *var);
int		ft_expand_status(char **cmd, char *var, int i);
char	*ft_expand(char *var, char *var_value, char *str);

/* PROCESS EXPAND */
void	ft_process_expand(char **cmd, char **env);

/* PROCESS FINAL CMD FUNCTIONS */
void	ft_process_final_cmd(t_mini *minishell, int i);

/* PROCESS HERE DOC FUNCTIONS */
char	*ft_get_here_doc(char *str);
void	ft_process_here_doc(t_mini *minishell);

/* PROCESS INPUT */
int		ft_process_input(t_mini *minishell);

/* PROCESS MULTIPLE CMDS FUNCTIONS */
void	ft_process_multiple_cmds(t_mini *minishell, int i);

/* PROCESS ONE CMD FUNCTIONS */
int		ft_process_one_cmd(t_mini *minishell);
void	ft_exec_one_parent(t_mini *minishell, pid_t pid);
void	ft_exec_one_child(t_mini *minishell, int *fd);

/* PROCESS REDIR UTILS */
bool	ft_search_redir(char **cmd);
int		ft_get_redir(char *str, char redir);

/* PROCESS REDIR */
int		*ft_process_redir(t_mini *minishell, int cmd);

/* SEARCH FUNCTIONS */
int		ft_strchr(const char *str, int c);
bool	ft_str_is_digit(char *str);
bool	ft_isdigit(int c);

/* SIGNALS FUNCTIONS */
void	ft_signal_handler(int signal);
void	ft_child_signal_handler(int signal);

/* SIZE FUNCTIONS */
size_t	ft_strlen(char *str);
size_t	ft_2dstrlen(char **str);
size_t	ft_3dstrlen(char ***str);
int		ft_get_chrlen(char *str, int c);

/* STRING UTILS FUNCTIONS */
char	**ft_split(char *str, char c);

/* STRING FUNCTIONS */
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_join_chr(char *str, int c);

/* TREAT FDS FUNCTIONS */
int		ft_treat_fds(int *infd, int *outfd, char *rest, char **here_doc);
void	ft_check_fd(int fd1, int fd2);

/* TREAT_INFD FUNCTIONS */
int		ft_set_infd(char *str);
int		ft_search_infd(char *str);

/* TREAT_OUTFD FUNCTIONS */
int		ft_set_outfd(char *str);

/* UNSET FUNCTIONS */
void	ft_unset(t_mini *minishell, int cmd);

#endif