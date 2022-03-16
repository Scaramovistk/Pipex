/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:10:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/03/16 15:29:06 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	ft_error(int id, char *str)
{
	if (id == -1)
	{
		id = 0;
		while (str[id])
		{
			write(1, &str[id], 1);
			id++;
		}
		write(1, " Failed", 6);
		exit (0);
	}
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	pid[2];
	int	file;
	//int	status;

	pid[0] = fork();
	pid[1] = fork();
	if (pid[0] < 0 || pid[1] < 0)
		ft_error(-1, "Fork");
	if (pid[0] == 0)
	{
		file = open(argv[1], O_RDONLY);
		ft_error(file, "First File");
		ft_error(dup2(file, STDIN_FILENO), "First Dup");
		ft_error(dup2(fd[1], STDOUT_FILENO), "Second Dup");
		close(fd[0]);
		ft_execve(argv[2],envp);
	}
	else if (pid[1] == 0)
	{
		file = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
		ft_error(file, "Second File");
		ft_error(dup2(fd[0], STDIN_FILENO), "First Dup");
		ft_error(dup2(file, STDOUT_FILENO), "Second Dup");
		close(fd[1]);
		ft_execve(argv[3],envp);
	}
	//else
		//waitpid(pid, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc > 5)
		ft_error(-1, "Arguments");
	ft_error(pipe(fd), "Fork");
	
	child_process(argv, envp, fd);

	close(fd[0]);
	close(fd[1]);
	return (0);
}
