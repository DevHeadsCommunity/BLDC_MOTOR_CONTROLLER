#include "FreeRTOS.h"

#include <stdio.h>
#include <stdlib.h>

#include "stm32f1xx.h"
#include "task.h"
#include "usart_driver.h"
#include "utils.h"
#include "timer4.h"
#include "uart.h"
#include "buck.h"
#include "adc.h"
#include "timer2.h"
#include "timer3.h"
#include "custom_init.h"
int counter = 0;
int count2 = 133;
int count3 = 266;

void vBlinkLedTask(void *pvParameters);
void vBlinkLedTask(void *pvParameters)
{
	(void)pvParameters; // Unused parameter

	while (1)
	{
		GPIOC->ODR ^= (1 << 13);		// Toggle LED
		vTaskDelay(pdMS_TO_TICKS(100)); // Delay 1000 ms (1 second)
	}
}
/*const int dutycycle[400] = {0, 57, 113, 170, 226, 282, 339, 395, 451, 507, 563, 619, 674, 730, 785, 840, 895, 950, 1004, 1058, 1112, 1166, 1219, 1272,
							1325, 1377, 1429, 1481, 1532, 1583, 1634, 1684, 1734, 1783, 1832, 1880, 1928, 1976, 2023, 2069, 2115, 2161, 2206, 2250, 2294, 2337, 2380, 2422, 2464,
							2505, 2545, 2585, 2624, 2662, 2700, 2737, 2773, 2809, 2844, 2878, 2912, 2945, 2977, 3008, 3039, 3069, 3098, 3126, 3154, 3181, 3207, 3232, 3256, 3280,
							3303, 3325, 3346, 3367, 3386, 3405, 3423, 3440, 3456, 3471, 3486, 3500, 3512, 3524, 3535, 3545, 3555, 3563, 3571, 3577, 3583, 3588, 3592, 3595, 3597,
							3599, 3599, 3599, 3597, 3595, 3592, 3588, 3583, 3577, 3571, 3563, 3555, 3545, 3535, 3524, 3512, 3500, 3486, 3471, 3456, 3440, 3423, 3405, 3386, 3367,
							3346, 3325, 3303, 3280, 3256, 3232, 3207, 3181, 3154, 3126, 3098, 3069, 3039, 3008, 2977, 2945, 2912, 2878, 2844, 2809, 2773, 2737, 2700, 2662, 2624,
							2585, 2545, 2505, 2464, 2422, 2380, 2337, 2294, 2250, 2206, 2161, 2115, 2069, 2023, 1976, 1928, 1880, 1832, 1783, 1734, 1684, 1634, 1583, 1532, 1481,
							1429, 1377, 1325, 1272, 1219, 1166, 1112, 1058, 1004, 950, 895, 840, 785, 730, 674, 619, 563, 507, 451, 395, 339, 282, 226, 170, 113, 57, 0, -57, -113,
							-170, -226, -282, -339, -395, -451, -507, -563, -619, -674, -730, -785, -840, -895, -950, -1004, -1058, -1112, -1166, -1219, -1272, -1325, -1377, -1429,
							-1481, -1532, -1583, -1634, -1684, -1734, -1783, -1832, -1880, -1928, -1976, -2023, -2069, -2115, -2161, -2206, -2250, -2294, -2337, -2380, -2422, -2464,
							-2505, -2545, -2585, -2624, -2662, -2700, -2737, -2773, -2809, -2844, -2878, -2912, -2945, -2977, -3008, -3039, -3069, -3098, -3126, -3154, -3181, -3207,
							-3232, -3256, -3280, -3303, -3325, -3346, -3367, -3386, -3405, -3423, -3440, -3456, -3471, -3486, -3500, -3512, -3524, -3535, -3545, -3555, -3563, -3571,
							-3577, -3583, -3588, -3592, -3595, -3597, -3599, -3599, -3599, -3597, -3595, -3592, -3588, -3583, -3577, -3571, -3563, -3555, -3545, -3535, -3524, -3512,
							-3500, -3486, -3471, -3456, -3440, -3423, -3405, -3386, -3367, -3346, -3325, -3303, -3280, -3256, -3232, -3207, -3181, -3154, -3126, -3098, -3069, -3039,
							-3008, -2977, -2945, -2912, -2878, -2844, -2809, -2773, -2737, -2700, -2662, -2624, -2585, -2545, -2505, -2464, -2422, -2380, -2337, -2294, -2250, -2206,
							-2161, -2115, -2069, -2023, -1976, -1928, -1880, -1832, -1783, -1734, -1684, -1634, -1583, -1532, -1481, -1429, -1377, -1325, -1272, -1219, -1166, -1112,
							-1058, -1004, -950, -895, -840, -785, -730, -674, -619, -563, -507, -451, -395, -339, -282, -226, -170, -113, -57};*/
const int dutycycle[400] = {0, 28, 55, 83, 111, 138, 166, 193, 221, 248, 275,
							303, 330, 357, 384, 411, 438, 464, 491, 518, 544, 570, 596, 622, 648,
							674, 699, 724, 749, 774, 799, 824, 848, 872, 896, 920, 943, 966, 989,
							1012, 1035, 1057, 1079, 1100, 1122, 1143, 1164, 1185, 1205, 1225, 1245,
							1264, 1283, 1302, 1320, 1338, 1356, 1374, 1391, 1407, 1424, 1440, 1456,
							1471, 1486, 1501, 1515, 1529, 1542, 1555, 1568, 1581, 1592, 1604, 1615,
							1626, 1636, 1646, 1656, 1665, 1674, 1682, 1690, 1698, 1705, 1711, 1718,
							1723, 1729, 1734, 1738, 1742, 1746, 1749, 1752, 1755, 1757, 1758, 1759,
							1760, 1760, 1760, 1759, 1758, 1757, 1755, 1752, 1749, 1746, 1742, 1738,
							1734, 1729, 1723, 1718, 1711, 1705, 1698, 1690, 1682, 1674, 1665, 1656,
							1646, 1636, 1626, 1615, 1604, 1592, 1581, 1568, 1555, 1542, 1529, 1515,
							1501, 1486, 1471, 1456, 1440, 1424, 1407, 1391, 1374, 1356, 1338, 1320,
							1302, 1283, 1264, 1245, 1225, 1205, 1185, 1164, 1143, 1122, 1100, 1079,
							1057, 1035, 1012, 989, 966, 943, 920, 896, 872, 848, 824, 799, 774, 749,
							724, 699, 674, 648, 622, 596, 570, 544, 518, 491, 464, 438, 411, 384,
							357, 330, 303, 275, 248, 221, 193, 166, 138, 111, 83, 55, 28, 0, -28,
							-55, -83, -111, -138, -166, -193, -221, -248, -275, -303, -330, -357,
							-384, -411, -438, -464, -491, -518, -544, -570, -596, -622, -648, -674,
							-699, -724, -749, -774, -799, -824, -848, -872, -896, -920, -943, -966,
							-989, -1012, -1035, -1057, -1079, -1100, -1122, -1143, -1164, -1185,
							-1205, -1225, -1245, -1264, -1283, -1302, -1320, -1338, -1356, -1374,
							-1391, -1407, -1424, -1440, -1456, -1471, -1486, -1501, -1515, -1529,
							-1542, -1555, -1568, -1581, -1592, -1604, -1615, -1626, -1636, -1646,
							-1656, -1665, -1674, -1682, -1690, -1698, -1705, -1711, -1718, -1723,
							-1729, -1734, -1738, -1742, -1746, -1749, -1752, -1755, -1757, -1758,
							-1759, -1760, -1760, -1760, -1759, -1758, -1757, -1755, -1752, -1749,
							-1746, -1742, -1738, -1734, -1729, -1723, -1718, -1711, -1705, -1698,
							-1690, -1682, -1674, -1665, -1656, -1646, -1636, -1626, -1615, -1604,
							-1592, -1581, -1568, -1555, -1542, -1529, -1515, -1501, -1486, -1471,
							-1456, -1440, -1424, -1407, -1391, -1374, -1356, -1338, -1320, -1302,
							-1283, -1264, -1245, -1225, -1205, -1185, -1164, -1143, -1122, -1100,
							-1079, -1057, -1035, -1012, -989, -966, -943, -920, -896, -872, -848,
							-824, -799, -774, -749, -724, -699, -674, -648, -622, -596, -570, -544,
							-518, -491, -464, -438, -411, -384, -357, -330, -303, -275, -248, -221,
							-193, -166, -138, -111, -83, -55, -28};

int main()
{
	sysclock_init();
	systick_init();
	timer4_Init();
	delay_ms(10);
	uart_init();
	delay_ms(5);
	adc_Init();
	timer2_Init();
	buck_init();
	timer3_Init();
	// xTaskCreate(vBlinkLedTask, "BlinkTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	//  vTaskStartScheduler();
	//  TIM2->CR1 |= 1 << 0;
	TIM3->CR1 |= 1 << 0;
	TIM1->CR1 |= 1 << 0;
	while (1)
	{
		GPIOC->ODR ^= (1 << 13); // Toggle LED
		delay_ms(1000);
	}
}

void TIM2_IRQHandler(void)
{
	/* PA0 = ADCVALUE[1];
	 * PA1 = ADCVALUE[2];
	 * PA4 = ADCVALUE[3];
	 * PA5 = ADCVALUE[0];
	 *
	 * */

	timer2_counter++;

	adc1 = adcValue[1] + adc1; // pa0
	adc2 = adcValue[3] + adc2;
	adc3 = adcValue[2] + adc3;
	adc4 = adcValue[3] + adc4;
	if (timer2_counter > 100)
	{

		//		dcCurrent = ((adc1 / 70));
		//		dcCurrent = dcCurrent * (3.3 / 4095.0);
		//		dcCurrent /= gain;
		//		dcCurrentPeak = dcCurrent / shunt;
		// battery = (((adc2 / 70) * 3.3) / 372.2) - 0.11;
		// battery = ((((adc1 / timer2_counter) / 40.5444) * 3.3) + 0.95) - 2.29 - 0.44 + 0.22;
		if((adc1 / timer2_counter) < 500)
		{
           feedback = 500 * 0.0002442;
		}
		else{
          feedback = (adc1 / timer2_counter) * 0.0002442; //1 / 4095;
		}
		

		adc1 = adc2 = adc3 = adc4 = 0;
		timer2_counter = 0;
	}

	TIM2->SR &= ~(1 << 0); // ack the interrupt
}

void TIM1_IRQHandler(void)
{

	/* //

	//		if (feedBack < 200) {
	//			feedBackTimer++;
	//			if (feedBackTimer > 50000)
	//				inv_Off();
	//		}

	count1++;
	count2++;
	count3++;

	if (count1 > 400)
	{
		count1 = 0;
	}

	if (count2 > 400)
	{
		count2 = 0;
	}

	if (count3 > 400)
	{
		count3 = 0;
	}
	duty = dutycycle[count1] * 0.5;
	duty1 = dutycycle[count2] * 0.5;
	duty2 = dutycycle[count3] * 0.5;
	// TIM1->CCR1 = 1760 + (duty);
	// TIM1->CCR2 = 1760 + (duty1);
	TIM1->CCR1 = duty;
	TIM1->CCR2 = duty1;
	TIM1->CCR3 = duty2;
*/
	TIM1->SR &= ~(1 << 0);
}

/*void TIM3_IRQHandler(void)
{

	//

	//		if (feedBack < 200) {
	//			feedBackTimer++;
	//			if (feedBackTimer > 50000)
	//				inv_Off();
	//		}

	count1++;
	if (count1 >= 400)
		count1 = 0; // Wrap around after full sine table

	// Apply 120° phase shift offsets (67 for 120° and 134 for 240°)
	int index_U = count1;
	int index_V = (count1 + 133) % 400; // Phase V (120° shift)
	int index_W = (count1 + 266) % 400; // Phase W (240° shift)

	// Update duty cycles for each phase
	TIM1->CCR1 = dutycycle[index_U]; // Phase U (No phase shift)
	TIM1->CCR2 = dutycycle[index_V]; // Phase V (120° shift)
	TIM1->CCR3 = dutycycle[index_W]; // Phase W (240° shift)

	// Clear Timer3 interrupt flag
	TIM3->SR &= ~(1 << 0);
}*/

void TIM3_IRQHandler(void)
{
	// Counter for sine wave table index

	// Increment counter and wrap around at 400 (end of sine table)
	count1++;
	if (count1 >= 400)
	{
		count1 = 0;
	}

	/* // Calculate indices for 120° and 240° phase shifts
	 int index_U = count1;                       // Phase U
	 int index_V = (count1 + 133) % 400;         // Phase V (120° shift)
	 int index_W = (count1 + 266) % 400;         // Phase W (240° shift)

	 // Scale the sine table values for duty cycle adjustment
	 int duty_U = dutycycle[index_U] * 0.5;
	 int duty_V = dutycycle[index_V] * 0.5;
	 int duty_W = dutycycle[index_W] * 0.5;

	 // Update Timer1 CCR registers for 3-phase PWM
	 TIM1->CCR1 = 1760 + duty_U;  // Phase U
	 TIM1->CCR2 = 1760 + duty_V;  // Phase V
	 TIM1->CCR3 = 1760 + duty_W;  // Phase W
 */

	// Read Hall sensor inputs
	int H1 = (GPIOA->IDR & H1_PIN) ? 1 : 0; // PB0
	int H2 = (GPIOA->IDR & H2_PIN) ? 1 : 0; // PB1
	int H3 = (GPIOA->IDR & H3_PIN) ? 1 : 0; // PB10

	// Determine commutation step based on Hall sensor state
	int hall_state = (H3 << 2) | (H2 << 1) | H1;
	switch (hall_state)
	{
	case 0b101:
		commutation_step = 1;
		break;
	case 0b001:
		commutation_step = 2;
		break;
	case 0b011:
		commutation_step = 3;
		break;
	case 0b010:
		commutation_step = 4;
		break;
	case 0b110:
		commutation_step = 5;
		break;
	case 0b100:
		commutation_step = 6;
		break;
	default:
		commutation_step = 0; // Error state
	}

	int index_offset = (commutation_step - 1) * (400 / 6);
	int index_U = (count1 + index_offset) % 400; // Phase U
	int index_V = (index_U + 133) % 400;		 // Phase V (120° shift)
	int index_W = (index_U + 266) % 400;		 // Phase W (240° shift)

	// Scale the sine table values for duty cycle adjustment
	int duty_U = dutycycle[index_U] * feedback;
	int duty_V = dutycycle[index_V] * feedback;
	int duty_W = dutycycle[index_W] * feedback;

	// Update Timer1 CCR registers for 3-phase PWM
	TIM1->CCR1 = 1760 + duty_U; // Phase U
	TIM1->CCR2 = 1760 + duty_V; // Phase V
	TIM1->CCR3 = 1760 + duty_W; // Phase W
	// Clear the Timer3 interrupt flag
	TIM3->SR &= ~(1 << 0);
}
