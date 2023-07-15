/* ************************************************************************** */
/*                                                                            */
/*                                                    *._           _.*   @   */
/*   minishell.c                                        |\  \\_//  /|     #   */
/*                                                      \/         \/     $   */
/*   By: olnytim <yearagotomorrow@gmail.com>           _|_    V  V  |_    %   */
/*                                                  *=.    =  _*  =   .=* ^   */
/*   Created: 2023/07/15 19:14:56 by olnytim           \= ___________=/   &   */
/*   Updated: 2023/07/15 19:14:57 by olnytim                /     \       *   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hf/minishell.h"

void	ft_prompt(void)
{
	char	*cwd;
	char	*hostname;
	char	*username;

	getcwd(cwd, sizeof(cwd));
	gethostname(hostname, sizeof(hostname));
	getlogin_r(username, sizeof(username));
	printf("%s@%s:%s$ ", username, hostname, cwd);
}


int	main(void)
{
	while (1)
	{
		ft_prompt();
	}
	return (0);
}
