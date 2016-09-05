
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
	- dog_stateIface_dog_detected
	- dog_stateIface_get_time_secs
	- dog_stateIface_object_detected
	- dog_stateIface_on_sleep
	- dog_stateIface_on_play_no
	- dog_stateIface_is_done_playing_no
are defined.

These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
There are some constraints that have to be considered for the implementation of these functions:
	- never call the statechart API functions from within these functions.
	- make sure that the execution time is as short as possible.
 
*/
extern bool dog_stateIface_dog_detected(const Dog_state* handle);
extern uint32_t dog_stateIface_get_time_secs(const Dog_state* handle);
extern bool dog_stateIface_object_detected(const Dog_state* handle);
extern void dog_stateIface_on_sleep(const Dog_state* handle);
extern void dog_stateIface_on_play_no(const Dog_state* handle);
extern bool dog_stateIface_is_done_playing_no(const Dog_state* handle);





#ifdef __cplusplus
}
#endif 

#endif /* DOG_STATEREQUIRED_H_ */
