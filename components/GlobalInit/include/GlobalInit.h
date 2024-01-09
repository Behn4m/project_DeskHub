#ifndef GLOBAL_INIT_H_
#define GLOBAL_INIT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <esp_log.h>
#include <esp_system.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

// **************************************************************** applicaiton configurations
#define SpotifyEnable
#define WIFI_INIT_STA_MODE

// spiffs directories
#define WifiConfigDirectoryAddressInSpiffs  "/spiffs/WifiConfig.txt"
#define SpotifyConfigAddressInSpiffs "/spiffs/SpotifyConfig.txt"

// **************************************************************** constant macros
#define SEC 1000
#define HOUR 3600
#define LONG_BUF 2500
#define MEDIUM_BUF 1000
#define SMALL_BUF   250
#define SPOTIFY_TASK_STACK_SIZE (uint16_t)(10*1000U)
#define HttpsTaskStackSize   (uint16_t)(9*1000U)
#define WifiModuleTaskStackSize   (uint16_t)(10*1000U)

typedef struct
{
#ifdef SpotifyEnable        
    QueueHandle_t *HttpsBufQueue;
    SemaphoreHandle_t *HttpsResponseReadySemaphore;
    SemaphoreHandle_t *IsSpotifyAuthorizedSemaphore;
    SemaphoreHandle_t *WorkWithStorageInSpotifyComponentSemaphore;
#endif    
    SemaphoreHandle_t *WifiParamExistenceCheckerSemaphore;
    SemaphoreHandle_t *FinishWifiConfig;  
} GlobalInitInterfaceHandler_t;

#ifdef SpotifyEnable
/**
 * timeout definition part 
*/
#define SPOTIFY_RESPONSE_TIMEOUT (30*1000)/portTICK_PERIOD_MS
#endif

// **************************************************************** initilization functions
/**
 * in this function we init hardware or variable that need them
 *  globally
 */

bool GlobalInit(GlobalInitInterfaceHandler_t *GlobalInitInterfaceHandler);

#ifdef __cplusplus
}//extern "C"
#endif

#endif//GLOBAL_INIT_H_