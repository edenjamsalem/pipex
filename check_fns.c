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

static bool	check_cmds_valid(int argc, char **argv, char **envp, bool here_doc)
{
	char	**cmd_args;
	int		i;
	bool	error;

	error = false;
	i = 2;
	if (here_doc)
		i = 3;
	while (i < argc - 1)
	{
		cmd_args = ft_split(argv[i++], ' ');
		if (!find_cmd_path(cmd_args[0], envp))
		{
			ft_printf("%s: command not found\n", cmd_args[0]);
			error = true;
		}
	}
	if (error)
		return (false);
	return (true);
}

static bool	check_infile_valid(char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(infile);
		return (false);
	}
	else if (access(infile, R_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(infile);
		return (false);
	}
	return (true);
}

static bool	check_outfile_valid(char *outfile)
{
	if ((access(outfile, F_OK) != -1) && (access(outfile, W_OK) == -1))
	{
		ft_putstr_fd("bash: ", 2);
		perror(outfile);
		return (false);
	}
	return (true);
}

static bool	check_input_count(int argc, char **argv)
{
	if ((ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6) || argc < 5)
	{
		ft_putstr_fd("Missing arguments\n", 2);
		return (false);
	}
	return (true);
}

void	check_input(int argc, char **argv, char **envp)
{
	bool	error;
	bool	here_doc;

	error = false;
	here_doc = false;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc = true;
	if (!check_input_count(argc, argv))
		exit(EXIT_FAILURE);
	if (!check_outfile_valid(argv[argc - 1]))
		error = true;
	if (!here_doc && !check_infile_valid(argv[1]))
		error = true;
	if (!check_cmds_valid(argc, argv, envp, here_doc))
		error = true;
	if (error)
		exit(EXIT_FAILURE);
}
