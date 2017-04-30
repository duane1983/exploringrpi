/** Simple On-board LED flashing program - written in C by Derek Molloy
*   simple functional struture for the Exploring Raspberry Pi book
*
*   Attempting to create an OOP-like program using C similar to the
*   C++ verison with classes
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>       // for the microsecond sleep function

#define GPIO_PATH "/sys/class/gpio/gpio"
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[]){
   FILE* fp;                           // create a file pointer fp
   fp = fopen(filename, "w+");         // open file for writing
   fprintf(fp, "%s", value);           // send the value to the file
   fclose(fp);                         // close the file using fp
}

void LED_setup(int gpioNum) {
   char gpio_path[40] = GPIO_PATH;
   char gpio_sysfs[40] = GPIO_SYSFS;
   char *gpio_str, str[15];
   gpio_str = str;
   sprintf(str, "%d", gpioNum);
   strcat(gpio_sysfs, "export");
   strcat(gpio_path, gpio_str);
   strcat(gpio_path, "/direction"); 
   printf("Setting up the LED on the GPIO %d\n", gpioNum);
   writeGPIO(gpio_sysfs, gpio_str);
   usleep(100000);                  // sleep for 100ms
   writeGPIO(gpio_path, "out");
}

void LED_close(int gpioNum) {
   char gpio_sysfs[40] = GPIO_SYSFS;
   char *gpio_str, str[15];
   gpio_str = str;
   sprintf(str, "%d", gpioNum);
   strcat(gpio_sysfs, "unexport");
   printf("Closing the LED on the GPIO %d\n", gpioNum);
   writeGPIO(gpio_sysfs, gpio_str);
}

void LED_turnON(int gpioNum) {
   char gpio_path[40] = GPIO_PATH;
   char *gpio_str, str[15];
   gpio_str = str;
   sprintf(str, "%d", gpioNum);
   strcat(gpio_path, gpio_str);
   strcat(gpio_path, "/value");
   writeGPIO(gpio_path, "1");
}

void LED_turnOFF(int gpioNum) {
   char gpio_path[40] = GPIO_PATH;
   char *gpio_str, str[15];
   gpio_str = str;
   sprintf(str, "%d", gpioNum);
   strcat(gpio_path, gpio_str);
   strcat(gpio_path, "/value");
   writeGPIO(gpio_path, "0");
}

int main(){

   int i;

   printf("Starting the makeLED program\n");
   LED_setup(4);
   LED_setup(17);

   for (i=0; i<50; i++) {

      LED_turnON(4);
      LED_turnOFF(17);
      usleep(50000);
      LED_turnOFF(4);
      LED_turnON(17);
      usleep(50000);

   }

   LED_close(4);
   LED_close(17);

   printf("Finished the makeLED Program\n");
   return 0;
}
