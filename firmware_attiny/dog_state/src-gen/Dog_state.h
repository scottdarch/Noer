
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
	Dog_state_firmware_running,
	Dog_state_firmware_running_MCU_no_dog,
	Dog_state_firmware_running_MCU_no_dog_MCU_sleeping,
	Dog_state_firmware_running_MCU_no_dog_MCU_reading_range,
	Dog_state_firmware_running_MCU_dog,
	Dog_state_firmware_running_MCU_dog_MCU_playing_no,
	Dog_state_firmware_running_MCU_dog_MCU_reading_range,
	Dog_state_firmware_running_TOF_handling_error,
	Dog_state_firmware_running_TOF_waiting_for_range,
	Dog_state_firmware_running_TOF_resetting_range_status,
	Dog_state_firmware_initializing,
	Dog_state_firmware_initializing_TOF_waiting_for_reset,
	Dog_state_firmware_initializing_TOF_writing_default_settings,
	Dog_state_firmware_initializing_TOF_writing_application_settings,
	Dog_state_firmware_initializing_TOF_waiting_for_device,
	Dog_state_last_state
} Dog_stateStates;

/*! Type definition of the data structure for the Dog_stateInternal interface scope. */
typedef struct
{
	uint32_t ticks;
	uint32_t last_detection_time_ticks;
	uint32_t last_no_time_ticks;
	uint8_t last_range_status;
} Dog_stateInternal;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define DOG_STATE_MAX_ORTHOGONAL_STATES 2

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
