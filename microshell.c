#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_put2str_fd(char *str, char *arg, int out)
{
	while (*str != '\0')
	{	
		write(out, str, 1);
		str ++;
	}
	if (arg != NULL)
	{
		while (*arg != '\0')
		{	
			write(out, arg, 1);
			arg ++;
		}
	}
	write(2, "\n", 1);
}

//0 => READ
//1 => WRITE

int main (int argc, char *argv[], char *env[])
{
	int i;
	int pipe_fd[2];
	(void) argc;
	int tmp_fd;


	i = 0;

	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];


		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
		{
			i++;	
		}

		if (strcmp(argv[0], "cd") == 0) //cd
		{
			if (i != 2)
				ft_put2str_fd("error: cd: bad arguments", NULL, 2);
			else if (chdir(argv[1]) != 0)
				ft_put2str_fd("error: cd: cannot change directory to ", argv[1], 2);
		}
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			if (fork() == 0)
			{
				dup2(tmp_fd, STDIN_FILENO);
				close(tmp_fd);

				argv[i] = NULL;
				execve(argv[0], argv, env);
				ft_put2str_fd("error: cannot execute ", argv[0], 2);
				return 1;
			}
			else
			{
				close(tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					;
				dup(STDIN_FILENO);
			}	
		}
		else if (i != 0 && argv[i][0] == '|')
		{
			pipe(pipe_fd);
			if (fork() == 0)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				
				dup2(tmp_fd, STDIN_FILENO);
				close(tmp_fd);

				argv[i] = NULL;
				execve(argv[0], argv, env);
				ft_put2str_fd("error: cannot execute ", argv[0], 2);
				return 1;
			}
			else
			{
				close(pipe_fd[1]);
				close(tmp_fd);
				tmp_fd = pipe_fd[0];
			}
		}

	}
	close(tmp_fd);
	return 0;
}