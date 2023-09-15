/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_more_bu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:58:31 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/15 15:47:25 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	norm_cd(t_data *data, t_parse *pars, char *old, char *new)
{
	old = getcwd(0, 0);
	chdir(pars->cmd[1]);
	find_var(data, "OLDPWD", old);
	new = getcwd(0, 0);
	find_var(data, "PWD", new);
	free(old);
	free(new);
}

int	sravnim(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1 && str2 && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	tilda(t_parse *pars, char *valid)
{
	if (valid_dir(valid) == -1)
	{
		printf("cd: %s: No such file or directory\n", pars->cmd[1]);
		return (0);
	}
	return (1);
}
