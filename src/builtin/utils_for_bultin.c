/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_bultin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:19:14 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:19:17 by vfedorov         ###   ########.fr       */
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
		if (var[b])
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

void	export_env(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (!current->key && !*current->key && !current->val)
			printf("%s", current->key);
		else if (current->val && *current->val && *current->key)
			printf("declare -x %s=\"%s\"\n", current->key, current->val);
		else if (current->flag == 0 && *current->key)
			printf("declare -x %s\n", current->key);
		else if (current->flag == 1)
		{
			if (!*current->key && !*current->val)
				printf("%s", current->key);
			else
				printf("declare -x %s=\"\"\n", current->key);
		}
		current = current->next;
	}
	g_exit_code = 0;
}

int	valid_dir(char *path)
{
	struct stat	buf;

	return (stat(path, &buf));
}
