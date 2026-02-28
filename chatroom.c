#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    char *room_name = argv[1];
    char *user_name = argv[2];

    char room[256];
    strcpy(room, "/tmp/chatroom-");
    strcat(room, room_name);

    char pipename[256];
    strcpy(pipename, room);
    strcat(pipename, "/");
    strcat(pipename, user_name);
    mkdir(room, 0777);
    mkfifo(pipename, 0666);

    printf("Welcome to %s!\n", room_name);
    pid_t pid = fork();

    if (pid == 0) {
        int fd = open(pipename, O_RDWR);
        char rmessage[512];

        while (1) {
            int read_count = read(fd, rmessage, 511);
            if (read_count > 0) {
                rmessage[read_count] = '\0'; 
                printf("\n%s\n", rmessage);

                printf("[%s] %s > ", room_name, user_name);
                fflush(stdout);
            }
        }
    } 

    char input[512];
    char smessage[512]; 

    while (1) {
        printf("[%s] %s > ", room_name, user_name);
        fflush(stdout);

        if (fgets(input, 512, stdin) == NULL) {
            break; 
        }

        int len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        strcpy(smessage, "[");
        strcat(smessage, room_name);
        strcat(smessage, "] ");
        strcat(smessage, user_name);
        strcat(smessage, ": ");
        strcat(smessage, input);

        DIR *dir = opendir(room);
        if (dir != NULL) {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                char *name = entry->d_name;

                if (strcmp(name, ".") == 0) {
			continue;
		}
                if (strcmp(name, "..") == 0){	
			 continue;
			}
             if (strcmp(name, user_name) == 0){
		 continue;
		}

                pid_t member_pid = fork();
                if (member_pid == 0) {
                    char member_pipe[512];
                    strcpy(member_pipe, room);
                    strcat(member_pipe, "/");
                    strcat(member_pipe, name);

                    int member_fd = open(member_pipe, O_WRONLY);
                    if (member_fd != -1) {
                        write(member_fd, smessage, strlen(smessage));
                        close(member_fd);
                    }
                    exit(0);
                }
            }
            closedir(dir);
        }

    }

    kill(pid, 9);
    unlink(pipename);

    return 0;
}
