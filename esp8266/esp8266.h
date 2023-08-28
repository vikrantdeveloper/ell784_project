#ifndef __ESP8266__


#include "main.h"
#include "stm32f0xx_hal_uart.h"
#include <string.h>
#include <stdio.h>



#define  true                   1
#define  false                  0

#define UART_WIFI_CMD            USART5
#define UART_CONSOLE             huart2

#define CR                       "\r"
#define NR                       "\n"

#define WIFI_START_CMD      	"AT\r\n"                                            /*start command*/
#define WIFI_RST_CMD        	"AT+RST\r\n"										/*reset command*/
#define WIFI_MODE_CMD(x)      	"AT+CWMODE="##x##CR##NR 							/*access point mode configuration command*/
#define WIFI_CONNECT_AP_CMD   	"AT+CWJAP=\"AndroidSDC\",\"jsrb0337\"\r\n" 			/*connect to access point ssid ,psk*/
#define WIFI_GMR_CMD            "AT+GMR\r\n"
#define WIFI_MAC_CMD            "AT+CIFSR\r\n"
#define TCP_LOCAL_HOTSPOT       "AT+CIPSTART=\"TCP\",\"192.168.149.67\",8888\r\n"
//#define TCP_LOCAL_HOTSPOT       "AT+CIPMUX?\r\n"

#define WIFI_RX_LEN            512

typedef void (*console_buff_log_t)(char * , size_t *);          /*clear & print logs*/


////////////////////////////////////////// STRUCTURE CONFIGuRATION /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum{
	WIFI_STA_MODE,
	WIFI_AP_MODE,
	WIFI_ST_AP_MODE
}wifi_mode_config;

typedef struct{

	char *WiFi_Tx;
	uint8_t WiFi_Tx_len;

	char WiFi_Rx[WIFI_RX_LEN + 1];
	size_t WiFi_Rx_len;
	console_buff_log_t log_buf;
	console_buff_log_t log_clr;

}Wifi_Uart;

extern Wifi_Uart Wifi_Uart_t;
extern UART_HandleTypeDef UART_CONSOLE;

#ifdef __cplusplus
extern "C"{

#endif



uint8_t wifi_mode(wifi_mode_config wifi_se_mode_t);
uint8_t wifi_ap_connect();
uint8_t wifi_rst();
void wifi_init();
void wifi_resp_check();
uint8_t wifi_version();
uint8_t wifi_comm_check();
uint8_t wifi_mac_add();
uint8_t tcp_server_conn();



#ifdef __cplusplus
}
#endif

#endif




