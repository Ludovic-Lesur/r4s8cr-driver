/*
 * r4s8cr.c
 *
 *  Created on: 28 nov. 2024
 *      Author: Ludo
 */

#include "r4s8cr.h"

#ifndef R4S8CR_DRIVER_DISABLE_FLAGS_FILE
#include "r4s8cr_driver_flags.h"
#endif
#include "r4s8cr_hw.h"
#include "types.h"

#ifndef R4S8CR_DRIVER_DISABLE

/*** R4S8CR local macros ***/

#define R4S8CR_UART_BAUD_RATE               9600

#define R4S8CR_ADDRESS_SIZE_BYTES           1
#define R4S8CR_RELAY_ADDRESS_SIZE_BYTES     1
#define R4S8CR_COMMAND_SIZE_BYTES           1

#define R4S8CR_NODE_ADDRESS                 0xFF

#define R4S8CR_COMMAND_READ                 0xA0
#define R4S8CR_COMMAND_OFF                  0x00
#define R4S8CR_COMMAND_ON                   0x01
#define R4S8CR_COMMAND_BUFFER_SIZE_BYTES    (R4S8CR_ADDRESS_SIZE_BYTES + R4S8CR_RELAY_ADDRESS_SIZE_BYTES + R4S8CR_COMMAND_SIZE_BYTES)

#define R4S8CR_REPLY_PARSING_DELAY_MS       10
#define R4S8CR_REPLY_TIMEOUT_MS             200
#define R4S8CR_REPLY_HEADER_SIZE            (R4S8CR_ADDRESS_SIZE_BYTES + R4S8CR_RELAY_ADDRESS_SIZE_BYTES)
#define R4S8CR_REPLY_SIZE_BYTES             (R4S8CR_REPLY_HEADER_SIZE + R4S8CR_NUMBER_OF_RELAYS)
#define R4S8CR_REPLY_BUFFER_SIZE_BYTES      64

/*** R4S8CR local structures ***/

/*******************************************************************/
typedef struct {
    volatile uint8_t reply[R4S8CR_REPLY_BUFFER_SIZE_BYTES];
    volatile uint8_t reply_size;
} R4S8CR_context_t;

/*** R4S8CR local global variables ***/

static R4S8CR_context_t r4s8cr_ctx;

/*** R4S8CR local functions ***/

/*******************************************************************/
static void _R4S8CR_rx_irq_callback(uint8_t data) {
    // Store incoming byte.
    r4s8cr_ctx.reply[r4s8cr_ctx.reply_size] = data;
    // Manage index.
    r4s8cr_ctx.reply_size = (uint8_t) ((r4s8cr_ctx.reply_size + 1) % R4S8CR_REPLY_BUFFER_SIZE_BYTES);
}

/*******************************************************************/
static void _R4S8CR_flush_buffer(void) {
    // Local variables.
    uint8_t idx = 0;
    // Flush buffer.
    for (idx = 0; idx < R4S8CR_REPLY_BUFFER_SIZE_BYTES; idx++) {
        r4s8cr_ctx.reply[idx] = 0x00;
    }
    r4s8cr_ctx.reply_size = 0;
}

/*** R4S8CR functions ***/

/*******************************************************************/
R4S8CR_status_t R4S8CR_init(void) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    R4S8CR_HW_configuration_t hw_config;
    // Init context.
    _R4S8CR_flush_buffer();
    // Init hardware interface.
    hw_config.uart_baud_rate = R4S8CR_UART_BAUD_RATE;
    hw_config.rx_irq_callback = &_R4S8CR_rx_irq_callback;
    status = R4S8CR_HW_init(&hw_config);
    if (status != R4S8CR_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
R4S8CR_status_t R4S8CR_de_init(void) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    // Release hardware interface.
    status = R4S8CR_HW_de_init();
    if (status != R4S8CR_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
R4S8CR_status_t R4S8CR_write(uint8_t relay_box_id, uint8_t relay_index, uint8_t state) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    uint8_t command[R4S8CR_COMMAND_BUFFER_SIZE_BYTES];
    // Check parameters.
    if ((relay_box_id < R4S8CR_RELAY_BOX_ID_MIN) || (relay_box_id > R4S8CR_RELAY_BOX_ID_MAX)) {
        status = R4S8CR_ERROR_RELAY_BOX_ID;
        goto errors;
    }
    if (relay_index > R4S8CR_RELAY_INDEX_MAX) {
        status = R4S8CR_ERROR_RELAY_INDEX;
        goto errors;
    }
    // Build command.
    command[0] = R4S8CR_NODE_ADDRESS;
    command[1] = (relay_box_id * relay_index);
    command[2] = (state == 0) ? R4S8CR_COMMAND_OFF : R4S8CR_COMMAND_ON;
    // Send command.
    status = R4S8CR_HW_write(command, R4S8CR_COMMAND_BUFFER_SIZE_BYTES);
    if (status != R4S8CR_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
R4S8CR_status_t R4S8CR_read(uint8_t relay_box_id, uint8_t* state) {
    // Local variables.
    R4S8CR_status_t status = R4S8CR_SUCCESS;
    uint8_t command[R4S8CR_COMMAND_BUFFER_SIZE_BYTES];
    uint32_t reply_time_ms = 0;
    uint8_t idx = 0;
    // Check parameters.
    if (state == NULL) {
        status = R4S8CR_ERROR_NULL_PARAMETER;
        goto errors;
    }
    if ((relay_box_id < R4S8CR_RELAY_BOX_ID_MIN) || (relay_box_id > R4S8CR_RELAY_BOX_ID_MAX)) {
        status = R4S8CR_ERROR_RELAY_BOX_ID;
        goto errors;
    }
    // Flush buffers and state.
    _R4S8CR_flush_buffer();
    (*state) = 0;
    // Build command.
    command[0] = R4S8CR_NODE_ADDRESS;
    command[1] = (R4S8CR_COMMAND_READ | relay_box_id);
    command[2] = 0x00;
    // Send command.
    status = R4S8CR_HW_write(command, R4S8CR_COMMAND_BUFFER_SIZE_BYTES);
    if (status != R4S8CR_SUCCESS) goto errors;
    // Enable receiver.
    status = R4S8CR_HW_enable_rx();
    if (status != R4S8CR_SUCCESS) goto errors;
    // Wait reply.
    while (1) {
        // Delay.
        status = R4S8CR_HW_delay_milliseconds(R4S8CR_REPLY_PARSING_DELAY_MS);
        if (status != R4S8CR_SUCCESS) goto errors;
        // Update loop time.
        reply_time_ms += R4S8CR_REPLY_PARSING_DELAY_MS;
        // Check number of received bytes.
        if (r4s8cr_ctx.reply_size >= R4S8CR_REPLY_SIZE_BYTES) {
            // Relays loop.
            for (idx = 0; idx < R4S8CR_NUMBER_OF_RELAYS; idx++) {
                // Get relay state.
                if (r4s8cr_ctx.reply[R4S8CR_REPLY_HEADER_SIZE + idx] != 0) {
                    (*state) |= (0b1 << idx);
                }
            }
            break;
        }
        // Exit if timeout.
        if (reply_time_ms > R4S8CR_REPLY_TIMEOUT_MS) {
            // Set status to timeout.
            status = R4S8CR_ERROR_READ_TIMEOUT;
            goto errors;
        }
    }
errors:
    R4S8CR_HW_disable_rx();
    return status;
}

#endif /* R4S8CR_DRIVER_DISABLE */
