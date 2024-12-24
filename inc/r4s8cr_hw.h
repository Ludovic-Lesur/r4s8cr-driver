/*
 * r4s8cr_hw.h
 *
 *  Created on: 28 nov. 2024
 *      Author: Ludo
 */

#ifndef __R4S8CR_HW_H__
#define __R4S8CR_HW_H__

#ifndef R4S8CR_DRIVER_DISABLE_FLAGS_FILE
#include "r4s8cr_driver_flags.h"
#endif
#include "r4s8cr.h"
#include "types.h"

#ifndef R4S8CR_DRIVER_DISABLE

/*** R4S8CR HW structures ***/

/*!******************************************************************
 * \fn R4S8CR_HW_rx_irq_cb_t
 * \brief Byte reception interrupt callback.
 *******************************************************************/
typedef void (*R4S8CR_HW_rx_irq_cb_t)(uint8_t data);

/*!******************************************************************
 * \struct R4S8CR_HW_configuration_t
 * \brief R4S8CR hardware interface parameters.
 *******************************************************************/
typedef struct {
    uint32_t uart_baud_rate;
    R4S8CR_HW_rx_irq_cb_t rx_irq_callback;
} R4S8CR_HW_configuration_t;

/*** R4S8CR HW functions ***/

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_HW_init(R4S8CR_HW_configuration_t* configuration)
 * \brief Init R4S8CR hardware interface.
 * \param[in]   configuration: Pointer to the hardware interface parameters structure.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_HW_init(R4S8CR_HW_configuration_t* configuration);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_HW_de_init(void)
 * \brief Release R4S8CR hardware interface.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_HW_de_init(void);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_HW_enable_rx(void)
 * \brief Enable bus reception.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_HW_enable_rx(void);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_HW_disable_rx(void)
 * \brief Disable bus reception.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_HW_disable_rx(void);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_HW_write(uint8_t* data, uint32_t data_size_bytes)
 * \brief Write data on RS485 bus.
 * \param[in]   data: Byte array to send.
 * \param[in]   data_size_bytes: Number of bytes to send.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_HW_write(uint8_t* data, uint32_t data_size_bytes);

/*!******************************************************************
 * \fn R4S8CR_status_t R4S8CR_HW_delay_milliseconds(uint32_t delay_ms)
 * \brief Delay function.
 * \param[in]   delay_ms: Delay to wait in ms.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
R4S8CR_status_t R4S8CR_HW_delay_milliseconds(uint32_t delay_ms);

#endif /* R4S8CR_DRIVER_DISABLE */

#endif /* __R4S8CR_HW_H__ */
