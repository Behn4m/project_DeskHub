#pragma once

#include "esp_http_client.h"
#include "cJSON.h"

typedef struct weather_t{
    int     temperature;
    int     humidity;
    int     pressure;
    char    weather_code;
    int     wind_speed;
    int     wind_degree;
    int     cloudcover;
    int     feelslike;
    int     uv_index;
    int     visibility;
    char    is_day;
}weather_t;

esp_err_t _http_event_handler(esp_http_client_event_t *evt);
void CheckWeather(char *city, char *url, char *api_key);
void get_temp_pressure_humidity(const char *json_string);
