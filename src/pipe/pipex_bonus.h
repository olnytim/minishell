/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:37:57 by vfedorov          #+#    #+#             */
/*   Updated: 2023/09/16 22:37:57 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define INT_PIPEX 4242

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# include "../includes/minishell.h"

typedef struct s_pipex
{
	pid_t	pid1;
	int		fd[INT_PIPEX][2];
	int		infile;
	int		outfile;
	int		cmds;
	char	*path;
	char	**cmd_path;
	int		argc;
	char	**argv;
	t_data	*data;
}		t_pipex;

size_t	ft_strlen_p(const char *str);
size_t	ft_strlcpy_p(char *dest, const char *src, size_t size);
int		ft_strncmp_p(const char *str1, const char *str2, size_t n);
char	*ft_strjoin_p(char *s1, char *s2);
char	**ft_split_p(char *s, char c);

char	*xx_path(t_pipex *pipex, char *argv, char **env);
void	opening(t_pipex *pipex, int argc, char **argv);
void	closing(t_pipex *pipex);

#endif