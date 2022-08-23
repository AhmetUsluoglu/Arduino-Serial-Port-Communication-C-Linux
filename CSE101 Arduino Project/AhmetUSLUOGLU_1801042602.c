/*
Link to YouTube video: https://youtu.be/zBH_Nn3Kp2I
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

// To able to run this code in your pc this part needs to be changed according to port which arduino is connected.
#define port "/dev/ttyACM0"

void square();
void button();
void menu();

int main()
{
	// Opens serial communication
	char board = open( port, O_RDWR | O_NOCTTY | O_NDELAY ); 
	char select;

	printf("\n#-#\tWELCOME TO GTU ARDUINO LAB \t#-#\n");
	printf("#-#\tAHMET USLUOGLU 1801042602  \t#-#\n");
	printf("#-#\tPLEASE SELECT FROM THE FOLLOWING	#-#\n");
	sleep(0.5);
	// Loops and asks for selection until input is '0', then goes to corresponding function
	do	
	{
		menu();
		scanf(" %c",&select);
		
		switch(select)
		{
		
		case '0':
			printf("\nNice to have you!\nFarewell\n\n");				// If recieves 0 prints greetings and finishes the loop
			break;
		case '1':
			write(board,"1",1);
			printf("\n\tLED IS ON\n");									// Sends 1 to arduino
			break;
		case '2':
			write(board,"2",1);
			printf("\n\tLED IS OFF\n");									// Sends 2 to arduino
			break;
			
		case '3':															
			write(board,"3",1);
			printf("\n\tLED IS BLINKED\n");								// Sends 3 to arduino
			break;
			
		case '4':									
			printf("\n\tSquare by Arduino\n");
			square();
			break;
			
		case '5':									
			printf("\n\tButton Counter\n");
			button();
			break;
		
		case '6':
			printf("\n\tNice Tune :D\n\tPlease Wait Until The End\n");	
			write(board,"6",1);											// Sends 6 to arduino
			sleep(10);
			break;										   		
		
		default:												       
			printf("\n\tINVALID OPERATION\t\n");
		}
	}while (select != '0');
	
	// Closes serial communication
	close(board);
	return 0;
}

// Menu Function prints instructions at every turn
void menu()
{
	printf("\n\t#-#\tMENU\t#-#\n");
	printf("(1) TURN ON LED ON ARDUINO			   \n");
	printf("(2) TURN OFF LED ON ARDUINO 			   \n");
	printf("(3) FLASH ARDUINO LED 3 TIMES 		   \n");
	printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO \n");
	printf("(5) BUTTON PRESS COUNTER 			   \n");
	printf("(6) PLAY MUSIC		 			   \n");		
	printf("(0) EXIT                                 	   \n");
	printf("PLEASE SELECT: ");
}

// Calculates the square of the input number
void square()
{
	// Opens serial communication and spends some time 
	char board = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
	
	// Here we have to strings one for getting number from user and the other for adding '4' at the start of it.
	char num[10];			
	char number[11];
	number[0] = '4';

	printf("Enter the number : ");
	scanf("%s",num);
	
	// Copying strings 
	for(int i = 0; i < 10; i++)	
	{
		number[i+1] = num[i];
	} 

	// Sends '4', number and it's length to arduino as string
	write(board,number,10);
	sleep(1);
	printf("\n\tCALCULATING\n\n");	
	sleep(1);
							
	// Receives the result from arduino as string and stores it to 'number'. 
	read(board,number,11);
	
	// Converts number to integer and prints the results then closes serial port
	printf("Result of %s^2 is %d\n",num,atoi(number));
	close(board);
}

// Counts button pushes
void button()
{
	// Opens serial communication and spends some time 
	char board = open(port, O_RDWR | O_NOCTTY | O_NDELAY );
	
	// Sends '5' to arduino
	write(board,"5",1);

	char check[5];
	int times = 0, counter = 0;

	while(times == 0)
	{	
		// The value read from arduino assigned to times after it stored in 'check' then converted to integer.
		read(board,check,5);
		times = atoi(check);
		if (times == 1)
		{
			// When 'times' equals 1 it means button is pushed so counter increases.
			printf("%d times pushed\n",++counter);	
			sleep(1);
			// 'times' resetted to 0.
			times = 0;								
		}
		// When times equals 2, it means red button is pushed and loop ends.
		else if (times == 2)
		{	
			printf("Goodbye!\n");
			break;
		}
	}
	//Closes serial communication
	close(board);
}
/**/