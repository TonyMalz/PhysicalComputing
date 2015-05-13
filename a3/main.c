#include "configureSerial.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BAUDRATE 57600

int main(int argc, char const *argv[])
{
    int serialPort;
    fd_set readFileDescriptors;
    int retval;
    int bufferSize=256;
    char inputBuffer[bufferSize];
    char serialBuffer[bufferSize];

    memset(inputBuffer, 0, bufferSize);
    memset(serialBuffer, 0, bufferSize);
    
    if (argc < 2)
    {
         printf("Missing %d argument(s): serkom <PORT> \n",2-argc);
         return 1;
    }

    serialPort = open(argv[1],O_RDONLY);
    if(serialPort < 0){
        printf("Cannot open file: %s\n", argv[1] );
        perror("open()");
        return 1;
    }

    serialPort = configureSerial(serialPort,BAUDRATE);
    if(serialPort < 0){
        printf("Could not configure serial port: %s\n", argv[1] );
        perror("configureSerial()");
        return 1;
    }

#if DEBUG
    printf("[Serial port number: %i]\n",serialPort );
#endif
   
    /* watch stdin and serial port */
    FD_ZERO(&readFileDescriptors);
    FD_SET(serialPort, &readFileDescriptors);
    FD_SET(STDIN_FILENO, &readFileDescriptors);

	printf("Starting serial communication...\n");

    /* block until at least one file descriptor has data */
    while ((retval = select(serialPort+1, &readFileDescriptors, NULL, NULL, NULL)) > 0 ){

#if DEBUG
        printf("[number of FDs with data: %i]\n",retval);
#endif  

        if (FD_ISSET(STDIN_FILENO, &readFileDescriptors) )
        {

#if DEBUG   
            printf("\n[Got data from stdin:]\n");
#endif

            if(read(STDIN_FILENO,inputBuffer,bufferSize) > 0){

#if DEBUG
                printf("%s",inputBuffer);
#endif  

                if (inputBuffer[0] == 'q' && inputBuffer[1] == '\n')
                {
                    printf("Shutting down...\n");
                    return 0;
                }
                memset(inputBuffer, 0, bufferSize);
            }
        }
        
        if (FD_ISSET(serialPort, &readFileDescriptors) ) {

#if DEBUG
            printf("\n[Got data from serial port:]\n");
#endif

            if(read(serialPort,serialBuffer,bufferSize) > 0){
                printf("%s",serialBuffer);
                memset(serialBuffer, 0, bufferSize);
            } 
        }

        /* keep on listening...*/
        FD_SET(STDIN_FILENO, &readFileDescriptors);
        FD_SET(serialPort, &readFileDescriptors);
    }

    if (retval == -1) {
        perror("select()");
    }
    else {
        /* retval == 0 -> should never be reached since no timeout was set */
        printf("Timeout expired!\n"); 
    }
    
    return 1;
}