/**************************************************************************************************
  Filename:      sh10.c

  Description:    sh10 driver 
                  
**************************************************************************************************/

/******************************************************************************
 * INCLUDES
 */
#include "ioCC2530.h"
#include "hal_defs.h"
#include "hal_types.h"
#include "get_adc.h"


/******************************************************************************
 * GLOBAL VARIABLES
 */
void hal_adc_Init(void);
 uint16 readVoltage(void);
//static volatile uint32 value;

void hal_adc_Init(void)
{
	APCFG  |=1;   
        P0SEL  |= (1 << (0));	
        P0DIR  &= ~(1 << (0));	
    
}
/******************************************************************************
 * 名称       get_adc
 * 功能       读取A/D值
 * 入口参数   无
 * 出口参数   16位电压值，分辨率为10mV, 如0x0102表示2.58V
 *****************************************************************************/
uint16 get_adc(void)
{
   uint32 value;
   hal_adc_Init(); // ADC初始化
   ADCIF = 0;   //清ADC 中断标志
   //采用基准电压avdd5:3.3V，通道0，启动AD转化
   ADCCON3 = (0x80 | 0x10 | 0x00);
   while ( !ADCIF )
   {
       ;  //等待AD转化结束
   }
   value = ADCH;
   value = value<< 8;
   value |= ADCL;
  // AD值转化成电压值
  // 0 表示 0V ，32768 表示 3.3V
  // 电压值 = (value*3.3)/32768 （V)
  value = (value * 330);
  value = value >> 15;   // 除以32768
  // 返回分辨率为0.01V的电压值
  return (uint16)value;
}

























