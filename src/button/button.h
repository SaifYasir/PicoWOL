#pragma once

#include <stdint.h>

#include "configuration.h"

/**
 * \file button.h
 * \brief Functions to initialise and set interrupts for buttons using variables set in \ref configuration.h
 * 
 * This file will also use variables \ref default_selected_wol_profile and \ref default_wol_profiles 
 * to search through WOL profiles and select the current wol displayed. Variable \ref default_udp_polling_machine_stack
 * is also used to add to this stack so machines can be awoken when this stack is polled.
*/


/**
 * \brief Initialises the left button using \ref LEFT_BTN_GPIO to decrement \ref default_selected_wol_profile 
 * and then display the selected wol profile (\ref default_selected_wol_profile being an index to \ref default_wol_profiles) 
 */
void initialise_left_btn();
/**
 * \brief Initialises the right button using \ref RIGHT_BTN_GPIO to decrement \ref default_selected_wol_profile 
 * and then display the selected wol profile (\ref default_selected_wol_profile being an index to \ref default_wol_profiles) 
 */
void initialise_right_btn();
/**
 * \brief Initialises the accept button using \ref ACCEPT_BTN_GPIO to select the current profile (using \ref default_selected_wol_profile 
 * as an index to \ref default_wol_profiles) and added to the stack \ref default_udp_polling_machine_stack (so when polled the machine can be awoken)
 */
void initialise_accept_btn();
/**
 * \brief Initialises the info button using \ref INFO_BTN_GPIO to display WIFI information about the pico,
 * Being the local IP address and the port number used for UDP packets
 */
void initialise_info_btn();

/**
 * \brief Disables all currently currently enabled buttons
 */
void disable_all_buttons();

/**
 * \brief Renables all currently displayed buttons via \ref disable_all_buttons
 * 
 */
void reenable_all_buttons();

/**
 * \brief Initialises all buttons defined via:
 * 
 * - \ref initialise_left_btn
 * - \ref initialise_right_btn
 * - \ref initialise_accept_btn
 * - \ref initialise_info_btn
 */
void initialise_all_buttons();
