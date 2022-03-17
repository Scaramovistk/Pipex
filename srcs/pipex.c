/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:10:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/03/17 13:40:56 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

static void	ft_free(char **str)
{
	int	row;

	row = 0;
	write(2, "zsh: command not found: ", 25);
	write(2, &str[0][1], ft_strlen(&str[0][1]));
	write(2, "\n", 1);
	while (str[row])
	{
		free(str[row]);
		row++;
	}
	free(str);
}

static char	*addbackslash(char *cmd)
{
	char	*str;
	int		row;

	row = 0;
	str = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	if (str == NULL)
		ft_error(-1, "Malloc");
	str[0] = '/';
	while (cmd[row])
	{
		str[row + 1] = cmd[row];
		row++;
	}
	str[row + 1] = '\0';
	free(cmd);
	return (str);
}

static char	**find_usrpath(char **cmd, char **envp)
{
	char	**usrpath;
	int		row;

	row = 0;
	cmd[0] = addbackslash(cmd[0]);
	while (ft_strncmp(envp[row], "PATH=", 5))
		row++;
	usrpath = ft_split(envp [row] + 5, ':');
	if (usrpath == NULL)
		ft_error(-1, "Split");
	row = 0;
	while (usrpath[row])
	{
		usrpath[row] = ft_strjoin(usrpath[row], cmd[0]);
		row++;
	}
	return (usrpath);
}

static char	*find_cmdpath(char **cmd, char **envp)
{
	char	**cmdpath;
	int		row;

	row = 0;
	cmdpath = find_usrpath(cmd, envp);
	while (access(cmdpath[row], X_OK) != 0 && cmdpath[row])
		row++;
	if (!cmdpath[row])
	{
		ft_free(cmd);
		exit(1);
	}
	return (cmdpath[row]);
}

void	ft_execve(char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		ft_error(-1, "Split");
	path = find_cmdpath(cmd, envp);
	execve(path, cmd, envp);
}
