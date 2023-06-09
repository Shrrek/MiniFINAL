#include "../incs/minishell.h"

static	void	ft_var_not_found_aux(int *i, char *str)
{
	(*i)++;
	while (str[*i] && str[*i] != 34 && str[*i] != '$'
		&& str[*i] != 32 && str[*i] != 39 && str[*i] != '=')
		(*i)++;
}

char	*ft_var_not_found(char *str, char *var)
{
	int		i;
	int		j;
	char	*new_value;
	int		qty;

	i = 0;
	j = -1;
	qty = 0;
	new_value = (char *)malloc(sizeof(char)
			* (ft_strlen(str) - ft_strlen(var)));
	if (!new_value)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && qty == 0)
		{
			ft_var_not_found_aux(&i, str);
			qty = 1;
		}
		else
			new_value[++j] = str[i++];
	}
	new_value[++j] = '\0';
	return (new_value);
}

static	void	ft_expand_aux2(char *str, int *i, int *j, char *new_value)
{
	while (str[*i])
		new_value[++(*j)] = str[(*i)++];
	new_value[++(*j)] = '\0';
}

static void	ft_expand_aux(char *new_value, char *str, char *var_value)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	k = -1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (var_value[++k])
				new_value[++j] = var_value[k];
			while (str[i] && str[i] != ' ' && str[i] != 34 && str[i]
				!= '$' && str[i] != 39 && str[i] != '='
				&& str[i] != '+')
				i++;
			break ;
		}
		else
			new_value[++j] = str[i++];
	}
	ft_expand_aux2(str, &i, &j, new_value);
}

char	*ft_expand(char *var, char *var_value, char *str)
{
	char	*new_value;

	new_value = (char *)ft_calloc((ft_strlen(var_value)
				+ ft_strlen(str) - ft_strlen(var)), sizeof(char));
	if (!new_value)
		return (NULL);
	ft_expand_aux(new_value, str, var_value);
	return (new_value);
}
