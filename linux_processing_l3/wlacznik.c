#include <stdio.h>
int add(int a, int b);

int main() {

    int pid;
    printf("Proces uruchomiony %d\n", getpid());

    pid = fork();
    
    if (pid == -1) {
        printf("Blad utorzenia procesu potomnego!");
        return 1;
    }

    if (pid == 0) {
        printf("Zglasza sie proces potomny %d\n", getpid());
        //sleep(10);
        execl("./BUILD.SH", NULL);
        //printf("Potomny odpalil BUILD.SH\n");

        // char *envp[] = {
        //     "LD_LIBRARY_PATH=.",
        //     0 };

        // execle("./main.out",NULL , envp);
        // //execle("./main.out",NULL ,"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.")
        return 0;
    }
    else {
        waitpid(pid, NULL);
        int pid2 = fork();
        
        if (pid2 == 0) {
            printf("Zglasza sie proces potomny %d\n", getpid());
            char *const env[] = {"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.", NULL};
            execle("./main.out",NULL ,NULL, env);
        } 
        else {
            printf("Zglasza sie proces macierzysty %d. Potomek %d i %d\n",
                    getpid(), pid, pid2);
            waitpid(pid2, NULL);
            execl("./DELETE.SH", NULL);
        }
        return 0;
    }
    
}