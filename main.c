#include <stdio.h>
#include <unistd.h>

int main()
{
	int	fd1;
	int	fd2;
	int	fd_all;
	int	fd_write;

	fd1 = -1;
	fd2 = -1;
	fd_write = -1;
	fd_all = -1;

	fd1 = dup(1);
	fd2 = dup(2);

	dup2(fd2, fd1);
	//fd_write = dup(fd1);

	write(2, "test avec fd2 dans fd1\n", 23);
	
	return (0);
}
