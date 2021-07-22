#include "minishell.h"

int	execution(char **cmd)
{
	char	**path;
	int		i;
	int		res;
	int		len;
	DIR		*dir;
	int		pid;
	struct	dirent *dp;
	char	*newname;

	i = 0;
	res = 0;
	newname = ft_strjoin("/", cmd[0]);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			exit (1);
		len = ft_strlen(cmd[0]);
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_namlen == len && ft_strcmp(dp->d_name, cmd[0]) == 0) //if the command is found
			{
				pid = fork();
				if (pid == 0)
				{
					if ((execve(ft_strjoin(path[i], newname), cmd, NULL)) != 0) //executes the command
						perror(cmd[0]);
				}
				else if (pid < 0)
					ft_putstr_fd("sh: process error", 1);
				else
				{
					wait(0);
					res = 1;
				}
			}
		}
		i++;
	}
	if (res == 0)
	{
		write(1, "sh: ", 4);
		write(1, cmd[0], len);
		ft_putstr_fd(": command not found", 1);
	}
	free(path);
	closedir(dir);
	return (1);
}

// int	execution_pipe(t_all *all)
// {

// }

void	control_center(t_all *all)
{
	if (!all->cmd->parsedpipe)
		execution(all->cmd->parsed);
	// else
	// 	execution_pipe(all);
}