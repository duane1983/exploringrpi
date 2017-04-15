/** Simple On-board LED flashing program - written in C by Derek Molloy
*    simple functional struture for the Exploring Raspberry Pi book
*
*    This program uses GPIO4 with a connected LED and can be executed:
*    Changed name of program to LEDblink 4/15/2017.
*         LEDblink setup
*         LEDblink on
*         LEDblink off
*         LEDblink status
*         LEDblink close
*
*    Modified the code by adding a blink function just to see if I
*    could do it.  Duane Shelton 4/15/2017. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define GPIO_NUMBER "4"
#define GPIO4_PATH "/sys/class/gpio/gpio4/"
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[]){
   FILE* fp;                           // create a file pointer fp
   fp = fopen(filename, "w+");         // open file for writing
   fprintf(fp, "%s", value);           // send the value to the file
   fclose(fp);                         // close the file using fp
}

void blink(void) {
   int i;
   for (i = 0; i <= 10; i++) {
       writeGPIO(GPIO4_PATH "value", "1");
       usleep(500000);
       writeGPIO(GPIO4_PATH "value", "0");
       usleep(500000);
   }
}

int main(int argc, char* argv[]){
   if(argc!=2){                        // program name is argument 1
      printf("Usage is LEDblink and one of:\n");
      printf("   setup, on, off, blink, status, or close\n");
      printf(" e.g. LEDblink on\n");
      return 2;                        // invalid number of arguments
   }
   printf("Starting the LEDblink program\n");
   if(strcmp(argv[1],"setup")==0){
      printf("Setting up the LED on the GPIO\n");
      writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER);
      usleep(100000);                  // sleep for 100ms
      writeGPIO(GPIO4_PATH "direction", "out");
   }
   else if(strcmp(argv[1],"close")==0){
      printf("Closing the LED on the GPIO\n");
      writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER);
   }
   else if(strcmp(argv[1],"on")==0){
      printf("Turning the LED on\n");
      writeGPIO(GPIO4_PATH "value", "1");
   }
   else if (strcmp(argv[1],"off")==0){
      printf("Turning the LED off\n");
      writeGPIO(GPIO4_PATH "value", "0");
   }
   else if (strcmp(argv[1],"blink")==0){
      printf("Blinking the LED\n");
      blink();
   }
   else if (strcmp(argv[1],"status")==0){
      FILE* fp;        // see writeGPIO function above for description
      char line[80], fullFilename[100];
      sprintf(fullFilename, GPIO4_PATH "value");
      fp = fopen(fullFilename, "rt");        // reading text this time
      while (fgets(line, 80, fp) != NULL){
         printf("The state of the LED is %s", line);
      }
      fclose(fp);
   }
   else{
      printf("Invalid command!\n");
   }
   printf("Finished the LEDblink Program\n");
   return 0;
}

