
#ifndef DOG_STATEREQUIRED_H_
#define DOG_STATEREQUIRED_H_

#include "../src/sc_types.h"
#include "Dog_state.h"

#ifdef __cplusplus
extern "C"
{
#endif 

/*! \file This header defines prototypes for all functions that are required by the state machine implementation.

This state machine makes use of operations declared in the state machines interface or internal scopes. Thus the function prototypes:
	- dog_stateIfaceDog_dog_detected
	- dog_stateIfaceDog_on_play_no
	- dog_stateIfaceDog_is_done_playing_no
	- dog_stateIfaceMCU_on_init
	- dog_stateIfaceMCU_on_sleep
	- dog_stateIfaceTOF_on_init
	- dog_stateIfaceTOF_object_detected
	- dog_stateIfaceTOF_is_sensor_reset
	- dog_stateIfaceTOF_did_write_default_settings
	- dog_stateIfaceTOF_did_write_application_settings
	- dog_stateIfaceTOF_is_sensor_ready
	- dog_stateIfaceTOF_get_range_status
	- dog_stateIfaceTOF_on_reset_range_status
	- dog_stateIfaceTOF_on_handle_error
	- dog_stateIfaceTOF_on_config_start
	- dog_stateIfaceTOF_on_config_complete
	- dog_stateIfaceTOF_on_start
are defined.

These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
There are some constraints that have to be considered for the implementation of these functions:
	- never call the statechart API functions from within these functions.
	- make sure that the execution time is as short as possible.
 
*/
extern bool dog_stateIfaceDog_dog_detected(const Dog_state* handle);
extern void dog_stateIfaceDog_on_play_no(const Dog_state* handle);
extern bool dog_stateIfaceDog_is_done_playing_no(const Dog_state* handle);

extern void dog_stateIfaceMCU_on_init(const Dog_state* handle);
extern void dog_stateIfaceMCU_on_sleep(const Dog_state* handle);

extern void dog_stateIfaceTOF_on_init(const Dog_state* handle);
extern bool dog_stateIfaceTOF_object_detected(const Dog_state* handle);
extern bool dog_stateIfaceTOF_is_sensor_reset(const Dog_state* handle);
extern bool dog_stateIfaceTOF_did_write_default_settings(const Dog_state* handle);
extern bool dog_stateIfaceTOF_did_write_application_settings(const Dog_state* handle);
extern bool dog_stateIfaceTOF_is_sensor_ready(const Dog_state* handle);
extern uint8_t dog_stateIfaceTOF_get_range_status(const Dog_state* handle);
extern void dog_stateIfaceTOF_on_reset_range_status(const Dog_state* handle);
extern void dog_stateIfaceTOF_on_handle_error(const Dog_state* handle, const uint8_t error);
extern void dog_stateIfaceTOF_on_config_start(const Dog_state* handle);
extern void dog_stateIfaceTOF_on_config_complete(const Dog_state* handle);
extern void dog_stateIfaceTOF_on_start(const Dog_state* handle);





#ifdef __cplusplus
}
#endif 

#endif /* DOG_STATEREQUIRED_H_ */
