/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_more_bu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:18:44 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:18:48 by vfedorov         ###   ########.fr       */
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
	g_exit_code = 0;
}

int	sravnim(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1 && str2 && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*whum_find(t_data *data, char *whum)
{
	t_env	*lst;
	char	*kto;

	kto = ft_strjoin(whum, "=");
	lst = data->env_lst;
	while (ft_strncmp(lst->key, kto,
			ft_strlen(lst->key)) != 0
		&& ft_strncmp(lst->key, kto,
			ft_strlen(kto)) != 0)
		lst = lst->next;
	free(kto);
	return (lst->val);
}
