/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:21:10 by eamsalem          #+#    #+#             */
/*   Updated: 2024/06/17 11:21:50 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/wait.h> 

void	check_cmds_valid(char **cmds);

void	check_infile_valid(char **argv);

void	check_input_count(int argc);

void	check_input(int	argc, char **argv, char **cmds);