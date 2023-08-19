#include "microshell.h"

int	size_tab(char **tab)
{
	int result;

	result = 0;
	while (tab[result] != NULL)
	{
		result++;
	}
	return (result);
}

int ft_strlen(char *str)
{
	int size = 0;

	if (str == NULL)
		return 0;
	while (*(str ++) != '\0')
		size++;
	return size;
}


char *ft_strdup(char *str)
{
	int		size_str;
	int		i;
	char	*copy;
	
	if (str == NULL)
		return NULL;

	size_str = ft_strlen(str);
	copy = (char *) malloc(sizeof(char) * (size_str + 1));
	if (copy == NULL)
		return NULL;
	
	i = 0;
	while(i++ < size_str)
	{
		copy[i] = str[i];
		//i++;
	}
	return copy;
}

/*char	**dup_tab(char **tab)
{
	char	**result:
	int		size;
	int		i;

	size = size_tab(tab);

	result = (char **) malloc (sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);

	i = 0;
	while (i < size)
	{

		i++;
	}

	return (result);
}*/

int	main(int argc, char *argv[], char *env[])
{
	(void) argc;
	(void) argv;

	char	*test[3];
	int		r;

	test[0] = "/bin/ls";
	test[1] = "-la";
	test[2] = NULL;

	//ft_strdup(test[0]);


	//r = size_tab(test);
	//printf("r = %d\n", r);

	pid_t pid_process1;
	
	//printf("Mon PID = %d \n", getpid());

	r = 0;
	while (r < 2)
	{
		printf("r = %d\n", r);
		printf("fork renvoie = %d \n", fork());
		printf("getpid = %d\n", getpid());
		printf("\n");
		r++;

	}	
	
	//(1733, 1734)
	//()


	//printf("%d : process\n\n", pid_process1);


	//r = execve(test[0], test, env);

	return 0;
}