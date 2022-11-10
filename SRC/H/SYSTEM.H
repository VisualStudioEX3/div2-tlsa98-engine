//! SYSTEM.DLL - System library for DIV Games Studio 2.
//! @copyright TLSA98 Engine (C) VisualStudioEX3, José Miguel Sánchez Fernández - 2022
//! @copyright DIV Games Studio 2 (C) Hammer Technologies, Daniel Navarro Medrano - 1998, 1999
/*!
    Engine base members and service provider.
*/

#ifndef __SYSTEM_DLL_
#define __SYSTEM_DLL_

#define GLOBALS                 // Required by DIV.H (before incluide it).
#include "DIV.H"                // DIV Games Studio 2 API header.

/// @brief True constant value.
/// @remarks In DIV Games Studio, all odd values are considered as true value.
#define true                                        1

/// @brief False constant value.
/// @remarks In DIV Games Studio, all even values are considered as false value.
#define false                                       0

/// @brief Default function success result.
#define RESULT_OK                                   0

/// @brief Default function error result.
#define RESULT_ERROR                                -1

/// @brief A service is already registered with the used id.
#define RESULT_ERROR_SERVICE_ALREADY_REGISTERED     1000

/// @brief Service container is full.
#define RESULT_ERROR_SERVICE_CONTAINER_IS_FULL      1001

/// @brief BYTE type in DIV Games Studio 2.
typedef unsigned char byte;

/// @brief WORD type in DIV Games Studio 2.
typedef unsigned short word;

/// @brief STRING type in DIV Games Studio 2.
/// @remarks An alias for char pointer type.
typedef char* string;

/// @brief Boolean alias.
/// @remarks In DIV Games Studio, like in C, a boolean value is an integer value.
typedef int bool;

/// @brief Service id.
typedef int service_id_t;

/// @brief DIV getparm() overload to get a DIV2 STRING parameter.
#define getstrparm()    (string)&mem[text_offset + getparm()]

/// @brief malloc() alias to DIV implementation.
#define malloc(size)    div_malloc(size)

/// @brief free() alias to DIV implementation.
#define free(ptr)       div_free(ptr)

/// @brief Gets the size of an array.
/// @param a Array to measure.
/// @return Returns the array size.
#define arraylen(a)     sizeof(a) / sizeof(a[0])

/// @brief Registers a new service.
/// @param id Unique id used to identify the service.
/// @param service Pointer to the service.
/// @return Returns #RESULT_ERROR_SERVICE_ALREADY_REGISTERED if a service is already 
/// registered with this id, #RESULT_ERROR_SERVICE_CONTAINER_IS_FULL if the service 
/// container is full, #RESULT_OK otherwise.
int registerService(service_id_t id, const void* service);

/// @brief Gets the service instance.
/// @param id The service id.
/// @return Returns the pointer to the service, #DIV::NULL if the id is not found. 
const void* getService(service_id_t id);

/// @brief Gets the number of registered services.
/// @return Returns the number of registered services in the container. 
int getServiceProviderCount();

/// @brief Gets the max number of services that service provider can register.
/// @return Returns the capacity of the service provider.
int getServiceProviderCapacity();

#endif
