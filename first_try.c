
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int ft_put2str_err (char *str1, char *str2)
{
	if (str1 != NULL)
	{
		while (*str1 != '\0')
		{
			write(2, str1, 1);
			str1++;
		}
	}
	if (str2 != NULL)
	{
		while (*str2 != '\0')
		{
			write(2, str2, 1);
			str2++;
		}
	}
	write(2, "\n", 1);
	return (1);
}




int main(int argc, char *argv[], char *env[])
{

	int i;
	(void) argc;
	int pipe_fd[2];

	int tmp_fd;

	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] != NULL && argv[i + 1] != NULL)
	{
		
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] != NULL && strcmp(argv[i], ";") != 0 && strcmp(argv[i], "|") != 0)
		{
			i++;
		}
		

		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 2)
			{
				ft_put2str_err("error: cd: bad arguments", NULL);
			}
			else 
			{
				if (chdir(argv[1]) == -1)
				{
					ft_put2str_err("error: cd: cannot change directory to ", argv[1]);
				}
			}
		}
		else if (argv[i] == NULL || strcmp(argv[i], ";") == 0)
		{
			if (fork() == 0)
			{	
				dup2(tmp_fd, STDIN_FILENO);
				close (tmp_fd);
			
				argv[i] = NULL; //ici ça segfault ??
				execve(argv[0], argv, env);
				return ft_put2str_err("error: cannot execute ", argv[0]);
			}
			else
			{
				close (tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) == -1)
					;
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (strcmp(argv[i], "|") == 0)
		{
			pipe(pipe_fd);
			if (fork () == 0)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);

				dup2(tmp_fd, STDIN_FILENO);
				close(tmp_fd);

				argv[i] = NULL;
				execve(argv[0], argv, env);
				return ft_put2str_err("error: cannot execute ", argv[0]);
			}
			else
			{
				close (tmp_fd);
				close(pipe_fd[1]);
				tmp_fd = pipe_fd[0];
			}
		}	
	}
	close (tmp_fd);
	return (0);
}