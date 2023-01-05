/* Author: Isabelle Oktay
 * Description: This program randomizes numbers between 1 and 10 and prompts the user to add,
                subtract, or multiply two of these random numbers. The user will input a
                specific number of questions they want to answer. The user is expected to answer
                each question within 5 seconds. If not, then the program will move prompt the user to
                move on to the next question. At the end of the program, the program will display
                the number of questions missed, incorrect, and correct.
 */

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// set up global variables to use
pid_t pid;
int incorrect = 0;
int correct = 0;
int missed = 0;
bool miss = false;

/*
 * Handles child signal if a question is missed
 *
 * Parameters:
 *  sig - the signal it recieves
 * Return value:
 *  Void
 *
 */
void missed_answer(int sig)
{
    miss = true;
    // user can't input any more answers, will have to prompt to move on
    printf("enter 0 to continue\n");
    kill(pid, SIGKILL); // we need to kill the current process to then start again.
}

int main(int argc, char **argv)
{

    signal(SIGINT, missed_answer);
    int child_status;

    int thispid;
    int i;

    // prompt the user to input the number of questions they want to answer
    int num = 0;
    printf("How many questions would you like to answer? ");
    scanf(" %d", &num);
    printf("\nAwesome! Let's goooo...\n\n");

    // create random numbers based on the current time seed
    srand(time(0));
    int op;
    int num1;
    int num2;

    // iterate for the number of questions
    for (i = 0; i < num; i++)
    {
        char answer[20];
        int intAns;

        // create a separate timer process for each child
        pid = fork();
        if (pid == 0)
        {
            pid = execve("Process6P1", NULL, NULL);
        }

        // determine which numbers and operator will be used
        op = rand() % 3;
        num1 = rand() % 10;
        num2 = rand() % 10;
        miss = false;

        // addition operation
        if (op == 0)
        {
            printf("What is %d + %d? ", num1, num2);
            scanf(" %s", answer);
        }
        // subtraction operation
        else if (op == 1)
        {
            printf("What is %d - %d? ", num1, num2);
            scanf(" %s", answer);
        }
        // multiplication operation
        else
        {
            printf("What is %d * %d? ", num1, num2);
            scanf(" %s", answer);
        }
        intAns = atoi(answer); // convert to int

        // now we need to check if the answers are correct, incorrect, or missed
        if (op == 0)
        {

            // each of these clauses depend on if miss is true or false;
            // the value of miss depends on the timer
            if (num1 + num2 != intAns && !miss)
            {
                incorrect++;
                printf("\n");
            }
            else if (num1 + num2 == intAns && !miss)
            {
                correct++;
                printf("\n");
            }
            else
            {
                printf("\n");
                miss = false;
                missed++;
            }
        }
        else if (op == 1)
        {

            if (num1 - num2 != intAns && !miss)
            {
                incorrect++;
                printf("\n");
            }
            else if (num1 - num2 == intAns && !miss)
            {
                correct++;
                printf("\n");
            }
            else
            {
                printf("\n");
                missed++;
                miss = false;
            }
        }
        else
        {

            if (num1 * num2 != intAns && !miss)
            {
                incorrect++;
                printf("\n");
            }
            else if (num1 * num2 == intAns && !miss)
            {
                correct++;
                printf("\n");
            }
            else
            {
                printf("\n");
                missed++;
                miss = false;
            }
        }

        // kill the child timer process
        kill(pid, SIGKILL);
    }

    // print out results
    printf("Your total score is: \n\n");
    printf("%d correct answers\n%d incorrect answers\n%d missed questions\n",
           correct, incorrect, missed);

    return (0);
    exit(0); // exit parent process
}
