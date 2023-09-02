#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "lvgl.h"
#include "rm67162.h"
#include "wifi.h"
#include "CheckWeather.h"

// To Do: ask user through console to provide SSID and Password
char *pass = WIFI_PASSWORD; 
char *ssid = WIFI_SSID;

/* https://weatherstack.com/documentation */
static char *API_KEY_weatherstack = "bb60cad0bc94e772f2d2615ecfaeeb46";
static char *CITY = "Montreal";
static char *URL_weatherstack = "http://api.weatherstack.com/current";

void app_main(void)
{
    rm67162_init();
    lv_init();

    nvs_flash_init();
    configure_wifi(ssid, pass);
    connect_wifi();

    vTaskDelay(3000 / portTICK_PERIOD_MS);

    CheckWeather(CITY, URL_weatherstack, API_KEY_weatherstack);

    lcd_fill(100, 100, 536, 240, 0x1221);
}
