/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:33:24 by eamsalem          #+#    #+#             */
/*   Updated: 2024/06/24 14:33:26 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	check_cmds_valid(char **cmds)
{
	char	*file_path;
	char	**cmd_args;
	int		i;
	bool	error;

	error = false;
	i = 0;
	while (cmds[i])
	{
		cmd_args = ft_split(cmds[i], ' ');
		file_path = ft_strjoin("/bin/", cmd_args[0]);
		if (access(file_path, F_OK) == -1)
		{
			ft_printf("%s: command not found\n", cmd_args[0]);
			error = true;
		}
		free(file_path);
		i++;
	}
	if (error)
		return (false);
	return (true);
}

static bool	check_infile_valid(char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		ft_printf("bash: ");
		perror(infile);
		return (false);
	}
	else if (access(infile, R_OK) == -1)
	{
		ft_printf("bash: ");
		perror(infile);
		return (false);
	}
	return (true);
}

static bool	check_outfile_valid(char *outfile)
{
	if (access(outfile, W_OK) == -1)
	{
		ft_printf("bash: ");
		perror(outfile);
		return (false);
	}
	return (true);
}

static bool	check_input_count(int argc)
{
	if (argc < 5)
	{
		ft_printf("Too few arguments");
		return (false);
	}
	return (true);
}

void	check_input(int argc, char **argv, char **cmds)
{
	bool	error;

	error = false;
	if (!check_input_count(argc))
		exit(EXIT_FAILURE);
	if (!check_outfile_valid(argv[argc - 1]))
		error = true;
	if (!check_infile_valid(argv[1]))
		error = true;
	if (!check_cmds_valid(cmds))
		error = true;
	if (error)
		exit(EXIT_FAILURE);
}
