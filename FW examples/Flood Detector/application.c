/*
*   Example code for Wi-Fi module for BigClown: Flood Detector
*   Flood detector indicates water on your floor about washing machine, dishwasher or somewhere else.
*   The detector LD-81 is directly connected to P7 GPIO.
*   
*   CONNECTION: LD-81 detector Black wire - GND, Red wire to P7, Resistor 4k7 from VCC to P7, cut other wires.
*
*   If Flood detector detects water, the warning value (it means number 1) is sent to TMEP.cz/TMEP.eu. Otherwise
*   Wi-Fi module sends number 0 every hour - it means, no water, still alive. 
*
*   NOTE: In this example, you don't need to buy Sensor module by BigClown and Core module with Radio (you have Wi-Fi module).
*
*   What you need: 
*   Core module without Radio https://shop.bigclown.com/core-module-nr/
*   Flood detector: https://shop.bigclown.com/3d-printed-enclosure-501/
*   Mini baterry module: https://shop.bigclown.com/mini-battery-module/
*   3D printed enclosure: https://shop.bigclown.com/3d-printed-enclosure-501/
*   and Wi-Fi module v1.1 
*
*   FW code was written by chiptron.cz (2019)
*   ESP8266 library created by Martin Grames (cryptoclock example: https://github.com/bigclownprojects/bcf-wifi-cryptoclock)
*/

#include <application.h>

#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "password"
#define HTTP_HOST "HOSTNAME.tmep.cz" //or HOSTNAME.tmep.eu
#define HTTP_PATH "/index.php?"
#define REFRESH_DATA_INTERVAL (60 * 60 * 1000) // check every hour

// LED instance
bc_led_t led;

// WiFi module instance
bc_esp8266_t esp8266;

// floorDetector instance (GPIO P7)
bc_button_t floorDetector;

uint8_t u8_contact = 0; // no water

void floorDetector_event_handler(bc_button_t *self, bc_button_event_t event, void *event_param)
{
    if (event == BC_BUTTON_EVENT_PRESS)
    {
        bc_esp8266_connect(&esp8266);
        bc_scheduler_plan_current_relative(REFRESH_DATA_INTERVAL);
        u8_contact = 1; // the presence of water
    }
}

void esp8266_event_handler(bc_esp8266_t *self, bc_esp8266_event_t event, void *event_param)
{
    if (event == BC_ESP8266_EVENT_WIFI_CONNECT_SUCCESS)
    {
        bc_led_pulse(&led, 500);

        bc_esp8266_tcp_connect(&esp8266, HTTP_HOST, 80);
    }
    else if (event == BC_ESP8266_EVENT_SOCKET_CONNECT_SUCCESS)
    {
        char data[100];
        sprintf(data,
            "GET %scontact=%d HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n\r\n",
            HTTP_PATH, u8_contact, HTTP_HOST);

        bc_esp8266_send_data(&esp8266, data, strlen(data));
    }
    
    else if (event == BC_ESP8266_EVENT_DATA_RECEIVED)
    {
        bc_esp8266_disconnect(&esp8266);
        u8_contact = 0;
    }
}

static void refresh_data_event_handler(void *param)
{
    bc_esp8266_connect(&esp8266);

    bc_scheduler_plan_current_relative(REFRESH_DATA_INTERVAL);
}

void application_init()
{
    // Initialize LED
    bc_led_init(&led, BC_GPIO_LED, false, false);

    // Initialize floorDetector (GPIO P7)
    bc_button_init(&floorDetector, BC_GPIO_P7, BC_GPIO_PULL_DOWN, false);
    bc_button_set_event_handler(&floorDetector, floorDetector_event_handler, NULL);

    // Initialize WiFi module
    bc_esp8266_init(&esp8266, BC_UART_UART0);
    bc_esp8266_set_event_handler(&esp8266, esp8266_event_handler, NULL);
    bc_esp8266_set_station_mode(&esp8266, WIFI_SSID, WIFI_PASSWORD);

    bc_scheduler_register(refresh_data_event_handler, NULL, 100);

}

void application_task(void)
{

}
