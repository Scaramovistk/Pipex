/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:10:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/03/16 14:55:39 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

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

	cmdpath = find_usrpath(cmd, envp);
	row = 0;
	while (access(cmdpath[row], X_OK) != 0 && cmdpath[row + 1])
		row++;
	return (cmdpath[row]);
}

void	ft_execve(char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	path = find_cmdpath(cmd, envp);
	execve(path, cmd, envp);
}
