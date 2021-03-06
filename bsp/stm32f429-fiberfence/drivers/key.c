#include "key.h"
#include "delay.h"
#include "rtthread.h"
/*********************************************************************************	 
*	   
* 按键驱动代码，实现按键的扫描
*				  
**********************************************************************************/

//按键初始化函数
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOD_CLK_ENABLE();                  //开启GPIOA时钟
    
    GPIO_Initure.Pin =GPIO_PIN_10|GPIO_PIN_11|\
											GPIO_PIN_12|GPIO_PIN_13|\
											GPIO_PIN_14|GPIO_PIN_15;    //PD10-15
    GPIO_Initure.Mode=GPIO_MODE_INPUT;             //输入
    GPIO_Initure.Pull=GPIO_PULLDOWN;               //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;            //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//注意此函数有响应优先级,KEY0>KEY1>KEY2>....
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //按键松开标志
    if(mode==1)key_up=1;    //支持连按
    if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0))
    {
        //delay_ms(10);
				rt_thread_delay(100);
        key_up=0;
        if(KEY0==0)       return KEY0_PRES;
        else if(KEY1==0)  return KEY1_PRES;
        else if(KEY2==0)  return KEY2_PRES;
				else if(KEY3==0)  return KEY3_PRES;
				else if(KEY4==0)  return KEY4_PRES;
				else if(KEY5==0)  return KEY5_PRES;          
    }else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1)key_up=1;
    return 0;   //无按键按下
}
