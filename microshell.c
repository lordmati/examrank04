#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void ft_putstrfd(char *str,char *arg)
{
	while(*str)
		write(2,str++,1);
	if(arg)
		while(*arg)
			write(2,arg++,1);
	write(2,"\n",1);
}
void ft_exec(char **argv,char **envp,int i,int tmp_fd)
{
	argv[i] = NULL;
	dup2(tmp_fd,0);
	close(tmp_fd);
	execve(argv[0],argv,envp);
	ft_putstrfd("error: cannot execute ",argv[0]);
	exit(1);
}

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	int tmp_fd;
	int fd[2];

	(void)argc;
	tmp_fd = dup(0);
	while(argv[i] && argv[i + 1])
	{
		argv = &argv[1 + i];
		i = 0;
		while(argv[i] && strcmp(argv[i],";") && strcmp(argv[i],"|"))
			i++;
		if (strcmp(argv[0],"cd") == 0)
		{
			if (i != 2)
				ft_putstrfd("error: cd: bad arguments",NULL);
			else if (chdir(argv[1]) != 0)
				ft_putstrfd("error: cd: cannot change directory to ",argv[1]);
		}
		else if (i != 0 && (argv [i] == NULL || strcmp(argv[i],";") == 0))
		{
			if(fork() == 0)
				ft_exec(argv,envp,i,tmp_fd);
			else
			{
				close(tmp_fd);
				while(waitpid(-1,NULL,2) != -1)
					;
				tmp_fd = dup(0);
			}
		}
		else if ( i != 0 && strcmp(argv[i],"|") == 0)
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1],1);
				close(fd[0]);
				close(fd[1]);
				ft_exec(argv,envp,i,tmp_fd);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}

	}
	close(tmp_fd);
}
