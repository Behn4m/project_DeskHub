idf_component_register(SRCS "CheckWeather.c"
                    INCLUDE_DIRS "."
                    REQUIRES driver esp_http_client json
                    )
