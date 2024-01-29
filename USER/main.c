#include "sys.h" 
#include "delay.h"
#include "usart.h"
#include "bee.h"  
#include "icm20602.h" 
#include "tim.h"

extern int tm_sec;
int tm_min;
int tm_hour;

	
int main(void)
{   
	delay_init(168);
	OLED_Init();
	TIM3_Init(10000,8400);
    
    tm_sec=0;
	
    while (1)
   {     
	   if(tm_sec>=60)
	   {
		   tm_sec=0;
		   tm_min++;
		   
	   }
	   if(tm_min>=60)
	   {
		   tm_min=0;
		   tm_hour++;
	   }
	   if(tm_hour>=24)
	   {
		   tm_hour=0;
	   }
	   OLED_ShowNum(1,1,tm_hour,2);
	   OLED_ShowChar(1,3,':');
	   OLED_ShowNum(1,4,tm_min,2);
	   OLED_ShowChar(1,6,':');
	   OLED_ShowNum(1,7,tm_sec,2);
	   
   }  
		
}

