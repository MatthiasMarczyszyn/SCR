#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define Buf_rozmiar 32
int main(int argc, char *argv[]) {

	pid_t pid;
	int fd[2], in_fd, n;
	char buf [Buf_rozmiar];

	if(pipe(fd)<0)//sprawdzanie pipe
        {
        fprintf(stderr, "blad\n");
        }

	pid = fork();//tworzenie dziecka

	if(pid==0)//dziecko
		{
		close(fd[1]);
		while(n = read(fd[0],&buf,Buf_rozmiar)>0)
            {
                printf("#%s#\n",buf);
            }
            close(fd[0]);
		}

	else if(pid>0)//rodzic
	{
		close(fd[0]);
		if((in_fd=open(argv[1],O_RDONLY))<0)
			{
			fprintf(stderr,"blad\n");
			return 2;
			}

	while ((n= read(in_fd, &buf,Buf_rozmiar))>0){
		if(write(fd[1],&buf,n)<0){
			fprintf(stderr,"blad\n");
			return 3;
			}

		}
	}
}
