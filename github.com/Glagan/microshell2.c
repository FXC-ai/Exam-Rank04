#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int	find_size_nb(int nb, int is_negativ)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		size++;
	}
	if (is_negativ == -1)
	{
		size = size + 1;
	}
	return (size);
}

static char	*imintoa(void)
{
	char	*tab;

	tab = malloc(sizeof(char) * (12));
	if (tab == NULL)
		return (NULL);
	tab[0] = '-';
	tab[1] = '2';
	tab[2] = '1';
	tab[3] = '4';
	tab[4] = '7';
	tab[5] = '4';
	tab[6] = '8';
	tab[7] = '3';
	tab[8] = '6';
	tab[9] = '4';
	tab[10] = '8';
	tab[11] = '\0';
	return (tab);
}

static void	itoa_result(int is_negativ, int nb, int size, char *tab)
{
	tab[size] = '\0';
	while (--size >= 1)
	{
		tab[size] = (nb % 10) + 48;
		nb = nb / 10;
	}	
	if (is_negativ == -1)
		tab[0] = '-';
	else
		tab[0] = nb + 48;
}

char	*ft_itoa(int nb)
{
	char	*tab;
	int		is_negativ;
	int		size;

	is_negativ = 1;
	if (nb == -2147483648)
		return (imintoa());
	if (nb < 0)
	{
		nb = -nb;
		is_negativ = -1;
	}
	size = find_size_nb(nb, is_negativ);
	tab = malloc (sizeof(char) * (size + 1));
	if (tab == NULL)
		return (NULL);
	itoa_result(is_negativ, nb, size, tab);
	return (tab);
}

int	ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}



int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int fd[2];
	int tmp_fd;
	(void)argc;	// is needed in exam, because the exam tester compiles with -Wall -Wextra -Werror


	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	//ft_putstr_fd2(argv[0], ft_itoa(tmp_fd));

	while (argv[i] && argv[i + 1]) //check if the end is reached
	{

		argv = &argv[i + 1];	//the new argv start after the ; or |
		i = 0;

		//debug_str = strdup(argv[i]);
		//(void) debug_str;
		//count until we have all informations to execute the next child;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0) //cd
		{
			if (i != 2)
				ft_putstr_fd2("error: cd: bad arguments", NULL);
			else if (chdir(argv[1]) != 0)
				ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]	);
		}
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0)) //exec in stdout
		{
			if ( fork() == 0)
			{
				argv[i] = NULL;
				dup2(tmp_fd, STDIN_FILENO);
				close(tmp_fd);
				execve(argv[0], argv, env);
				return (ft_putstr_fd2("error: cannot execute ", argv[0]));
			}
			else
			{
				close(tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp_fd = dup(STDIN_FILENO);
				//ft_putstr_fd2(argv[0], ft_itoa(tmp_fd));
			}
		}
		else if(i != 0 && strcmp(argv[i], "|") == 0) //pipe
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);

				argv[i] = NULL;
				dup2(tmp_fd, STDIN_FILENO);
				close(tmp_fd);
				execve(argv[0], argv, env);
				return (ft_putstr_fd2("error: cannot execute ", argv[0]));
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
				//ft_putstr_fd2(argv[0], ft_itoa(tmp_fd));
			}
		}
	}
	close(tmp_fd);
	// if (TEST)		// not needed in exam, but necessary if you want to use this tester:
	// 	while (1);	// https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh
	return (0);
}