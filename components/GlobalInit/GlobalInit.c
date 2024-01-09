#include "GlobalInit.h"

static const char *TAG = "GlobalInit";

/**
 * in this function we init hardware or variable that need them
 *  globally
 */
bool GlobalInit(GlobalInitInterfaceHandler_t *InterfaceHandler)
{        
    if (
    #ifdef SpotifyEnable        
        InterfaceHandler->HttpsBufQueue != NULL &&
        InterfaceHandler->HttpsResponseReadySemaphore != NULL &&
        InterfaceHandler->IsSpotifyAuthorizedSemaphore != NULL &&
        InterfaceHandler->WorkWithStorageInSpotifyComponentSemaphore != NULL &&
    #endif        
        InterfaceHandler->FinishWifiConfig != NULL &&
        InterfaceHandler->WifiParamExistenceCheckerSemaphore != NULL)
    {     
    #ifdef SpotifyEnable        
        InterfaceHandler->HttpsBufQueue = xQueueCreate(1, sizeof(char) * sizeof(char[2500]));
        InterfaceHandler->HttpsResponseReadySemaphore = xSemaphoreCreateBinary();
        InterfaceHandler->IsSpotifyAuthorizedSemaphore = xSemaphoreCreateBinary();
        InterfaceHandler->WorkWithStorageInSpotifyComponentSemaphore = xSemaphoreCreateBinary();
    #endif        
        InterfaceHandler->FinishWifiConfig = xSemaphoreCreateBinary();
        InterfaceHandler->WifiParamExistenceCheckerSemaphore = xSemaphoreCreateBinary();        

        ESP_LOGI(TAG, "GlobalInit initiated successfully");        
        return true;
    }    
    else
    {
        ESP_LOGE(TAG, "GlobalInit is missing some pointers, can not run the app");
        return false;
    }
    
    // ESP-Matter core create default event loop.
    // so we dont need to create it here.
    
    // ESP_LOGI(TAG, "Eventloop create");
    // ESP_ERROR_CHECK(esp_event_loop_create_default());
}