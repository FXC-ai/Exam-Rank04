#include <unistd.h>
#include <stdio.h>


int main ()
{
	//int fd;
	int test_dup = dup (STDIN_FILENO);
	


	printf("STDIN = %d STDOUT =  %d STDERR = %d\n", STDIN_FILENO ,STDOUT_FILENO, STDERR_FILENO);
	printf("test_dup = %d\n", test_dup);



	return 0;
}