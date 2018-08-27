#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include "csapp.h"

/*
 * Author: Summer Li
 *
 * This program will print a message on the console after a specific number of seconds elapses.
 *
 */

int ARGC = -1;
char** ARGV = NULL;
int TIME = 0;

void display_message(int signo) {
    int i;
    // Show message
    printf("\n");
    for(i = 2; i < ARGC; ++i) {
        if(i > 2) printf(" ");
        printf("%s", ARGV[i]);
    }
    printf("\n");
    // Recursive call using alarm and signal
    alarm(TIME);
    signal(SIGALRM, display_message);
}

int main( int argc, char** argv ) {
    if(argc < 3) {
        printf("Usage: %s <time> <message-text>\n", argv[0]);
        return 0;
    }
    // Convert string to integer
    int time = atoi(argv[1]);
    // Checking if input is negative
    if(time < 0) {
        printf("Time must be non negative number\n");
        return 0;
    }
    ARGC = argc;
    ARGV = argv;
    TIME = time;
    // Spawn new process
    if ( Fork() == 0 ) {
        printf("%s process-id %d\n", argv[0], getpid());
        signal(SIGALRM, display_message);
        alarm(time);
	while(1) { printf(""); Pause();}
    } else {} 

    return 0;
}
