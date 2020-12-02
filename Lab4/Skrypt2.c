#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define Buf_rozmiar 10
int main(int argc, char *argv[]) {
	
	pid_t pid;
	int fd[2], in_fd, n;
	char buf [Buf_rozmiar];

	if(pipe(fd)<0) //sprawdzanie czy pipe stworzyl sie poprawnie
        {
        fprintf(stderr, "blad\n");
        }

	pid = fork();//tworzenie dziecko

	if(pid==0)//dziecko
		{
		close(fd[1]);
		close(0);
		dup(fd[0]);
		close(fd[0]);
		execlp("display","display","-",NULL); //wyswietlanie obrazka
		}

	else if(pid>0)//rodzic
	{
		close(fd[0]);
		if((in_fd=open(argv[1],O_RDONLY))<0)//obsluga bledu wyswietlania
			{
			fprintf(stderr,"blad\n");
			return 2;
			}

	while ((n= read(in_fd, &buf,Buf_rozmiar))>0){//wczytywanie danych
		if(write(fd[1],&buf,n)<0){//obsluga bledy wczytywania
			fprintf(stderr,"blad\n");
			return 3;
			}

		}
	
	}
}