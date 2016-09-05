
#ifndef DOG_STATE_H_
#define DOG_STATE_H_

#include "../src/sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'dog_state'.
*/

/*! Enumeration of all states */ 
typedef enum
{
	Dog_state_main_region_no_dog,
	Dog_state_main_region_no_dog_r1_sleeping,
	Dog_state_main_region_no_dog_r1_reading_range,
	Dog_state_main_region_dog,
	Dog_state_main_region_dog_r1_playing_no,
	Dog_state_main_region_dog_r1_reading_range,
	Dog_state_last_state
} Dog_stateStates;

/*! Type definition of the data structure for the Dog_stateInternal interface scope. */
typedef struct
{
	uint16_t last_detection_time_millis;
	uint16_t last_no_time_millis;
} Dog_stateInternal;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define DOG_STATE_MAX_ORTHOGONAL_STATES 1

/*! 
 * Type definition of the data structure for the Dog_state state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	Dog_stateStates stateConfVector[DOG_STATE_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	Dog_stateInternal internal;
} Dog_state;

/*! Initializes the Dog_state state machine data structures. Must be called before first usage.*/
extern void dog_state_init(Dog_state* handle);

/*! Activates the state machine */
extern void dog_state_enter(Dog_state* handle);

/*! Deactivates the state machine */
extern void dog_state_exit(Dog_state* handle);

/*! Performs a 'run to completion' step. */
extern void dog_state_runCycle(Dog_state* handle);



/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean dog_state_isActive(const Dog_state* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean dog_state_isFinal(const Dog_state* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean dog_state_isStateActive(const Dog_state* handle, Dog_stateStates state);

#ifdef __cplusplus
}
#endif 

#endif /* DOG_STATE_H_ */
