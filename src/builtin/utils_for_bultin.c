/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_bultin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:24:41 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/15 22:26:14 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	errorchar(int symbol)
{
	if ((symbol >= 33 && symbol <= 35) || (symbol >= 58
			&& symbol <= 64) || (symbol >= 37 && symbol <= 47)
		|| (symbol >= 91 && symbol <= 94 && symbol <= 96)
		|| (symbol >= 123 && symbol <= 126))
		return (1);
	return (0);
}

int	valid_variable_name(char *var)
{
	int	b;

	b = 0;
	while (var[b])
	{
		if (var[b] == 43 && var[b + 1] == '\0')
			b++;
		if (errorchar(var[b]) == 1)
		{
			write(2, "syntax error near unexpected token\n", 35);
			return (0);
		}
		b++;
	}
	b = 0;
	if (ft_isalpha(var[b]) == 0 && var[0] != '_')
	{
		write(2, "export: not a valid identifier\n", 31);
		b++;
		return (0);
	}
	return (1);
}
int	find_equal(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
void	export_env(t_env *head, char **keyvalue)
{
	t_env	*current;
	int		i;

	i = 0;
	current = head;
	while (current != NULL)
	{
		if (current->val && *current->val && *current->key)
			printf("declare -x %s=\"%s\"\n", current->key, current->val);
		else if (find_equal(keyvalue[i], '=') == 0)
			printf("declare -x %s\n", current->key);
		else if ((find_equal(keyvalue[i], '=') == 1))
			printf("declare -x %s=\"\"\n", current->key);
		i++;
		current = current->next;
	}
}
// name && name != NULL && *name == '=' && *(name + 1) == '\0'

int	valid_dir(char *path)
{
	struct stat	buf;

	return (stat(path, &buf));
}
