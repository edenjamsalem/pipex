/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arrtrunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:49:14 by eamsalem          #+#    #+#             */
/*   Updated: 2024/05/22 13:12:43 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*int_arrtrunc(int *src, int size)
{
	int	i;
	int	*tmp;
	int	*new;

	if (!src || size < 0)
		return (NULL);
	new = malloc(sizeof(int) * size);
	if (!new)
		return (NULL);
	i = 0;
	tmp = new;
	while (i < size)
	{
		tmp[i] = src[i];
		i++;
	}
	return (new);
}
