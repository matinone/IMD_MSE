
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_FRAME_LENGTH        3

typedef enum {
    SLAVE_IDLE,
    SLAVE_PAUSE,
    SLAVE_PROCESS_A,
    SLAVE_PROCESS_B,
    SLAVE_DONE,
}   slave_state_t;

void print_command_help();
char* translate_state(slave_state_t state);

int main(){
   int ret, device_handler, command;
   int count = 1;
   char read_data[COMMAND_FRAME_LENGTH];

   printf("Opening ESP32 device.\n");
   device_handler = open("/dev/esp32", O_RDWR);             // Open the device with read/write access
   if (device_handler < 0  ){
      printf("Failed to open the device.\n");
      return -1;
   }

   while (1)   {
      print_command_help();
      printf("Enter command: ");
      scanf("%d", &command);
      printf("Sending command %d\n", command);

      if (command == 10)   {
         break;
      }

      ret = write(device_handler, &command, count);
      if (ret == count) {
         printf("Command successfully sent.\n");
      }
      else
      {
         printf("Command sent failed.\n");
      }

      // get status
      if (command == 5) {
         printf("Getting slave status.\n");
         ret = read(device_handler, read_data, COMMAND_FRAME_LENGTH);
         if (ret < 0)   {
            printf("Failed reading the device status.");
         }
         else  {
            printf("Device status: %s.\n", translate_state(read_data[1]));
         }
      }  // if (command == 5)
   }  // while(1)

   printf("End of the program\n");
   close(device_handler);

   return 0;
}


void print_command_help()  {
   printf("\n-----------------\n");
   printf("Command help\n");
   printf("0  - Process A\n");
   printf("1  - Process B\n");
   printf("2  - Pause\n");
   printf("3  - Continue\n");
   printf("4  - Reset\n");
   printf("5  - Status\n");
   printf("10 - Exit\n");
   printf("-----------------\n");
}

char* translate_state(slave_state_t state)
{
    switch(state)
    {
        case SLAVE_IDLE:
            return "SLAVE_IDLE";
        case SLAVE_PROCESS_A:
            return "SLAVE_PROCESS_A";
        case SLAVE_PROCESS_B:
            return "SLAVE_PROCESS_B";
        case SLAVE_PAUSE:
            return "SLAVE_PAUSE";
        case SLAVE_DONE:
            return "SLAVE_DONE";
        default:
            return "UNKNOWN";
    }
}
