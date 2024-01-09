#ifndef _SPIFFS_MANAGER_H_
#define _SPIFFS_MANAGER_H_

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include <stdarg.h>
#include "cJSON.h"
#include "GlobalInit.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief This function does global initialization for Spiffs, checks for save existence, and sends a signal if it exists
 * @param[in] GlobalInitInterfaceHandler pointer of GlobalInitHandeler for its content access
 */
void SpiffsGlobalConfig(GlobalInitInterfaceHandler_t *GlobalInitInterfaceHandler);

/**
 * @brief Read the contents of a file in the SPIFFS file system and store it in a buffer.
 * @param[in] addressInSpiffs The address of the file in SPIFFS.
 * @param[out] Buffer The buffer to store the file contents.
 * @param SizeOfBuffer The size of the buffer.
 */
void SpiffsRead(char *addressInSpiffs, char *Buffer, size_t SizeOfBuffer);

/**
 * @brief Write data to a new file or append to existing file
 * @param[in] addressInSpiffs File path
 * @param[out] data Data to write
 */
void SpiffsWrite(char *addressInSpiffs, char *data);

/**
 * @brief This function saves key-value pairs in a file in SPIFFS with a text format.
 * @param[in] filename The name of the file to save the key-value pairs.
 * @param[in] key key-var
 * @param[in] value value-var
 * @param[in] ... The variable arguments containing key-value pairs. The last argument must be NULL.
 * @return Returns true if the file is successfully saved, and false otherwise.
 */
void SpiffsWriteTxtFile(char *addressInSpiffs, char *key, char *value, ...);

/**
 * @brief This function reads key-value pairs from a file in SPIFFS with a text format.
 * @param[in] filename The name of the file to read the key-value pairs.
 * @param[in] key key-var
 * @param[out] value value-var
 * @param[out] ... The variable arguments to store the retrieved values. The last argument must be NULL.
 * @return Returns true if the file is successfully read and key-value pairs are retrieved, and false otherwise.
 */
void SpiffsReadTxtFile(char *addressInSpiffs, char *key, char *value, ...);

/**
 * @brief This function renames a file in SPIFFS.
 * @param[in] oldName The name of the file to be renamed.
 * @param[in] newName The new name for the file.
 * @return Returns true if the rename operation is successful, and false otherwise.
 */
void SpiffsRename(char *oldName, char *newName);

/**
 * @brief This function removes a file from SPIFFS.
 * @param[in] addressInSpiffs The address of the file to be removed.
 * @return Returns true if the file removal is successful, and false otherwise.
 */
bool SpiffsRemoveFile(char *addressInSpiffs);

/**
* @brief Searches for a file in the SPIFFS file system using the provided user-supplied address.
* This function takes an address from the user, performs a search in the SPIFFS file system,
* and attempts to locate a file with the specified address. If the file is found, the function
* returns true; otherwise, it returns false.
* @param[in] addressInSpiffs The address of the file in the SPIFFS.
* @return True if the file is found, false otherwise.
*/
bool SpiffsExistenceCheck(char *addressInSpiffs);

/**
 * @brief This function is a test scenario that demonstrates the usage of the SPIFFS and JSON-related functions.
 */
void SpiffsTest(void);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //_SPIFFS_MANAGER_H_