/*
 * r4s8cr.h
 *
 *  Created on: 28 nov. 2024
 *      Author: Ludo
 */

#ifndef __R4S8CR_H__
#define __R4S8CR_H__

#ifndef R4S8CR_DRIVER_DISABLE_FLAGS_FILE
#include "r4s8cr_driver_flags.h"
#endif
#include "error.h"
#include "types.h"

/*** R4S8CR macros ***/

#define R4S8CR_RELAY_BOX_ID_MIN     1
#define R4S8CR_RELAY_BOX_ID_MAX     15

#define R4S8CR_RELAY_INDEX_MIN      1
#define R4S8CR_RELAY_INDEX_MAX      8

#define R4S8CR_NUMBER_OF_RELAYS     (R4S8CR_RELAY_INDEX_MAX - R4S8CR_RELAY_INDEX_MIN + 1)

/*** R4S8CR structures ***/

/*!******************************************************************
 * \enum R4S8CR_status_t
 * \brief R4S8CR driver error codes.
 *******************************************************************/
typedef enum {
    // Driver errors.
    R4S8CR_SUCCESS = 0,
    R4S8CR_ERROR_NULL_PARAMETER,
    R4S8CR_ERROR_RELAY_BOX_ID,
    R4S8CR_ERROR_RELAY_INDEX,
    R4S8CR_ERROR_READ_TIMEOUT,
    // Low level drivers errors.
    R4S8CR_ERROR_BASE_RS485 = ERROR_BASE_STEP,
    R4S8CR_ERROR_BASE_DELAY = (R4S8CR_ERROR_BASE_RS485 + R4S8CR_DRIVER_RS485_ERROR_BASE_LAST),
    // Last base value.
    R4S8CR_ERROR_BASE_LAST = (R4S8CR_ERROR_BASE_DELAY + R4S8CR_DRIVER_DELAY_ERROR_BASE_LAST),
} R4S8CR_status_t;

#ifndef R4S8CR_DRIVER_DISABLE

/*** R4S8CR functions ***/

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_init(void)
 * \brief Init relay box driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_init(void);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_de_init(void)
 * \brief Release relay box driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_de_init(void);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_write(uint8_t relay_box_id, uint8_t relay_index, uint8_t state)
 * \brief Set relay state.
 * \param[in]   relay_box_id: Relay box ID (1 to 15 according to DIP switches configuration).
 * \param[in]   relay_index: Relay to control (1 to 8).
 * \param[in]   state: Open the relay if 0, close it otherwise.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_write(uint8_t relay_box_id, uint8_t relay_index, uint8_t state);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_read(uint8_t relay_box_id, uint8_t* state)
 * \brief Read all relays state.
 * \param[in]   relay_box_id: Relay box ID (1 to 15 according to DIP switches configuration).
 * \param[out]  state: Relays state defined as a bitfield (bit x indicates relay x state).
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_read(uint8_t relay_box_id, uint8_t* state);

/*******************************************************************/
#define R4S8CR_exit_error(base) { ERROR_check_exit(r4s8cr_status, R4S8CR_SUCCESS, base) }

/*******************************************************************/
#define R4S8CR_stack_error(base) { ERROR_check_stack(r4s8cr_status, R4S8CR_SUCCESS, base) }

/*******************************************************************/
#define R4S8CR_stack_exit_error(base, code) { ERROR_check_stack_exit(r4s8cr_status, R4S8CR_SUCCESS, base, code) }

#endif /* R4S8CR_DRIVER_DISABLE */

#endif /* __R4S8CR_H__ */
