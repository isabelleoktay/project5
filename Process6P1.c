/* Author: Isabelle Oktay
 * Version: 05.15.2021
 * Description: This program is a timer for ForkExecAssign.c. The timer will continue
                as long as its seconds are less than 5. If seconds reaches 5, then
                a signal is sent to the parent, and the parent will decide how to
                handle it. 
 */
#include <unistd.h> 
#include <sys/types.h> 
#include <stdio.h> 
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

int secs=0;
pid_t ppid;

/*
 * Handles parent signal if a question is missed
 *
 * Parameters:
 *  sig - the signal it recieves
 * Return value:
 *  Void
 *
*/
void reset(int sig) {
    secs = 0;
}

int main(int argc, char **argv) {
    sleep(1);
    signal(SIGINT, reset); // receive the parent reset signal

    int i;
    int j;

    ppid = getppid();

    printf("\n");
    // print out timer
    while(secs<6) {
        printf("Time:%i\n",secs);
        fflush(0);
        sleep(1);
        secs++;
        // if seconds reaches 5, then we have to signal the parent to kill this process and move on
        if (secs == 5) {
            kill(ppid, SIGINT);
        }
        printf("\r\b\r");
    }


  return 0;
}
 
