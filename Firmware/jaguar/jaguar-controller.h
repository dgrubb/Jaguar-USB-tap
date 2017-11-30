/*
 * File: jaguar-controller.h
 * Author: dgrubb
 * Date: 30/11/2017
 *
 * Interpret digital I/O in context of Jaguar controller.
 */

#ifndef _JAGUAR_CONTROLLER_H
#define _JAGUAR_CONTROLLER_H

#include <stdint.h>

void jaguar_update_inputs();
void jaguar_get_pending_transition();


#endif /* _JAGUAR_CONTROLLER_H */

