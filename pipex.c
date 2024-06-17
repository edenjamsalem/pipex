/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:20:52 by eamsalem          #+#    #+#             */
/*   Updated: 2024/06/17 11:27:24 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// execve() 	- executes the specified program with the specified argv and envp variables
//				  (if envp == NONE, the same environment parameters are used)
// pipe()		- redirects an output as input to another process
// dup()		- creates a copy of a file descriptor using the lowest, unused number
// dup2()		- creates a copy of a file descriptor using the number passed as arg
// perror()		- writes the error message arg to stderror
// strerror()	- returns a pointer to the textual representation of the error number arg
// access()		- checks whether a file is accessible for the specified mode
// fork()		- creates a new (child) process by duplicating the calling process
// unlink()		- removes the link to the specified file
//				  (if the no. fd's for a file drops to 0, its content can be overwritten)
// wait()		- suspend the calling process until a child process is complete
// waitpid()	- same as wait() but specifies the specific child process ID (PID)


//PSEUDO CODE:
// Read the contents of file_1 and pass them as input to cmd1 X
// Pipe the output of cmd1 to cmd2
// Write the output of cmd2 to file_2

char	**get_cmds(int argc, char **argv)
{
	char	**cmds;
	int		i;
	int		j;
	int		len;

	cmds = malloc(sizeof(char *) * argc - 2);
	if (!cmds)
		return (NULL);
	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		len = ft_strlen(argv[i]);
		cmds[j] = malloc(sizeof(char *) * (len + 1));
		ft_strlcpy(cmds[j++], argv[i++], len + 1);
	}
	cmds[j] = NULL;
	return (cmds);
}

char	**get_exec_args(char *file1, char **cmd_args)
{
	char	**exec_args;
	int		arg_count;
	int		i;
	int		j;

	arg_count = ft_arrlen(cmd_args);
	exec_args = malloc(sizeof(char *) * (arg_count + 3));
	exec_args[0] = "<";
	exec_args[1] = file1;
	i = 0;
	j = 2;
	while (i < arg_count)
		exec_args[j++] = cmd_args[i++];
	exec_args[j] = NULL;
	return (exec_args);
}

int	read_file1_to_cmd1(char *file1, char *cmd1)
{
	char	*cmd_path;
	char	**cmd_args;
	char	**exec_args;
	
	cmd_args = ft_split(cmd1, ' ');
	cmd_path = ft_strjoin("/bin/", cmd_args[0]);
	exec_args = get_exec_args(file1, cmd_args);
	if (!execve(cmd_path, exec_args, NULL))
	{
		perror("execve");
		return (-1);
	}
	free_2D_arr(cmd_args);
	free_2D_arr(exec_args);
	free(cmd_path);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*file1;
	char	*file2;
	char	**cmds;
//	int		fd1;
//	int		fd2;
	
	if (argc < 5)
		return (-1); // write error ?
	file1 = argv[1];
	file2 = argv[argc - 1];
	
	cmds = get_cmds(argc, argv);
	read_file1_to_cmd1(file1, cmds[0]);
		
//	fd1 = open(file1, O_RDONLY);
//	fd2 = open(file2, O_WRONLY);
//	pipex(fd1, fd2);
	free_2D_arr(cmds);
}
