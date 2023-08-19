#include "microshell.h"

void print_pipes (int *pipe[2])
{

	printf("%d %d\n", pipe[0][1], pipe[0][1]);

}


int	main()
{
	int		r;

	//int *pipes[2];

	int	*tab_pipes[2] = malloc(sizeof(int) * 4);
	if (tab_pipes == NULL)
		return (0);


	//print_pipes(pipes);

	r = 0;
	while (r < 2)
	{
		pipe(tab_pipes[r]);
		r++;
	}


	r = 0;
	while (r < 2)
	{
		//printf("r = %d\n", r);
		printf("r = %d || getpid = %d || fork = %d || getpid = %d\n",
				r, getpid() ,fork(), getpid());
		printf("\n");
		r++;
	}	
	return 0;
}

