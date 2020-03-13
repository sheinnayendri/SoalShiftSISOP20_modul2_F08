#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<syslog.h>
#include<string.h>
#include<time.h>
#include<wait.h>
#include<sys/prctl.h>
#include<stdbool.h>

void daemonstart()
{
	pid_t pid, sid;
    pid = fork();
    if(pid < 0) exit(EXIT_FAILURE);
    if(pid > 0) exit(EXIT_SUCCESS);
    umask(0);
    sid = setsid();
    if(sid < 0) exit(EXIT_FAILURE);
    //if((chdir("/")) < 0) exit(EXIT_FAILURE);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char* argv[])
{
    if(argc != 2 || (argv[1][1] != 'a' && argv[1][1] != 'b')) 
    {
        printf("Mode hanya ada -a atau -b\n");
        exit(0);
    }
    
    int stat;
    FILE* kill;
    kill = fopen("kill.sh", "w");
    fprintf(kill, "#!/bin/bash\nkill %d\nkill %d\necho \'Killed program.\'\nrm \"$0\"", getpid() + 2, getpid() + 3);
    fclose(kill);
    pid_t cid;
    cid = fork();
    if(cid < 0) exit(0);
    if(cid = 0)
    {
        char *ag[] = {"chmod", "u+x", "kill.sh", NULL};
        execv("/bin/chmod", ag);
    }
    while(wait(&stat) > 0);

    daemonstart();

    char curtime[30], curtime2[30], curtime3[30], link[50];
    int stat1, stat2, stat3;

    while(1)
    {
    	int i;
        pid_t cid, cid2, cid3, cid4, cid5;
        time_t t1 = time(NULL);
        struct tm* p1 = localtime(&t1);
        strftime(curtime, 30, "%Y-%m-%d_%H:%M:%S", p1);

        cid = fork();
        if(cid < 0) exit(0);
        if(cid == 0)
        {
            char *ag[] = {"mkdir", curtime, NULL};
            execv("/bin/mkdir", ag);
        }

        while(wait(&stat1) > 0);
        cid2 = fork();
        if(cid2 < 0) exit(0);
        if(cid2 == 0)
        {
            if(argv[1][1] == 'a') prctl(PR_SET_PDEATHSIG, SIGHUP);
            chdir(curtime);
            for(i = 0; i < 20; i++)
            {
                time_t t2 = time(NULL);
                struct tm* p2 = localtime(&t2);
                strftime(curtime2, 30, "%Y-%m-%d_%H:%M:%S", p2);
                sprintf(link, "https://picsum.photos/%ld", (t2 % 1000) + 100);

                cid3 = fork();
                if(cid3 < 0) exit(0);
                if(cid3 == 0)
                {
                    char *ag[] = {"wget", link, "-O", curtime2, "-o", "/dev/null", NULL};
                    execv("/usr/bin/wget", ag);
                }
                sleep(5);
            }

            while(wait(&stat2) > 0);
            chdir("..");
            strcpy(curtime3, curtime);
            strcat(curtime3, ".zip");

            cid4 = fork();
            if(cid4 < 0) exit(0);
            if(cid4 == 0)
            {
                char *ag[] = {"zip", "-r", curtime3, curtime, NULL};
                execv("/usr/bin/zip", ag);
            }
		
            while(wait(&stat3) > 0);
            cid5 = fork();
	    if(cid5 < 0) exit(0);
            if(cid5 == 0)
            {
                char *ag[] = {"rm", "-r", curtime, NULL};
            	execv("/bin/rm", ag);
            }
        }
        sleep(30);
    }
}
