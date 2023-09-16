/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timelkon <timelkon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:14:52 by timelkon          #+#    #+#             */
/*   Updated: 2023/01/27 18:40:31 by timelkon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)

{
	if ((c < 97 || c > 122) && (c < 65 || c > 90))
		return (0);
	else
		return (1);
}
