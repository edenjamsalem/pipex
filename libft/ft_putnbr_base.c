/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:51:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/05/15 15:13:29 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	int		i;

	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		if (chrsetcmp(base[i], &base[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	int		base_len;
	int		digit;
	int		i;
	char	str[32];

	if (check_base(base))
	{
		if (nbr == 0)
			return (ft_putchar_count('0'));
		else
		{
			base_len = ft_strlen(base);
			i = 0;
			while (nbr > 0)
			{
				digit = nbr % base_len;
				str[i++] = base[digit];
				nbr /= base_len;
			}
			str[i--] = '\0';
			while (i >= 0)
				write(1, &str[i--], 1);
		}
	}
	return (ft_strlen(str));
}
