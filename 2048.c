//version 2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#define GRID_LEN 16
int M[GRID_LEN];   // The board
int X = GRID_LEN;  // Shorthand for 16
int W;             // Game over bit mask: 1 = won , 2 = not Lost
int a;
int K[] = { 2, 3, 1 }; // Translation table between keyboard key
					   // code and direction. Note that since K[3]
					   // is in BSS and most likely 0, but not guaranteed.
int pts;
int temp1,temp2,temp3;
int point=0;

int b=0;
int w (int d, int i, int j) // Declare translation function from direction and relative position to absolute position
{						    // d = The direction ; i = Row Number ; j = Column Number

  if (d <= 0) {				
    return 4 * i + j;		// Base case at direction 0
  }

  return w (d - 1, j, 3 - i); //Recursively call myself to find direction -1
}

void s (int f, int d) //Declare our shift function, If false, will simulate a shift only
{
  int i = 4, j, l, P; // i=> Temp var to hold current row  | j=>The read head  | l=> Temp var to store Last value read in row | P => Temp var to hold "current value" in row 
//  pts = 0;
  
  while(i--) {  //Loop over each row
    temp1 = a = temp2 = 0;
    
    while(a < 4)  //Loop over each column
	{  
	  
      if (temp1 < 4) { //Are there still values to read in the row?
        temp3 = M[w (d, i, temp1++)]; //Store the read value in row accounting for direction, increment read head
        W = W | (temp3 >> 11); // Is stored value 2048 (1<<11)? if so, filp the first bit in winning mask 	W|
		
		if(f){
			if(temp2 == temp3){
				point = point + temp2*2;
			}
		}
        temp2 * temp3 && 
					(    // If Last value read and current value are not 0  //If not read only, use write head to write
							// The Last value if not equal to current or double the last value if it is
					
					f ? M[w (d, i, a)] =  temp2 << (temp2 == temp3) : 0  
					, a++
					);  // Increment the write head
					
					
					
					
					
					
		
        temp2 = temp2 ? (temp3 ? (temp2 - temp3 ? temp3 : 0) : temp2) : temp3; // Set the last value according to the value of the last and current values.

      }
      else {
        f ? M[w (d, i, a)] = temp2 : 0; //If not read-only, write the last value(may be zero)
        ++a;						    //Increment the write head
        W |= 2 * !temp2;				//If we are write a 0 here, that means board isn't full so set winning mask bit 2
        temp2 = 0;						//set last to zero so that the next write will be padding
      }
    }

  }
}

void T () //Deaclare main game logic function , General temp variable
{
  int i = X + rand () % X; //First, set i to be a random number grater than 16

  while(M[i % X] * i)
  {
	i--; //Loop while i mod 16 points to a filled cell and i>0 // Decrement i
  }

  i ? M[i % X] = 2 << rand () % 2 : 0; //If i is zero , it means we've looped over the board at least once and did not find an empty cell Set empty cell to be 2 or 4
  W = i = 0;

  while(i < 4){  //Clear winning mask, loop over all four directions and simulate shifts in read-only made.
    s (0, i);
	i++;
  }

  // Prints the tiles onto the terminal
  i = X;     
//	  printf("(a >> X )%4 = %d\n",(a>>X)%4);  
 puts ("\e[2J\e[H"); //Clear screen and move cursor to 1,1 using ANSI codes.

  while(i--)
  {  if (M[i]) {                     //Is cell non-empty
		printf ("%4c|", M[i]==2    ?    'a'     :        
						M[i]==4    ?    'b'     :
						M[i]==8    ?    'c'     :
						M[i]==16   ?    'd'     :
						M[i]==32   ?    'e'     :
						M[i]==64   ?    'f'     :
						M[i]==128  ?    'g'     :
						M[i]==256  ?    'h'     :
						M[i]==512  ?    'i'     :
						M[i]==1024 ?    'j'     :
						M[i]==2048 ?    'k'     : 'fuck' );        //Print Lpadded interger value of cell
		
		} else {
		printf ("%s", "    |");        //Print empty cell
		}
	
		// every 4th cell is followed by a line-break
		if (0 == (i & 3)) {
		putchar ('\n');
		}
  }
  printf ("temp1 : %d \n", temp1);  
  printf ("temp2 : %d \n", temp2); 
  printf ("temp3 : %d \n", temp3);  
  // printf ("pts : %d \n", pts);  
  printf ("point : %d \n",point);
//  wait(100000);

  // read input from keyboard
  if (!(W - 2)) { //If we haven't won
 
    read (0, &a, 3); // Read 3 bytes of cursor sancode into a as an int
	
    
	
	switch (a) {
		case 4479771: b=0;
				 break;
		case 4348699: b=2;
				 break;
		case 4414235: b=3;
				 break;
		case 4283163: b=1;
				 break;
		case 114:   b=0;
					for(b=0;b<16;b++){
						M[b] = 0;
					}
					temp1 = 0;
					temp2 = 0;
					temp3 = 0;
					point = 0;
					system ("stty cbreak");
					 srand ((unsigned) time (NULL));
					
					
								break;
				 
	
	
	}
	
	printf("(a >> X )%4 = %d\n",(a>>X));
	printf("a = %d, X = %d ,b = %d\n",a,X,b);
	
    s (1, K[b]); // But first,shift based on key pressed , Not in read-only mode , Reshift scancode buffer by two bytes, and lookup direction in translation table
    T (); //Recursively call myself to process next iteration of game loop
	//4479771 left ,4348699 down,4414235 right  ,4283163 up , 114 r
  }
}


int main (void)
{
  
  // Uses stty to clear the screen in preparation for the game
  system ("stty cbreak");

  /* Intializes random number generator */
  srand ((unsigned) time (NULL));

  T ();

  // Game has finished by this point
  // If win, display "WIN". Otherwise, display "LOSE".
  puts (W & 1 ? "win" : "lose");
 
  
  
  
  return 0;
}
