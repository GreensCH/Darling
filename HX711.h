#ifndef __HX711_H
#define	__HX711_H

/* 只需要修改下面的代码即可改变控制的引脚 */
#define ADDO_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define ADDO_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define ADDO_GPIO_PIN		GPIO_Pin_2			        /* 连接到SCL时钟线的GPIO */

#define ADSK_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define ADSK_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define ADSK_GPIO_PIN		GPIO_Pin_1			        /* 连接到SCL时钟线的GPIO */

void HX711_GPIO_Init(void);
unsigned long ReadCount(void);

#endif /* __HX711_H */

