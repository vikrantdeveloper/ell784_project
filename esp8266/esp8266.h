#ifndef __ESP8266__


#define CR                       "\r"
#define NR                       "\n"

#define WIFI_START_CMD      	"AT\r\n"                                            /*start command*/
#define WIFI_RST_CMD        	"AT+RST\r\n"										/*reset command*/
#define WIFI_MODE_CMD           "AT+CWMODE=%d\r\n"							    /*access point mode configuration command*/
#define WIFI_CONNECT_AP_CMD   	"AT+CWJAP=\"%s\",\"%s\"\r\n" 			            /*connect to access point ssid ,psk*/
#define WIFI_GMR_CMD            "AT+GMR\r\n"
#define WIFI_MAC_CMD            "AT+CIFSR\r\n"
#define WIFI_IP_ADDR             "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n"   /*tcp ip address and port number*/
//#define TCP_LOCAL_HOTSPOT       "AT+CIPMUX?\r\n"

#define WIFI_RX_LEN            512

typedef void (*console_buff_log_t)(char * , size_t *);          /*clear & print logs*/


////////////////////////////////////////// STRUCTURE CONFIGURATION /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum{
	WIFI_STA_MODE,
	WIFI_AP_MODE,
	WIFI_ST_AP_MODE
}wifi_mode_config;

typedef enum{
	MS_NOT_OK,
	MS_OK
}wifi_api_status;

typedef struct{

	char *WiFi_Tx;
	size_t WiFi_Tx_len;
	union fl_con_u8 {
		 float f;
		 uint8_t u[4];
	} fl_con_u8_pt;

	char WiFi_Rx[WIFI_RX_LEN + 1];
	size_t WiFi_Rx_len;
	console_buff_log_t log_buf;
	console_buff_log_t log_clr;

}Wifi_Uart;

extern Wifi_Uart Wifi_Uart_t;
extern UART_HandleTypeDef console_uart;

#ifdef __cplusplus
extern "C"{

#endif



wifi_api_status wifi_mode(wifi_mode_config cnt);
wifi_api_status wifi_ap_connect();
wifi_api_status wifi_rst();
void wifi_init();
void wifi_resp_check();
void console_init();
wifi_api_status wifi_version();
wifi_api_status wifi_comm_check();
wifi_api_status wifi_mac_add();
wifi_api_status tcp_server_conn();
wifi_api_status wifi_send_fl_data(float buf[] , int len);
wifi_api_status wifi_log_thingspeak(char *APIkey , int bitfield , int buf[]);

int _write(int file, char *ptr, int len);


#ifdef __cplusplus
}
#endif

#endif




