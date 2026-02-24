#include <stdio.h>
#include <unistd.h>  // for sleep()

int main(void)
{
    int counter = 0;

    while (1)  // infinite loop
    {
        printf("Counter: %d\n", counter);
        counter++;          // increment counter
        sleep(1);           // wait 1 second
    }

    return 0;
}
