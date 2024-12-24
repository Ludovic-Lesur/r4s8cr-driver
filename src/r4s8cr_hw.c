/*
 * r4s8cr_hw.c
 *
 *  Created on: 28 nov. 2024
 *      Author: Ludo
 */

#include "r4s8cr_hw.h"

#ifndef R4S8CR_DRIVER_DISABLE_FLAGS_FILE
#include "r4s8cr_driver_flags.h"
#endif
#include "r4s8cr.h"
#include "types.h"

#ifndef R4S8CR_DRIVER_DISABLE

/*** R4S8CR HW functions ***/

/*******************************************************************/
R4S8CR_status_t __attribute__((weak)) R4S8CR_HW_init(R4S8CR_HW_configuration_t* configuration) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    /* To be implemented */
    UNUSED(configuration);
    return status;
}

/*******************************************************************/
R4S8CR_status_t __attribute__((weak)) R4S8CR_HW_de_init(void) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    /* To be implemented */
    return status;
}

/*******************************************************************/
R4S8CR_status_t __attribute__((weak)) R4S8CR_HW_enable_rx(void) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    /* To be implemented */
    return status;
}

/*******************************************************************/
R4S8CR_status_t __attribute__((weak)) R4S8CR_HW_disable_rx(void) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    /* To be implemented */
    return status;
}

/*******************************************************************/
R4S8CR_status_t __attribute__((weak)) R4S8CR_HW_write(uint8_t* data, uint32_t data_size_bytes) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    /* To be implemented */
    UNUSED(data);
    UNUSED(data_size_bytes);
    return status;
}

/*******************************************************************/
R4S8CR_status_t __attribute__((weak)) R4S8CR_HW_delay_milliseconds(uint32_t delay_ms) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    /* To be implemented */
    UNUSED(delay_ms);
    return status;
}

#endif /* R4S8CR_DRIVER_DISABLE */
