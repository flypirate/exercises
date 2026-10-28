#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int    picoshell(char **cmds[])
{
    int i = 0;
    int fd[2];
    int N;
    int prev_fd = -1;
    pid_t pid;
    int waitstatus = 0;
    int flag = 0;

    while (cmds[i])
        i++;
    N = i - 1;
    i = 0;
    while (i <= N)
    {
        if (i < N)
        {
            if (pipe(fd) < 0)
            {
                flag = 1;
                break;
            }
        }
        pid = fork(); 
        if (pid == -1)
        {
            if (i < N)
            {
                close(fd[0]);
                close(fd[1]);
            }
            flag = 1;
            break;
        }
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(1);
                close(prev_fd);
            }
            if (i < N)
            {
                if (dup2(fd[1], STDOUT_FILENO) == -1)
                    exit (1);
                 close(fd[0]);
                 close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (i < N)
        {
            prev_fd = fd[0];
            close(fd[1]);
        }
        i++;
    }
    if (prev_fd != -1)
        close(prev_fd);
    while (wait(&waitstatus) != -1)
    {
        if (!WIFEXITED(waitstatus) || WEXITSTATUS(waitstatus) != 0)
            flag = 1;
    }
    return (flag);
}

int main(void)
{
    char *ls[]   = {"ls", NULL};
    char *grep[] = {"grep", "picoshell", NULL};
    char *echo[] = {"echo", "squalala", NULL};
    char *cat[]  = {"cat", NULL};
    char *sed[]  = {"sed", "s/a/b/g", NULL};
    char *bad[]  = {"comandofalso", NULL};

    char **t1[] = {ls, grep, NULL};         /* ls | grep picoshell */
    char **t2[] = {echo, cat, sed, NULL};   /* echo | cat | sed    */
    char **t3[] = {ls, bad, cat, NULL};     /* comando inexistente */
    char **t4[] = {ls, NULL};               /* un solo comando     */

    printf("t1 -> %d\n", picoshell(t1));
    printf("t2 -> %d\n", picoshell(t2));
    printf("t3 -> %d\n", picoshell(t3));
    printf("t4 -> %d\n", picoshell(t4));
    return (0);
}