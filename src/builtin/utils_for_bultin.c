/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_bultin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:24:41 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/01 18:41:29 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	forchar(int symbol)
{
	if ((symbol >= 33 && symbol <= 47) || (symbol >= 58
			&& symbol <= 60 && symbol <= 64)
		|| (symbol >= 91 && symbol <= 94 && symbol <= 96)
		|| (symbol >= 123 && symbol <= 126))
		return (1);
	return (0);
}

int	valid_variable_name(char *var)
{
	int	b;

	b = 0;
	while (var[b] == '_')
		b++;
	while (var[b])
	{
		if (forchar(var[b]) == 1)
		{
			write(2, "syntax error near unexpected token\n", 35);
			return (0);
		}
		b++;
	}
	b = 0;
	if (ft_isalpha(var[b]) == 0 && var[0] != '_')
	{
		write(2, "unset: not a valid identifier\n", 30);
		b++;
		return (0);
	}
	return (1);
}

void	print2d_expo(t_env *enw)
{
	while (enw)
	{
		if (enw->key == NULL)
			return ;
		printf("declare -x %s=\"%s\"\n", enw->key, enw->val);
		enw = enw->next;
	}
}

void	export_env(t_data *data)
{
	print2d_expo(data->env_lst);
}
