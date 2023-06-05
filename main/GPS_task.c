/*
GPS NMEA data decoding with ESP32.
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

#include "gps_nmea.h"

static const int RX_BUF_SIZE = 1024;

// NEO-6M pins connected on RX2 and TX2 of ESP board
#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)


void gps_init (void)
{
    //Initial UART config setting baud rate, data bits, stop bits, etc.
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB
    };

    uart_driver_install (UART_NUM_2, RX_BUF_SIZE*2,0,0,NULL,0);
    uart_param_config (UART_NUM_2, &uart_config);
    uart_set_pin (UART_NUM_2, TXD_PIN,RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

}

//Task to recieve data from GPS module and parse the NMEA packets.
static void receive_data (void *arg) 
{
    uint8_t* data = (uint8_t*) malloc (RX_BUF_SIZE+1); //Data buffer
    GPS myData; //Struct containing UTC, Lat, Long data.

    while (1)
    {
        //Read data received by the UART and saved in the Rx FIFO buffer
        const int rxbytes = uart_read_bytes(UART_NUM_2, data, RX_BUF_SIZE, 1000/portTICK_PERIOD_MS); 
        if (rxbytes)
        {
            data[rxbytes] = '\0';
            
            parse_gps_data ((char*) data, &myData); //Parse data buffer and decode the GGA string.
            printf("\r\nTime: %f\nLat: %f %c\nLon: %f %c\nAlt: %f m\nSatellites: %d\nHDOP: %f\r\n",myData.utc_time, myData.nmea_latitude/100, myData.ns, myData.nmea_longitude/100, myData.ew, myData.msl_altitude, myData.sattelites, myData.hdop);
        }
               
            //printf ("Recv data: %s", (char *) data);   

    vTaskDelay (100/portTICK_PERIOD_MS); // Block for 100ms.
    }

    free (data);

}

void app_main(void)
{
    gps_init ();
    xTaskCreate(receive_data, "uart_receive_data", 1024*2, NULL, configMAX_PRIORITIES, NULL);

}
