
#include "led.h"  
#include "delay.h"
#include "usart.h"
#include "OLED.h"
#include "bee.h"  
#include "w25q128.h"
#include "HMC5883L.h"
#include "bmp280.h"
#include "icm20602.h"
#include "bmi088.h"
// 定义状态转换表为一个二维数组，数组元素为state_transition_t结构体
// 数组的行表示当前状态，数组的列表示事件
state_transition_t state_transition_table[3][3] = {
    // 红灯状态转换
    {{RED,  TURN_ON_YELLOW}, {YELLOW, TURN_ON_GREEN}, {GREEN, TURN_ON_RED}},
    // 黄灯状态转换
    {{RED,  TURN_ON_YELLOW}, {YELLOW, TURN_ON_GREEN}, {GREEN, TURN_ON_RED}},
    // 绿灯状态转换
    {{RED,  TURN_ON_YELLOW}, {YELLOW, TURN_ON_GREEN}, {GREEN, TURN_ON_RED}}
};
// 定义一个变量来存储系统的当前状态
state_t current_state;
void state_init(void)
{

 current_state = RED;
}


// 定义一个函数来处理事件并执行状态转换
void handle_event(event_t event) {
    // 从状态转换表中获取下一个状态和动作
    state_t next_state = state_transition_table[current_state][event].next_state;
    action_t action = state_transition_table[current_state][event].action;
    // 执行输出动作
    switch (action) {
        case TURN_ON_RED:
           printf("Turn on red light\r\n"); // 打印打开红灯信息
          OLED_ShowString(1, 3, "Turn on red light");
				 icm20602_test();
				LED2_ON;
					LED1_OFF;LED3_OFF;
            break;
        case TURN_ON_YELLOW:
           printf("Turn on yellow light\r\n"); // 打印打开黄灯信息
				OLED_ShowString(1, 3, "Turn on yellow light");
				bmp280_test();
				bmi088_test();
				Bee_OFF;
				LED3_ON
        LED1_OFF;LED2_OFF
            break;
        case TURN_ON_GREEN:
            printf("Turn on green light\r\n"); // 打印打开绿灯信息
				OLED_ShowString(1, 3, "Turn on green light");
				hmc_read_xyz();
				//Flsh_test();
				Bee_OFF;
				LED1_ON;LED2_OFF;LED3_OFF;
            break;
        default:
						LED1_OFF;LED2_OFF;LED3_OFF
            printf("Invalid action\r\n"); // 打印无效动作信息
				OLED_ShowString(1, 3, "Invalid action");
            break;
    }

    // 更新当前状态
    current_state = next_state;
}

// 定义一个函数来模拟一些事件并测试状态机
void test_state_machine() {
    // 模拟一些事件并处理它们
    handle_event(RED_TIMEOUT); // 打开黄灯并进入黄灯状态
	 delay_ms(700);
    handle_event(YELLOW_TIMEOUT); // 打开绿灯并进入绿灯状态
	 delay_ms(700);
    handle_event(GREEN_TIMEOUT); // 打开黄灯并进入黄灯状态
	 delay_ms(700);
	//handle_event(ddd); // 打开黄灯并进入黄灯状态
}





// 函数：LED IO口初始化
//



void LED_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
	RCC_AHB1PeriphClockCmd ( LED1_CLK, ENABLE); 	//初始化GPIOG时钟	
	RCC_AHB1PeriphClockCmd ( LED2_3_CLK, ENABLE); 	//初始化GPIOG时钟	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz; //速度选?
	//初始化 LED1 引脚
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	 
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度选?
	GPIO_InitStructure.GPIO_Pin = LED2_PIN|LED3_PIN;	 
	GPIO_Init(LED2_3_PORT, &GPIO_InitStructure);	
  LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}
void Flsh_test(void)
{


}
