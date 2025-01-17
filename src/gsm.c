#include "gsm.h"
#include "timer4.h"

char value33[10] = { 0 };
char jsonPayload[350];
char gsm_uart_data;
char gsm_uart_data2[300] = { 0 };
int data_position = 0;
int time_push = 0;
char push_data = 0;
int readFlag = 0;
char* buff_() {
	readFlag = 1;
	//delay_ms(1);
	return gsm_uart_data2;

}

//
//void sendCommand(char *cmd, int Mdelay){
//	gsm_printf(cmd);
//
//}

void gsm_send_to_server(int battery_percent, int energy_inv_used,
		int energy_grid_used, int energy_generated, int grid_avail,
		int solar_avail, int device_id, char *duration) {

	memset(jsonPayload, '\0', strlen(jsonPayload));
	memset(value33, '\0', strlen(value33));
	sprintf(jsonPayload,
			"{\"battery_percent\": %d, \"energy_generated\": %d, \"energy_consumed\": %d, \"grid_available\": %d,  \"solar_available\": %d, \"battery_duration\": %s, \"energy_grid_used\": %d, \"energy_inv_used\": %d}",
			battery_percent, energy_generated, device_id, grid_avail,
			solar_avail, duration, energy_grid_used, energy_inv_used);
	// Send the HTTP POST request with the JSON payload
	gsm_printf("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n"); // Set GPRS connection type
	delay_ms(2000);
	//uart_printf(jsonPayload);
	gsm_printf("AT+SAPBR=3,1,\"APN\",\" APN \"\r\n"); // Set APN
	delay_ms(2000);
	gsm_printf("AT+SAPBR=1,1\r\n"); // Set APN
	delay_ms(2000);
	gsm_printf("AT+HTTPINIT\r\n");
	delay_ms(2000);
	gsm_printf("AT+HTTPPARA=\"CID\",1\r\n");
	delay_ms(2000);
	gsm_printf(
			"AT+HTTPPARA=\"URL\",\"http://homefort-be-staging-41ad105d39de.herokuapp.com/v1/solar-service/record-solar-readings/10\"\r\n");
	//gsm_printf("AT+HTTPPARA=\"URL\",\"http://webhook.site/be0ee5b0-7171-4afa-8044-a333847698e4\"\r\n");
	delay_ms(2000);
	gsm_printf("AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n");
	delay_ms(1000);
	gsm_printf("AT+HTTPDATA=");
	gsm_printnn(strlen(jsonPayload));
	gsm_printf(",10000\r\n");
	delay_ms(2000);
	gsm_printf(jsonPayload);
	delay_ms(3000);
	USART2->CR1 |= 1 << 5;
	gsm_printf("AT+HTTPACTION=1\r\n");
	delay_ms(20000); // Wait for response
	//	gsm_printf("AT+HTTPREAD\r\n");
	//delay_ms(5000); // Wait for response

	// Terminate HTTP session

	gsm_printf("AT+HTTPTERM\r\n");
	delay_ms(5000);

	gsm_printf("AT+SAPBR=0,1\r\n");
	delay_ms(3000);
	gsm_printf("AT+CFUN=1,1\r\n");
	delay_ms(3000);
	USART2->CR1 &= ~(1 << 5);

//	memset(jsonPayload, '\0', strlen(jsonPayload));
//	memset(value33, '\0', strlen(value33));
//	sprintf(jsonPayload, "{\"battery\": %d, \"energy\": %d, \"inv_voltage\": %d}",
//			battery_voltage, energy, inv_voltage);
//	// Send the HTTP POST request with the JSON payload
//	gsm_printf("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n"); // Set GPRS connection type
//	delay_ms(1000);
//	gsm_printf("AT+SAPBR=3,1,\"APN\",\" APN \"\r\n"); // Set APN
//	delay_ms(1000);
//	gsm_printf("AT+SAPBR=1,1\r\n"); // Set APN
//	delay_ms(5000);
//	gsm_printf("AT+HTTPINIT\r\n");
//	delay_ms(5000);
//	gsm_printf("AT+HTTPPARA=\"CID\",1\r\n");
//	delay_ms(1000);
//	gsm_printf(
//			"AT+HTTPPARA=\"URL\",\"http://webhook.site/667211f9-6418-477d-80dd-258843ab9d66\"\r\n");
//	delay_ms(3000);
//	gsm_printf("AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n");
//	delay_ms(1000);
//	gsm_printf("AT+HTTPDATA=");
//	delay_ms(1000);
//	gsm_printnn(strlen(jsonPayload));
//	gsm_printf(",10000\r\n");
//	delay_ms(1000);
//	gsm_printf(jsonPayload);
//	delay_ms(1000);
//	gsm_printf("AT+HTTPACTION=1\r\n");
//	delay_ms(20000); // Wait for response
//	//gsm_printf("AT+HTTPREAD\r\n");
//	//delay_ms(5000); // Wait for response
//
//	// Terminate HTTP session
//	gsm_printf("AT+HTTPTERM\r\n");
//	delay_ms(3000);
//	gsm_printf("AT+SAPBR=0,1\r\n");
//	delay_ms(1000);
//	gsm_printf("AT+CFUN=1,1\r\n");
//	delay_ms(1000);

}

void gsm_init() {
//	AFIO->MAPR |= 1<<2; // remap uart to pb6 for tx pb7 for rx
	RCC->APB2ENR |= 1 << 2;
	RCC->APB2ENR |= 1 << 0;
	RCC->APB1ENR |= 1 << 17;
	GPIOA->CRL &= ~(0x0F << 8);   //clearing tx pin to make all zeros
	GPIOA->CRL |= (0x0B << 8); //setting the Tx pin to output, and alternate function push pull 1011
	///GPIOC ->CRH &= ~(0x0F << 20);
	//GPIOC ->CRH |= (3 << 20);
	// setting the rx pin is not necessary, because at reset the pins are set as input  ** TAKE NOTE*
	//GPIOB ->CRL &= ~(0x0F << 28);   //clearing rx pin to make all zeros
	//GPIOB ->CRL |= (1 << 28);    //setting the rx pin to input

	//setting the baudrate in BRR register
	USART2->BRR = 0xEA6;	//0x271;//0x1D4C; // setting the baudrate to 9600

	// enabling interrupt on uasart1 for tx and rx
	//USART2 -> CR1 |= (0xA0 <<0);
	//USART1->CR1 |= 1 << 5;
	//USART2->CR1 |= USART_CR1_RXNEIE;

	// enabling the tx, rx and uart enable7
	USART2->CR1 |= (3 << 2); // enabling tx and rx
	USART2->CR1 |= (1 << 13);   // enabling usart1
	NVIC_EnableIRQ(USART2_IRQn);

}
void USART2_IRQHandler(void) {

	if ( USART2->SR & 0x20) {
		if (readFlag == 1) {
			data_position = strlen(gsm_uart_data2);
//			memset
			for (int i = 0; i < data_position; i++) {
				gsm_uart_data2[i] = 0;
				//delay_ms(1);
			}
			data_position = 0;
		}
		readFlag = 0;
		gsm_uart_data2[data_position] = (char) USART2->DR;
		data_position++;

	}

	uart_printf(buff_());
	//uart_printf("\n\r");

//	char c = (char) USART2->DR;
//	if(c != '\n' || c!='\r'){
//		gsm_uart_data = c;
//	}

}

void gsm_print(uint8_t data) {
	USART2->DR = data;

	while (!(USART2->SR & 0x40))
		;
}

void gsm_printf(char *str) {

	while (*str) {
		gsm_print(*str);
		str++;
		for (long i = 0; i < 100; i++)
			;
	}

}
void gsm_printnn(int numb) {
	sprintf(value33, "%d", numb);
	gsm_printf(value33);
}

void gsm_printn(float x) {
//char value1[10];
//	sprintf(value1, "%d", d_numb);
//	//lcd_clear();
//	uart_print('\0');
//	uart_printf((char*) value1);

	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint16_t e, g, h, t = 0;

	t = x;
	a = (t / 1000);
	b = ((t / 100) % 10);
	c = ((t / 10) % 10);
	d = (t % 10);
	x = x - t;
	e = x * 100;
	g = e / 10;
	h = e % 10;

	if (a == 0) {

	} else {
		gsm_print(a + 0x30);
	}
	if ((b == 0) && (a == 0)) {

	} else {
		gsm_print(b + 0x30);
	}

	if ((b == 0) && (a == 0) && (c == 0)) {

	} else {
		gsm_print(c + 0x30);
	}
	gsm_print(d + 0x30);
	delay_ms(1);
	gsm_print('.');
	delay_ms(5);
	gsm_print(g + 0x30);
	delay_ms(5);
	gsm_print(h + 0x30);

}

void gsm_process_data() {
	uint8_t letter;
//	if (USART2->SR & (1 << 5)) {
//
//		letter = USART2->DR;
//	//	uart_output_char(letter);
//
//	}
}

// Construct the JSON payload
