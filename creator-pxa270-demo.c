#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <errno.h>

#include "def.h"
#include "creator_pxa270_lcd.h"
#include "creator_lib.h"

int 
main (int argc, char**argv)
{
        int		fd;
        int i=0, number[10]={0,1,2,3,4,5,6,7,8,9};
		
		int ret;
		unsigned short value;
		
	unsigned short key;
	unsigned short input;
	unsigned short output;
	unsigned char KeyASCIICode[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','*','#'};

//***************************************************************************
        
	fd = open("/dev/lcd", O_RDWR);
        
        if (fd < 0){
            printf("open /dev/lcd error\n");
            return(-1);
            }
            
        LCD_fClearScreen(fd);
        //LCD_fprintf(fd, "Lab 7 : test LCD \n\n");
//***************************************************************************
//LCD_fprintf(fd," A | A | A | A \n---|---|---|---\n A | A | A | A \n---|---|---|---\n A | A | A | A \n---|---|---|---\n A | A | A | A \n");    
LCD_fprintf(fd,"   |   |   |   \n A | A | A | A \n   |   |   |   \n---+---+---+---\n   |   |   |   \n A | A | A | A \n   |   |   |   \n---+---+---+---\n   |   |   |   \n A | A | A | A \n   |   |   |   \n---+---+---+---\n   |   |   |   \n A | A | A | A \n   |   |   |   \n");
while(1)
{
//LCD_fprintf(fd," A | A | A | A \n---|---|---|---\n A | A | A | A \n---|---|---|---\n A | A | A | A \n---|---|---|---\n A | A | A | A \n");    
if(KEYPAD_get_key(fd, &key) == OK)
	{
	input = key;
	ret = ioctl(fd,Write_data,&input);
	ret = ioctl(fd,Read_data,&output);		
        LCD_fClearScreen(fd);
	    //LCD_fprintf(fd, "key = %c\n", KeyASCIICode[key]);
		LCD_fprintf(fd, "reply key = %c\n", KeyASCIICode[output]);
	}
	

} 
        close(fd);
	return(0);
}
