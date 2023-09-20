/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:18:58 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/20 21:19:01 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tilda_main(t_data *data, t_parse *pars, char *joi)
{
	char	*valid;
	char	*old;
	char	*new;

	old = NULL;
	new = NULL;
	valid = ft_strjoin(joi, pars->cmd[1] + 1);
	if (tilda(pars, valid) == 0)
	{
		free(valid);
		return ;
	}
	else
		just_cd(data, valid, old, new);
	free(valid);
}

int	tilda(t_parse *pars, char *valid)
{
	if (valid_dir(valid) == -1)
	{
		printf("cd: %s: No such file or directory\n", pars->cmd[1]);
		g_exit_code = 1;
		return (0);
	}
	g_exit_code = 0;
	return (1);
}
