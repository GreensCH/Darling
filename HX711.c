#include "HX711.h"
/*
* @title：
* @func:
* @para:
*/

void HX711_GPIO_Init(void)
{		
    /*开启相关的GPIO外设时钟*/
    RCC_APB2PeriphClockCmd( ADDO_GPIO_CLK | ADSK_GPIO_CLK , ENABLE);

    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure_ADSK;
    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure_ADSK.GPIO_Pin = ADSK_GPIO_PIN;	
    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure_ADSK.GPIO_Mode = GPIO_Mode_Out_PP;   
    /*设置引脚速率为50MHz */   
    GPIO_InitStructure_ADSK.GPIO_Speed = GPIO_Speed_50MHz; 
    /*调用库函数，初始化GPIO*/
    GPIO_Init(ADSK_GPIO_PORT, &GPIO_InitStructure_ADDO);
    /*拉高禁用*/
    GPIO_SetBits(ADSK_GPIO_PORT, ADDO_GPIO_PIN);	
    
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure_ADDO;
    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure_ADDO.GPIO_Pin = ADDO_GPIO_PIN;
    /*设置按键的引脚为浮空输入*/
	GPIO_InitStructure_ADDO.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    /*调用库函数，初始化GPIO*/
    GPIO_Init(ADDO_GPIO_PORT, &GPIO_InitStructure_ADDO);
    
}


unsigned long ReadCount(void) 
{
    unsigned long Count=0;
    unsigned char i;
    GPIO_ResetBits(ADSK_GPIO_PORT,ADSK_GPIO_PIN);//ADSK=0;使能AD（PD_SCK 置低）

    while(1==GPIO_ReadInputDataBit(ADSK_GPIO_PORT,ADSK_GPIO_PIN)); //AD转换未结束则等待，否则开始读取
    for (i=0;i<24;i++)
    {
        GPIO_SetBits(ADSK_GPIO_PORT,ADSK_GPIO_PIN); //PD_SCK 置高（发送脉冲）
        Count=Count<<1; //下降沿来时变量Count左移一位，右侧补零
        GPIO_ResetBits(ADSK_GPIO_PORT,ADSK_GPIO_PIN); //PD_SCK 置低
        if(1==GPIO_ReadInputDataBit(ADSK_GPIO_PORT,ADSK_GPIO_PIN)) 
            Count++;
    }
    GPIO_SetBits(ADSK_GPIO_PORT,ADSK_GPIO_PIN);
    Count=Count^0x800000;//第25个脉冲下降沿来时，转换数据
    GPIO_ResetBits(ADSK_GPIO_PORT,ADSK_GPIO_PIN);
    return(Count);
}