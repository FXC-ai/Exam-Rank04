#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	print_tab(char **tab, int d)
{
	int	i;

	printf("---------------%d----------------\n\n", d);
	i = 0;
	while (tab[i] != NULL)
	{
		printf("[%s] (%d)\n", tab[i], i);
		i++;
	}
	printf("[%s] (%d)\n",tab[i], i);
	printf("\n---------------------------------\n\n");
}

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
	char *print_str;


	i = 0;

	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];


		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
		{
			i++;	
		}

		if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			if (fork() == 0)
			{
				argv[i] = NULL;

				execve(argv[0], argv, env);
				ft_put2str_fd("error: cannot execute ", argv[0], 2);
				return 1;
			}
			else
			{
				waitpid(-1, NULL, WUNTRACED);
			}	
		}

		//printf("argv[%d] = %s\n", i, argv[i]);
	}




	return 0;
}