#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int p1p0[2], pid, tot = 0;
    char parola[20];
    char trovate[20];
    
    if (argc != 2)
    {
        printf("Numero argomenti errato");
        return -1;
    }
    
    pipe(p1p0);
    
    while (1)
    {
        printf("Che parola stai cercando? ");
        scanf("%s", parola);
        
        if (strcmp(parola, "fine") == 0)
        {
            close(p1p0[1]);
            close(p1p0[0]);
            printf("\nSono state trovate %d parole\n", tot);
            exit(0);
        }

        pid = fork();
    
        if (pid == 0)
        {
            close(p1p0[0]);
            close(1);
            dup(p1p0[1]);
            close(p1p0[1]);
            execl("/bin/grep", "grep", "-c", parola, argv[1], (char *)0);
            return -1;
        }
        read(p1p0[0], trovate, sizeof(trovate));
        printf("la parola '%s' compare %d volte\n", parola, atoi(trovate));
        tot += atoi(trovate);
    }
    return 0;
}
