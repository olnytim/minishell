/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_more_bu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriafedorova <valeriafedorova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:58:31 by valeriafedo       #+#    #+#             */
/*   Updated: 2023/09/12 18:37:25 by valeriafedo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	norm_cd(t_data *data, t_parse *pars, char *old, char *new)
{
	getcwd(old, PATH_MAX);
	chdir(pars->cmd[1]);
	find_var(data, "OLDPWD", old);
	getcwd(new, PATH_MAX);
	find_var(data, "PWD", new);
}
int	sravnim(char *str1, char *str2)
{
    int i;

    i  = 0;
	while (str1 && str2 && str1[i] && str2[i]
        && str1[i] == str2[i])
            i++;
	return (str1[i] - str2[i]);
}