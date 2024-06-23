#include "pipex.h"

void	check_cmds_valid(char **cmds)
{
	char	*file_path;
	char	**cmd_args;
	bool	error;
	int		i;

	error = false;
	i = 0;
	while (cmds[i])
	{
		cmd_args = ft_split(cmds[i], ' ');	
		file_path = ft_strjoin("/bin/", cmd_args[0]);
		if (access(file_path, F_OK || X_OK) == -1)
		{
			ft_printf("%s: command not found\n", cmds[i]);
			error = true;
		}
		free(file_path);
		i++;
	}
	if (error)
		exit(EXIT_FAILURE);
}

void	check_infile_valid(char **argv)
{
	if (open(argv[1], O_RDONLY) == -1)
	{
		perror(argv[1]); // "No such file or directory"
		exit(EXIT_FAILURE);
	}
}

void	check_input_count(int argc)
{
	if (argc < 5)
	{
		ft_printf("Too few arguments");
		exit(EXIT_FAILURE);
	}
}

void	check_input(int	argc, char **argv, char **cmds)
{
	check_input_count(argc);
	check_infile_valid(argv);
	check_cmds_valid(cmds);
}