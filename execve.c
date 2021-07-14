#include "minishell.h"

// void	fill_cmd(char **cmd)
// {
// 	char	**arr
// }

int	execution(char **cmd)
{
	char	*env;
	char	**path;
	int		i;
	int		len;
	DIR		*dir;
	int		pid;
	struct	dirent *dp;
	char	*newname;
	// char	*argv[] = {cmd[0], NULL};

	i = 0;
	newname = ft_strjoin("/", cmd[0]);
	env = getenv("PATH");
	path = ft_split(env, ':');
	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			exit (1);
		len = ft_strlen(cmd[0]);
		while ((dp = readdir(dir)) != NULL)
		{
			if (dp->d_namlen == len && ft_strcmp(dp->d_name, cmd[0]) == 0)
			{
				pid = fork();
				if (pid == 0)
				{
					if ((execve(ft_strjoin(path[i], newname), cmd, NULL)) == -1)
						ft_putstr_fd("error while executing the command", 1);
				}
				else if (pid < 0)
				{
					ft_putstr_fd("sh: process error", 1);
				}
				else
					wait(0);
			}
		}
		i++;
	}
	closedir(dir);
	return (1);
}
