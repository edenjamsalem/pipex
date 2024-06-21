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
//				  this function replaces the current process image

// dup()		- creates a copy of a file descriptor using the lowest, unused number

// dup2()		- creates a copy of a file descriptor using the number passed as arg
//				  can use this to redirect printf from stdoutput to file2

// fork()		- creates a new (child) process by duplicating the calling process
//			  	  can be used to stop execve from overwriting our main process image

// pipe()		- redirects an output as input to another process
//				  can create a communication channel between parent & child processes

// perror()		- writes the error message arg to stderror

// strerror()	- returns a pointer to the textual representation of the error number arg

// access()		- checks whether a file is accessible for the specified mode

// unlink()		- removes the link to the specified file
//				  (if the no. fd's for a file drops to 0, its content can be overwritten)

// wait()		- suspend the calling process until a child process is complete

// waitpid()	- same as wait() but specifies the specific child process ID (PID)


// I can use the which command to find the path of any shell command


void	ft_exec(char *cmd_path, char **exec_args, char *output)
{
	pid_t	pid;
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		if (!execve(cmd_path, exec_args, NULL))
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
	}
	close(fd[1]);
	wait(NULL);
	while ((tmp = get_next_line(fd[0])))
	{

		ft_strlcat(output, tmp, ft_strlen(tmp) + ft_strlen(output) + 1);
		free(tmp);
	}
	close(fd[0]);
//	write(1, "1\n", 2);
}

char	**get_exec_args(char *input, char **cmd_args)
{
	char	**exec_args;
	int		arg_count;
	int		i;
	int		j;

	arg_count = ft_2D_arrlen(cmd_args);
	exec_args = malloc(sizeof(char *) * (arg_count + 2));
	i = 0;
	j = 0;
	while (i < arg_count)
		exec_args[j++] = cmd_args[i++];
	exec_args[j++] = input;
	exec_args[j] = NULL;
	return (exec_args);
}

int	pass_infile_to_cmd1(char *input, char *cmd1, char *output)
{
	char	*cmd1_path;
	char	**cmd1_args;
	char	**exec_args;

	cmd1_args = ft_split(cmd1, ' ');
	if (!cmd1_args)
		return (0);
	cmd1_path = ft_strjoin("/bin/", cmd1_args[0]);
	if (!cmd1_path)
		return (0);
	exec_args = get_exec_args(input, cmd1_args);
	if (!exec_args)
		return (0);
	ft_exec(cmd1_path, exec_args, output);
	free_2D_arr(cmd1_args, true);
	//free_2D_arr(exec_args, false);
	free(cmd1_path);
	return (1);
}

char	**get_cmds(int argc, char **argv)
{
	char	**cmds;
	int		i;
	int		j;
	int		len;

	cmds = malloc(sizeof(char **) * argc - 2);
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

bool	check_input(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*buf;

	// check if the first and last argv are actually files
	fd1 = open(argv[0], O_RDONLY);
	fd2 = open(argv[argc - 1], O_WRONLY);
	buf = NULL;
	if (read(fd1, buf, 0) == -1)
		return (false);
	if (read(fd2, buf, 0) == -1)
		return (false);
	
	// check if correct number of args
	if (argc < 5)
		return (false); // write error ?
	
	// check if cmds are valid shell commands ?? Might have to catch this when I find the path
	return (true);
}

int	main(int argc, char **argv)
{
	char	*infile;
//	char	*outfile;
	char	**cmds;
	char	*output = malloc(sizeof(char) * 1000);
//	int		i;

//	if (!check_input(argc, argv))
//		return (-1);
	infile = argv[1];
//	outfile = argv[argc - 1];
	cmds = get_cmds(argc, argv);
	if (!cmds)
		return (-1);
	output[0] = '\0';
	pass_infile_to_cmd1(infile, cmds[0], output);
	ft_printf("%s\n", output);
	free(output);
//	i = 1;
//	while (cmds[i])
//		exec(cmds[i]);
//	read_cmd_to_outfile(outfile, cmds[i]);
//	free_mem();
}
