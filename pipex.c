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

void	ft_exec(char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = ft_strjoin("/usr/bin/", cmd_args[0]);
	if (execve(cmd_path, cmd_args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

pid_t	pipe_fork(int pipe_fd[2])
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	pipe_infile_to_cmd(int pipe_fd[2][2], int fd_in, char *cmd)
{
	close(pipe_fd[0][0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipe_fd[0][1], STDOUT_FILENO);
	ft_exec(cmd);
}

void	pipe_cmd_to_cmd(int pipe_fd[2][2], char *cmd, int iter)
{
	pid_t	pid;

	if (iter % 2 == 0)
		pid = pipe_fork(pipe_fd[0]);
	else
		pid = pipe_fork(pipe_fd[1]);
	if (pid == 0)	
	{
		if (iter % 2 == 0)
		{
			close(pipe_fd[0][0]);
			close(pipe_fd[1][1]);
			dup2(pipe_fd[1][0], STDIN_FILENO);
			dup2(pipe_fd[0][1], STDOUT_FILENO);
		}	
		else
		{
			close(pipe_fd[1][0]);
			close(pipe_fd[0][1]);
			dup2(pipe_fd[0][0], STDIN_FILENO);
			dup2(pipe_fd[1][1], STDOUT_FILENO);
		}
		ft_exec(cmd);
	}
	if (iter % 2 == 0)
	{
		close(pipe_fd[0][1]);
		close(pipe_fd[1][0]);
		close(pipe_fd[1][1]);
	}
	else
	{
		close(pipe_fd[1][1]);
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);
	}
}


void	pipe_cmd_to_outfile(int pipe_fd[2][2], int fd_out, char *cmd, int iter)
{
	wait(0);
	if (iter % 2 == 0)
		dup2(pipe_fd[1][0], STDIN_FILENO);
	else	
		dup2(pipe_fd[0][0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	ft_exec(cmd);
}

char	**parse_cmds(int argc, char **argv)
{
	char	**cmds;
	int		len;
	int		i;
	int		j;

	cmds = malloc(sizeof(char *) * (argc - 2));
	if (!cmds)
		return (NULL);
	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		len = ft_strlen(argv[i]);
		cmds[j] = malloc(sizeof(char) * (len + 1));
		if (!cmds[j])
		{
			free_2D_arr(cmds, j - 1);
			return (NULL);
		}
		ft_strlcpy(cmds[j++], argv[i++], (len + 1));
	}
	cmds[j] = NULL;
	return (cmds);
}

//TODO: I need to create a new pipe for each extra child process
// 		I need a new pipe_fd for each new pipe ??



int	main(int argc, char **argv)
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2][2];
	char	**cmds;
	pid_t	pid;
	int		i;

	cmds = parse_cmds(argc, argv);
	if (!cmds)
		return (-1);
	check_input(argc, argv, cmds);
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = pipe_fork(pipe_fd[0]);
	if (pid == 0)
		pipe_infile_to_cmd(pipe_fd, fd_in, cmds[0]);
	i = 1;
	while (cmds[i + 1])
	{
		wait(0);
		pipe_cmd_to_cmd(pipe_fd, cmds[i], i);
		i++;
	}
	ft_printf("cmd = %s\n", cmds[i]);
	pipe_cmd_to_outfile(pipe_fd, fd_out, cmds[i], i);	
}