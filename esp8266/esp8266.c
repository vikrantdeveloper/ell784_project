#include "common.h"
#include "esp8266.h"

UART_HandleTypeDef wifi_cmd_uart;
UART_HandleTypeDef console_uart;
Wifi_Uart Wifi_Uart_t;
char tmp;


void Wifi_UART_Init(void)
{
  /* USER CODE BEGIN UART5_Init 2 */
  wifi_cmd_uart.Instance = UART_WIFI_CMD;
  wifi_cmd_uart.Init.BaudRate = 115200;
  wifi_cmd_uart.Init.WordLength = UART_WORDLENGTH_8B;
  wifi_cmd_uart.Init.StopBits = UART_STOPBITS_1;
  wifi_cmd_uart.Init.Parity = UART_PARITY_NONE;
  wifi_cmd_uart.Init.Mode = UART_MODE_TX_RX;
  wifi_cmd_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  wifi_cmd_uart.Init.OverSampling = UART_OVERSAMPLING_16;
  wifi_cmd_uart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  wifi_cmd_uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&wifi_cmd_uart) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE END UART5_Init 2 */
}

void console_init(void)
{
	 /* USER CODE BEGIN UART5_Init 2 */
	 console_uart.Instance = UART_CONSOLE;
	 console_uart.Init.BaudRate = 115200;
	 console_uart.Init.WordLength = UART_WORDLENGTH_8B;
	 console_uart.Init.StopBits = UART_STOPBITS_1;
	 console_uart.Init.Parity = UART_PARITY_NONE;
	 console_uart.Init.Mode = UART_MODE_TX_RX;
	 console_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	 console_uart.Init.OverSampling = UART_OVERSAMPLING_16;
	 console_uart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	 console_uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  if (HAL_UART_Init(&console_uart) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE END UART5_Init 2 */
}

int _write(int file, char *ptr, int len)
{
	HAL_StatusTypeDef ret = HAL_UART_Transmit(&console_uart , (uint8_t *)ptr, len , 100);
	UNUSED(ret);
	return ret;
}
static wifi_api_status uart_write(char *buffer)
{
	Wifi_Uart_t.WiFi_Tx_len = strlen(buffer);
	if(HAL_UART_Transmit(&wifi_cmd_uart, (uint8_t *)buffer, Wifi_Uart_t.WiFi_Tx_len, 1000) == HAL_OK)
		return MS_OK;
	else
		return MS_NOT_OK;
}
static wifi_api_status uart_byte_write(uint8_t *buf)
{
	if(HAL_UART_Transmit(&wifi_cmd_uart, (uint8_t *)buf, Wifi_Uart_t.WiFi_Tx_len, 1000) == HAL_OK)
			return MS_OK;
		else
			return MS_NOT_OK;
}
wifi_api_status wifi_mode(wifi_mode_config cnt)
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = malloc(sizeof(char) * 100);
	sprintf(Wifi_Uart_t.WiFi_Tx , WIFI_MODE_CMD , cnt);
	LucStatus = uart_write(Wifi_Uart_t.WiFi_Tx);
	free(Wifi_Uart_t.WiFi_Tx);
	return LucStatus;
}
wifi_api_status wifi_ap_connect(char *ssid , char *psk)
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = malloc(sizeof(char) * 100);
	sprintf(Wifi_Uart_t.WiFi_Tx , WIFI_CONNECT_AP_CMD , ssid , psk);
	LucStatus = uart_write(Wifi_Uart_t.WiFi_Tx);
	free(Wifi_Uart_t.WiFi_Tx);
	return LucStatus;
}
wifi_api_status wifi_rst()
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = WIFI_RST_CMD;
	LucStatus = uart_write(Wifi_Uart_t.WiFi_Tx);
	return LucStatus;
}
wifi_api_status wifi_version()
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = WIFI_GMR_CMD;
	LucStatus = uart_write(Wifi_Uart_t.WiFi_Tx);
	return LucStatus;
}
wifi_api_status wifi_comm_check()
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = WIFI_START_CMD;
	LucStatus = uart_write(Wifi_Uart_t.WiFi_Tx);
	return LucStatus;
}
wifi_api_status wifi_mac_add()
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = WIFI_MAC_CMD;
	LucStatus = uart_write(Wifi_Uart_t.WiFi_Tx);
	return LucStatus;
}
wifi_api_status tcp_server_conn(char *ipadress , char *port)
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = malloc(sizeof(char) * 100);
	sprintf(Wifi_Uart_t.WiFi_Tx , WIFI_CONNECT_AP_CMD , ipadress , port);
	LucStatus = uart_write(Wifi_Uart_t.WiFi_Tx);
	free(Wifi_Uart_t.WiFi_Tx);
	return LucStatus;
}
wifi_api_status wifi_send_fl_data(float buf[] , int len)
{
	wifi_api_status LucStatus = MS_NOT_OK;
	Wifi_Uart_t.WiFi_Tx = malloc(sizeof(char) * 100);
	sprintf (Wifi_Uart_t.WiFi_Tx, "AT+CIPSEND=%d\r\n", 4 * (1 + len));
	for(int j = 0; j < len; j++)
	{
		Wifi_Uart_t.fl_con_u8_pt.f = buf[j];
		Wifi_Uart_t.WiFi_Tx_len = 4;
		LucStatus = uart_byte_write(Wifi_Uart_t.fl_con_u8_pt.u);
	}
	return LucStatus;
}
/*
 * initialise the wifi - esp8266 via AT commands initialise the UART
 * initialise the command response handler
 */
void wifi_init()
{
	Wifi_UART_Init();

	Wifi_Uart_t.WiFi_Rx_len = 0;
	Wifi_Uart_t.WiFi_Tx_len = 0;
	memset(Wifi_Uart_t.WiFi_Rx , 0 , WIFI_RX_LEN);
	Wifi_Uart_t.log_buf = &console_buf_wr;
	Wifi_Uart_t.log_clr = &console_buf_clr;

	HAL_UART_Receive_IT(&wifi_cmd_uart, (uint8_t *)&tmp ,1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART_WIFI_CMD)
	{
		if(Wifi_Uart_t.WiFi_Rx_len < WIFI_RX_LEN && tmp != '\0')
		{
			Wifi_Uart_t.WiFi_Rx[Wifi_Uart_t.WiFi_Rx_len] = tmp;
			Wifi_Uart_t.WiFi_Rx_len++;
		}
		HAL_UART_Receive_IT(&wifi_cmd_uart, (uint8_t *)&tmp ,1);
	}
}
