#include "CheckWeather.h"

char *response_data = NULL;
size_t response_len = 0;
bool all_chunks_received = false;

weather_t weather;

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            response_data = realloc(response_data, response_len + evt->data_len);
            memcpy(response_data + response_len, evt->data, evt->data_len);
            response_len += evt->data_len;
            break;
        case HTTP_EVENT_ON_FINISH:
            all_chunks_received = true;
            get_temp_pressure_humidity(response_data);
            break;
        default:
            break;
        free(response_data);
    }
    return ESP_OK;
}

void CheckWeather(char *city, char *url, char *api_key)
{
    char weather_request[200];
    snprintf(weather_request,
             sizeof(weather_request),
             "%s?access_key=%s&query=%s",
             url, api_key,city);
    esp_http_client_config_t config = {
        .url = weather_request,
        .method = HTTP_METHOD_GET,
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) 
    {

    } 
    else 
    {
        
    }
    
}

void get_temp_pressure_humidity(const char *json_string)
{   
    cJSON *root = cJSON_Parse(json_string);
    cJSON *current = cJSON_GetObjectItemCaseSensitive(root, "current");
    
    weather.temperature = cJSON_GetObjectItemCaseSensitive(current, "temperature")->valuedouble;
    weather.pressure = cJSON_GetObjectItemCaseSensitive(current, "pressure")->valueint;
    weather.humidity = cJSON_GetObjectItemCaseSensitive(current, "humidity")->valueint;
    printf("Temperature: %d°C\nPressure: %d hPa\nHumidity: %d%%\n", weather.temperature, weather.pressure, weather.humidity);

    weather.feelslike = cJSON_GetObjectItemCaseSensitive(current, "feelslike")->valuedouble;
    weather.wind_speed = cJSON_GetObjectItemCaseSensitive(current, "wind_speed")->valuedouble;
    weather.wind_degree = cJSON_GetObjectItemCaseSensitive(current, "wind_degree")->valuedouble;
    printf("feelslike: %d°C\nWind Speed: %d Kmph\nWind Direction %d°\n", weather.feelslike, weather.wind_speed, weather.wind_degree);

    cJSON_Delete(root);
}