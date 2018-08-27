#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "csapp.h"

/*
 * Author: Summer Li
 * 
 * The program display the content of their home directory 
 * regardless of the actual working directory.
 *
 */

int main( void ) {
    int status;
    // list of args must be NULL terminated
    char *args[] = {"/bin/ls", "-l", NULL, NULL };
    char *newenviron[] = { NULL };
    // Get current home directory
    struct passwd *pw = getpwuid(getuid());
    // Replace third arg (NULL) with pointer to string that holds current directory
    args[2] = pw->pw_dir;

    // Spawn new process
    if ( Fork() == 0 ) 
        Execve( args[0], args, newenviron);  // child: call execve with the path and the args
    else 
        Wait( &status );               // parent: wait for the child

    return 0;
}
