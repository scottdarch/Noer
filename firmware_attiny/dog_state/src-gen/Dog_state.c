
#include <stdlib.h>
#include <string.h>
#include "../src/sc_types.h"
#include "Dog_state.h"
#include "Dog_stateRequired.h"
/*! \file Implementation of the state machine 'dog_state'
*/

/* prototypes of all internal functions */
static sc_boolean dog_state_check_firmware_running_lr1_lr1(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_sleeping_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_tr1_tr1(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_lr0_lr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_playing_no_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_reading_range_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_reading_range_tr1_tr1(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_reading_range_lr0_lr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_TOF_handling_error_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_TOF_waiting_for_range_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_TOF_waiting_for_range_lr0_lr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_TOF_resetting_range_status_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_initializing_TOF_waiting_for_reset_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_initializing_TOF_writing_default_settings_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_initializing_TOF_writing_application_settings_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_initializing_TOF_waiting_for_device_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_TOF__choice_0_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_firmware_running_TOF__choice_0_tr1(const Dog_state* handle);
static void dog_state_effect_firmware_running_lr1_lr1(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_no_dog_MCU_sleeping_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_tr1(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_lr0_lr0(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_dog_MCU_playing_no_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_tr1(Dog_state* handle);
static void dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_lr0_lr0(Dog_state* handle);
static void dog_state_effect_firmware_running_TOF_handling_error_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_TOF_waiting_for_range_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_TOF_waiting_for_range_lr0_lr0(Dog_state* handle);
static void dog_state_effect_firmware_running_TOF_resetting_range_status_tr0(Dog_state* handle);
static void dog_state_effect_firmware_initializing_tr0(Dog_state* handle);
static void dog_state_effect_firmware_initializing_TOF_waiting_for_reset_tr0(Dog_state* handle);
static void dog_state_effect_firmware_initializing_TOF_writing_default_settings_tr0(Dog_state* handle);
static void dog_state_effect_firmware_initializing_TOF_writing_application_settings_tr0(Dog_state* handle);
static void dog_state_effect_firmware_initializing_TOF_waiting_for_device_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_TOF__choice_0_tr0(Dog_state* handle);
static void dog_state_effect_firmware_running_TOF__choice_0_tr1(Dog_state* handle);
static void dog_state_enact_firmware_running(Dog_state* handle);
static void dog_state_enact_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle);
static void dog_state_enact_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle);
static void dog_state_enact_firmware_running_TOF_handling_error(Dog_state* handle);
static void dog_state_enact_firmware_running_TOF_resetting_range_status(Dog_state* handle);
static void dog_state_enact_firmware_initializing(Dog_state* handle);
static void dog_state_enact_firmware_initializing_TOF_waiting_for_reset(Dog_state* handle);
static void dog_state_exact_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle);
static void dog_state_exact_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle);
static void dog_state_exact_firmware_initializing_TOF_writing_application_settings(Dog_state* handle);
static void dog_state_enseq_firmware_running_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_no_dog_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_no_dog_MCU_sleeping_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_no_dog_MCU_reading_range_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_dog_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_dog_MCU_playing_no_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_dog_MCU_reading_range_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_TOF_handling_error_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_TOF_waiting_for_range_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_TOF_resetting_range_status_default(Dog_state* handle);
static void dog_state_enseq_firmware_initializing_default(Dog_state* handle);
static void dog_state_enseq_firmware_initializing_TOF_waiting_for_reset_default(Dog_state* handle);
static void dog_state_enseq_firmware_initializing_TOF_writing_default_settings_default(Dog_state* handle);
static void dog_state_enseq_firmware_initializing_TOF_writing_application_settings_default(Dog_state* handle);
static void dog_state_enseq_firmware_initializing_TOF_waiting_for_device_default(Dog_state* handle);
static void dog_state_enseq_firmware_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_no_dog_MCU_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_MCU_dog_MCU_default(Dog_state* handle);
static void dog_state_enseq_firmware_running_TOF_default(Dog_state* handle);
static void dog_state_enseq_firmware_initializing_TOF_default(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_no_dog(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_no_dog_MCU_reading_range(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_dog(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_dog_MCU_reading_range(Dog_state* handle);
static void dog_state_exseq_firmware_running_TOF_handling_error(Dog_state* handle);
static void dog_state_exseq_firmware_running_TOF_waiting_for_range(Dog_state* handle);
static void dog_state_exseq_firmware_running_TOF_resetting_range_status(Dog_state* handle);
static void dog_state_exseq_firmware_initializing(Dog_state* handle);
static void dog_state_exseq_firmware_initializing_TOF_waiting_for_reset(Dog_state* handle);
static void dog_state_exseq_firmware_initializing_TOF_writing_default_settings(Dog_state* handle);
static void dog_state_exseq_firmware_initializing_TOF_writing_application_settings(Dog_state* handle);
static void dog_state_exseq_firmware_initializing_TOF_waiting_for_device(Dog_state* handle);
static void dog_state_exseq_firmware(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_no_dog_MCU(Dog_state* handle);
static void dog_state_exseq_firmware_running_MCU_dog_MCU(Dog_state* handle);
static void dog_state_exseq_firmware_running_TOF(Dog_state* handle);
static void dog_state_exseq_firmware_initializing_TOF(Dog_state* handle);
static void dog_state_react_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle);
static void dog_state_react_firmware_running_MCU_no_dog_MCU_reading_range(Dog_state* handle);
static void dog_state_react_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle);
static void dog_state_react_firmware_running_MCU_dog_MCU_reading_range(Dog_state* handle);
static void dog_state_react_firmware_running_TOF_handling_error(Dog_state* handle);
static void dog_state_react_firmware_running_TOF_waiting_for_range(Dog_state* handle);
static void dog_state_react_firmware_running_TOF_resetting_range_status(Dog_state* handle);
static void dog_state_react_firmware_initializing_TOF_waiting_for_reset(Dog_state* handle);
static void dog_state_react_firmware_initializing_TOF_writing_default_settings(Dog_state* handle);
static void dog_state_react_firmware_initializing_TOF_writing_application_settings(Dog_state* handle);
static void dog_state_react_firmware_initializing_TOF_waiting_for_device(Dog_state* handle);
static void dog_state_react_firmware_running_TOF__choice_0(Dog_state* handle);
static void dog_state_react_firmware__entry_Default(Dog_state* handle);
static void dog_state_react_firmware_running_MCU__entry_Default(Dog_state* handle);
static void dog_state_react_firmware_running_MCU_no_dog_MCU__entry_Default(Dog_state* handle);
static void dog_state_react_firmware_running_MCU_dog_MCU__entry_Default(Dog_state* handle);
static void dog_state_react_firmware_running_TOF__entry_Default(Dog_state* handle);
static void dog_state_react_firmware_initializing_TOF__entry_Default(Dog_state* handle);
static void dog_state_react_firmware_initializing_TOF__exit_Default(Dog_state* handle);
static void dog_state_clearInEvents(Dog_state* handle);
static void dog_state_clearOutEvents(Dog_state* handle);

const uint32_t DOG_STATE_DOG_STATEINTERNAL_DETECTION_TIMEOUT_TICKS = 2;
const uint32_t DOG_STATE_DOG_STATEINTERNAL_NO_REPLAY_TIME_TICKS = 3;

void dog_state_init(Dog_state* handle)
{
	sc_integer i;

	for (i = 0; i < DOG_STATE_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = Dog_state_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;

	dog_state_clearInEvents(handle);
	dog_state_clearOutEvents(handle);

	/* Default init sequence for statechart dog_state */
	handle->internal.ticks = 0;
	handle->internal.last_detection_time_ticks = 0;
	handle->internal.last_no_time_ticks = 0;
	handle->internal.last_range_status = 0;

}

void dog_state_enter(Dog_state* handle)
{
	/* Default enter sequence for statechart dog_state */
	dog_state_enseq_firmware_default(handle);
}

void dog_state_exit(Dog_state* handle)
{
	/* Default exit sequence for statechart dog_state */
	dog_state_exseq_firmware(handle);
}

sc_boolean dog_state_isActive(const Dog_state* handle)
{
	sc_boolean result;
	if (handle->stateConfVector[0] != Dog_state_last_state || handle->stateConfVector[1] != Dog_state_last_state)
	{
		result =  bool_true;
	}
	else
	{
		result = bool_false;
	}
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean dog_state_isFinal(const Dog_state* handle)
{
   return bool_false;
}

static void dog_state_clearInEvents(Dog_state* handle)
{
}

static void dog_state_clearOutEvents(Dog_state* handle)
{
}

void dog_state_runCycle(Dog_state* handle)
{
	
	dog_state_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < DOG_STATE_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case Dog_state_firmware_running_MCU_no_dog_MCU_sleeping :
		{
			dog_state_react_firmware_running_MCU_no_dog_MCU_sleeping(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_no_dog_MCU_reading_range :
		{
			dog_state_react_firmware_running_MCU_no_dog_MCU_reading_range(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_dog_MCU_playing_no :
		{
			dog_state_react_firmware_running_MCU_dog_MCU_playing_no(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_dog_MCU_reading_range :
		{
			dog_state_react_firmware_running_MCU_dog_MCU_reading_range(handle);
			break;
		}
		case Dog_state_firmware_running_TOF_handling_error :
		{
			dog_state_react_firmware_running_TOF_handling_error(handle);
			break;
		}
		case Dog_state_firmware_running_TOF_waiting_for_range :
		{
			dog_state_react_firmware_running_TOF_waiting_for_range(handle);
			break;
		}
		case Dog_state_firmware_running_TOF_resetting_range_status :
		{
			dog_state_react_firmware_running_TOF_resetting_range_status(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_waiting_for_reset :
		{
			dog_state_react_firmware_initializing_TOF_waiting_for_reset(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_writing_default_settings :
		{
			dog_state_react_firmware_initializing_TOF_writing_default_settings(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_writing_application_settings :
		{
			dog_state_react_firmware_initializing_TOF_writing_application_settings(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_waiting_for_device :
		{
			dog_state_react_firmware_initializing_TOF_waiting_for_device(handle);
			break;
		}
		default:
			break;
		}
	}
	
	dog_state_clearInEvents(handle);
}


sc_boolean dog_state_isStateActive(const Dog_state* handle, Dog_stateStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Dog_state_firmware_running :
			result = (sc_boolean) (handle->stateConfVector[0] >= Dog_state_firmware_running
				&& handle->stateConfVector[0] <= Dog_state_firmware_running_TOF_resetting_range_status);
			break;
		case Dog_state_firmware_running_MCU_no_dog :
			result = (sc_boolean) (handle->stateConfVector[0] >= Dog_state_firmware_running_MCU_no_dog
				&& handle->stateConfVector[0] <= Dog_state_firmware_running_MCU_no_dog_MCU_reading_range);
			break;
		case Dog_state_firmware_running_MCU_no_dog_MCU_sleeping :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_running_MCU_no_dog_MCU_sleeping
			);
			break;
		case Dog_state_firmware_running_MCU_no_dog_MCU_reading_range :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_running_MCU_no_dog_MCU_reading_range
			);
			break;
		case Dog_state_firmware_running_MCU_dog :
			result = (sc_boolean) (handle->stateConfVector[0] >= Dog_state_firmware_running_MCU_dog
				&& handle->stateConfVector[0] <= Dog_state_firmware_running_MCU_dog_MCU_reading_range);
			break;
		case Dog_state_firmware_running_MCU_dog_MCU_playing_no :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_running_MCU_dog_MCU_playing_no
			);
			break;
		case Dog_state_firmware_running_MCU_dog_MCU_reading_range :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_running_MCU_dog_MCU_reading_range
			);
			break;
		case Dog_state_firmware_running_TOF_handling_error :
			result = (sc_boolean) (handle->stateConfVector[1] == Dog_state_firmware_running_TOF_handling_error
			);
			break;
		case Dog_state_firmware_running_TOF_waiting_for_range :
			result = (sc_boolean) (handle->stateConfVector[1] == Dog_state_firmware_running_TOF_waiting_for_range
			);
			break;
		case Dog_state_firmware_running_TOF_resetting_range_status :
			result = (sc_boolean) (handle->stateConfVector[1] == Dog_state_firmware_running_TOF_resetting_range_status
			);
			break;
		case Dog_state_firmware_initializing :
			result = (sc_boolean) (handle->stateConfVector[0] >= Dog_state_firmware_initializing
				&& handle->stateConfVector[0] <= Dog_state_firmware_initializing_TOF_waiting_for_device);
			break;
		case Dog_state_firmware_initializing_TOF_waiting_for_reset :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_initializing_TOF_waiting_for_reset
			);
			break;
		case Dog_state_firmware_initializing_TOF_writing_default_settings :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_initializing_TOF_writing_default_settings
			);
			break;
		case Dog_state_firmware_initializing_TOF_writing_application_settings :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_initializing_TOF_writing_application_settings
			);
			break;
		case Dog_state_firmware_initializing_TOF_waiting_for_device :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_firmware_initializing_TOF_waiting_for_device
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}








/* implementations of all internal functions */

static sc_boolean dog_state_check_firmware_running_lr1_lr1(const Dog_state* handle)
{
	return bool_true;
}

static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_sleeping_tr0_tr0(const Dog_state* handle)
{
	return bool_true;
}

static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_tr0_tr0(const Dog_state* handle)
{
	return (handle->internal.ticks - handle->internal.last_detection_time_ticks > DOG_STATE_DOG_STATEINTERNAL_DETECTION_TIMEOUT_TICKS) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_tr1_tr1(const Dog_state* handle)
{
	return dog_stateIfaceDog_dog_detected(handle);
}

static sc_boolean dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_lr0_lr0(const Dog_state* handle)
{
	return ((bool_true) && (dog_stateIfaceTOF_object_detected(handle))) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_playing_no_tr0_tr0(const Dog_state* handle)
{
	return dog_stateIfaceDog_is_done_playing_no(handle);
}

static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_reading_range_tr0_tr0(const Dog_state* handle)
{
	return (! dog_stateIfaceDog_dog_detected(handle)) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_reading_range_tr1_tr1(const Dog_state* handle)
{
	return (handle->internal.ticks - handle->internal.last_no_time_ticks > DOG_STATE_DOG_STATEINTERNAL_NO_REPLAY_TIME_TICKS) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_firmware_running_MCU_dog_MCU_reading_range_lr0_lr0(const Dog_state* handle)
{
	return ((bool_true) && (dog_stateIfaceTOF_object_detected(handle))) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_firmware_running_TOF_handling_error_tr0_tr0(const Dog_state* handle)
{
	return bool_true;
}

static sc_boolean dog_state_check_firmware_running_TOF_waiting_for_range_tr0_tr0(const Dog_state* handle)
{
	return (handle->internal.last_range_status != 0) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_firmware_running_TOF_waiting_for_range_lr0_lr0(const Dog_state* handle)
{
	return bool_true;
}

static sc_boolean dog_state_check_firmware_running_TOF_resetting_range_status_tr0_tr0(const Dog_state* handle)
{
	return bool_true;
}

static sc_boolean dog_state_check_firmware_initializing_TOF_waiting_for_reset_tr0_tr0(const Dog_state* handle)
{
	return dog_stateIfaceTOF_is_sensor_reset(handle);
}

static sc_boolean dog_state_check_firmware_initializing_TOF_writing_default_settings_tr0_tr0(const Dog_state* handle)
{
	return dog_stateIfaceTOF_did_write_default_settings(handle);
}

static sc_boolean dog_state_check_firmware_initializing_TOF_writing_application_settings_tr0_tr0(const Dog_state* handle)
{
	return dog_stateIfaceTOF_did_write_application_settings(handle);
}

static sc_boolean dog_state_check_firmware_initializing_TOF_waiting_for_device_tr0_tr0(const Dog_state* handle)
{
	return dog_stateIfaceTOF_is_sensor_ready(handle);
}

static sc_boolean dog_state_check_firmware_running_TOF__choice_0_tr0_tr0(const Dog_state* handle)
{
	return ((0xc0 & handle->internal.last_range_status) != 0) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_firmware_running_TOF__choice_0_tr1(const Dog_state* handle)
{
	return bool_true;
}

static void dog_state_effect_firmware_running_lr1_lr1(Dog_state* handle)
{
	handle->internal.ticks += 1;
}

static void dog_state_effect_firmware_running_MCU_no_dog_MCU_sleeping_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_running_MCU_no_dog_MCU_sleeping(handle);
	dog_state_enseq_firmware_running_MCU_no_dog_MCU_reading_range_default(handle);
}

static void dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_running_MCU_no_dog_MCU_reading_range(handle);
	dog_state_enseq_firmware_running_MCU_no_dog_MCU_sleeping_default(handle);
}

static void dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_tr1(Dog_state* handle)
{
	dog_state_exseq_firmware_running_MCU_no_dog(handle);
	dog_state_enseq_firmware_running_MCU_dog_default(handle);
}

static void dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_lr0_lr0(Dog_state* handle)
{
	handle->internal.last_detection_time_ticks = handle->internal.ticks;
}

static void dog_state_effect_firmware_running_MCU_dog_MCU_playing_no_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_running_MCU_dog_MCU_playing_no(handle);
	dog_state_enseq_firmware_running_MCU_dog_MCU_reading_range_default(handle);
}

static void dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_running_MCU_dog(handle);
	dog_state_enseq_firmware_running_MCU_no_dog_default(handle);
}

static void dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_tr1(Dog_state* handle)
{
	dog_state_exseq_firmware_running_MCU_dog_MCU_reading_range(handle);
	dog_state_enseq_firmware_running_MCU_dog_MCU_playing_no_default(handle);
}

static void dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_lr0_lr0(Dog_state* handle)
{
	handle->internal.last_detection_time_ticks = handle->internal.ticks;
}

static void dog_state_effect_firmware_running_TOF_handling_error_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_running_TOF_handling_error(handle);
	dog_state_enseq_firmware_running_TOF_resetting_range_status_default(handle);
}

static void dog_state_effect_firmware_running_TOF_waiting_for_range_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_running_TOF_waiting_for_range(handle);
	dog_state_react_firmware_running_TOF__choice_0(handle);
}

static void dog_state_effect_firmware_running_TOF_waiting_for_range_lr0_lr0(Dog_state* handle)
{
	handle->internal.last_range_status = dog_stateIfaceTOF_get_range_status(handle);
}

static void dog_state_effect_firmware_running_TOF_resetting_range_status_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_running_TOF_resetting_range_status(handle);
	dog_state_enseq_firmware_running_TOF_waiting_for_range_default(handle);
}

static void dog_state_effect_firmware_initializing_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_initializing(handle);
	dog_state_enseq_firmware_running_default(handle);
}

static void dog_state_effect_firmware_initializing_TOF_waiting_for_reset_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_initializing_TOF_waiting_for_reset(handle);
	dog_state_enseq_firmware_initializing_TOF_writing_default_settings_default(handle);
}

static void dog_state_effect_firmware_initializing_TOF_writing_default_settings_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_initializing_TOF_writing_default_settings(handle);
	dog_state_enseq_firmware_initializing_TOF_writing_application_settings_default(handle);
}

static void dog_state_effect_firmware_initializing_TOF_writing_application_settings_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_initializing_TOF_writing_application_settings(handle);
	dog_state_enseq_firmware_initializing_TOF_waiting_for_device_default(handle);
}

static void dog_state_effect_firmware_initializing_TOF_waiting_for_device_tr0(Dog_state* handle)
{
	dog_state_exseq_firmware_initializing_TOF_waiting_for_device(handle);
	dog_state_react_firmware_initializing_TOF__exit_Default(handle);
}

static void dog_state_effect_firmware_running_TOF__choice_0_tr0(Dog_state* handle)
{
	dog_state_enseq_firmware_running_TOF_handling_error_default(handle);
}

static void dog_state_effect_firmware_running_TOF__choice_0_tr1(Dog_state* handle)
{
	dog_state_enseq_firmware_running_TOF_resetting_range_status_default(handle);
}

/* Entry action for state 'running'. */
static void dog_state_enact_firmware_running(Dog_state* handle)
{
	/* Entry action for state 'running'. */
	dog_stateIfaceTOF_on_start(handle);
}

/* Entry action for state 'sleeping'. */
static void dog_state_enact_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle)
{
	/* Entry action for state 'sleeping'. */
	dog_stateIfaceMCU_on_sleep(handle);
}

/* Entry action for state 'playing_no'. */
static void dog_state_enact_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle)
{
	/* Entry action for state 'playing_no'. */
	dog_stateIfaceDog_on_play_no(handle);
}

/* Entry action for state 'handling_error'. */
static void dog_state_enact_firmware_running_TOF_handling_error(Dog_state* handle)
{
	/* Entry action for state 'handling_error'. */
	dog_stateIfaceTOF_on_handle_error(handle, (handle->internal.last_range_status >> 6) & 0x3);
}

/* Entry action for state 'resetting_range_status'. */
static void dog_state_enact_firmware_running_TOF_resetting_range_status(Dog_state* handle)
{
	/* Entry action for state 'resetting_range_status'. */
	dog_stateIfaceTOF_on_reset_range_status(handle);
}

/* Entry action for state 'initializing'. */
static void dog_state_enact_firmware_initializing(Dog_state* handle)
{
	/* Entry action for state 'initializing'. */
	dog_stateIfaceMCU_on_init(handle);
	dog_stateIfaceTOF_on_init(handle);
}

/* Entry action for state 'waiting_for_reset'. */
static void dog_state_enact_firmware_initializing_TOF_waiting_for_reset(Dog_state* handle)
{
	/* Entry action for state 'waiting_for_reset'. */
	dog_stateIfaceTOF_on_config_start(handle);
}

/* Exit action for state 'sleeping'. */
static void dog_state_exact_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle)
{
	/* Exit action for state 'sleeping'. */
	handle->internal.last_detection_time_ticks = handle->internal.ticks;
}

/* Exit action for state 'playing_no'. */
static void dog_state_exact_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle)
{
	/* Exit action for state 'playing_no'. */
	handle->internal.last_no_time_ticks = handle->internal.ticks;
}

/* Exit action for state 'writing_application_settings'. */
static void dog_state_exact_firmware_initializing_TOF_writing_application_settings(Dog_state* handle)
{
	/* Exit action for state 'writing_application_settings'. */
	dog_stateIfaceTOF_on_config_complete(handle);
}

/* 'default' enter sequence for state running */
static void dog_state_enseq_firmware_running_default(Dog_state* handle)
{
	/* 'default' enter sequence for state running */
	dog_state_enact_firmware_running(handle);
	dog_state_enseq_firmware_running_MCU_default(handle);
	dog_state_enseq_firmware_running_TOF_default(handle);
}

/* 'default' enter sequence for state no_dog */
static void dog_state_enseq_firmware_running_MCU_no_dog_default(Dog_state* handle)
{
	/* 'default' enter sequence for state no_dog */
	dog_state_enseq_firmware_running_MCU_no_dog_MCU_default(handle);
}

/* 'default' enter sequence for state sleeping */
static void dog_state_enseq_firmware_running_MCU_no_dog_MCU_sleeping_default(Dog_state* handle)
{
	/* 'default' enter sequence for state sleeping */
	dog_state_enact_firmware_running_MCU_no_dog_MCU_sleeping(handle);
	handle->stateConfVector[0] = Dog_state_firmware_running_MCU_no_dog_MCU_sleeping;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state reading_range */
static void dog_state_enseq_firmware_running_MCU_no_dog_MCU_reading_range_default(Dog_state* handle)
{
	/* 'default' enter sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_firmware_running_MCU_no_dog_MCU_reading_range;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state dog */
static void dog_state_enseq_firmware_running_MCU_dog_default(Dog_state* handle)
{
	/* 'default' enter sequence for state dog */
	dog_state_enseq_firmware_running_MCU_dog_MCU_default(handle);
}

/* 'default' enter sequence for state playing_no */
static void dog_state_enseq_firmware_running_MCU_dog_MCU_playing_no_default(Dog_state* handle)
{
	/* 'default' enter sequence for state playing_no */
	dog_state_enact_firmware_running_MCU_dog_MCU_playing_no(handle);
	handle->stateConfVector[0] = Dog_state_firmware_running_MCU_dog_MCU_playing_no;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state reading_range */
static void dog_state_enseq_firmware_running_MCU_dog_MCU_reading_range_default(Dog_state* handle)
{
	/* 'default' enter sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_firmware_running_MCU_dog_MCU_reading_range;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state handling_error */
static void dog_state_enseq_firmware_running_TOF_handling_error_default(Dog_state* handle)
{
	/* 'default' enter sequence for state handling_error */
	dog_state_enact_firmware_running_TOF_handling_error(handle);
	handle->stateConfVector[1] = Dog_state_firmware_running_TOF_handling_error;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state waiting_for_range */
static void dog_state_enseq_firmware_running_TOF_waiting_for_range_default(Dog_state* handle)
{
	/* 'default' enter sequence for state waiting_for_range */
	handle->stateConfVector[1] = Dog_state_firmware_running_TOF_waiting_for_range;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state resetting_range_status */
static void dog_state_enseq_firmware_running_TOF_resetting_range_status_default(Dog_state* handle)
{
	/* 'default' enter sequence for state resetting_range_status */
	dog_state_enact_firmware_running_TOF_resetting_range_status(handle);
	handle->stateConfVector[1] = Dog_state_firmware_running_TOF_resetting_range_status;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state initializing */
static void dog_state_enseq_firmware_initializing_default(Dog_state* handle)
{
	/* 'default' enter sequence for state initializing */
	dog_state_enact_firmware_initializing(handle);
	dog_state_enseq_firmware_initializing_TOF_default(handle);
}

/* 'default' enter sequence for state waiting_for_reset */
static void dog_state_enseq_firmware_initializing_TOF_waiting_for_reset_default(Dog_state* handle)
{
	/* 'default' enter sequence for state waiting_for_reset */
	dog_state_enact_firmware_initializing_TOF_waiting_for_reset(handle);
	handle->stateConfVector[0] = Dog_state_firmware_initializing_TOF_waiting_for_reset;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state writing_default_settings */
static void dog_state_enseq_firmware_initializing_TOF_writing_default_settings_default(Dog_state* handle)
{
	/* 'default' enter sequence for state writing_default_settings */
	handle->stateConfVector[0] = Dog_state_firmware_initializing_TOF_writing_default_settings;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state writing_application_settings */
static void dog_state_enseq_firmware_initializing_TOF_writing_application_settings_default(Dog_state* handle)
{
	/* 'default' enter sequence for state writing_application_settings */
	handle->stateConfVector[0] = Dog_state_firmware_initializing_TOF_writing_application_settings;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state waiting_for_device */
static void dog_state_enseq_firmware_initializing_TOF_waiting_for_device_default(Dog_state* handle)
{
	/* 'default' enter sequence for state waiting_for_device */
	handle->stateConfVector[0] = Dog_state_firmware_initializing_TOF_waiting_for_device;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region firmware */
static void dog_state_enseq_firmware_default(Dog_state* handle)
{
	/* 'default' enter sequence for region firmware */
	dog_state_react_firmware__entry_Default(handle);
}

/* 'default' enter sequence for region MCU */
static void dog_state_enseq_firmware_running_MCU_default(Dog_state* handle)
{
	/* 'default' enter sequence for region MCU */
	dog_state_react_firmware_running_MCU__entry_Default(handle);
}

/* 'default' enter sequence for region MCU */
static void dog_state_enseq_firmware_running_MCU_no_dog_MCU_default(Dog_state* handle)
{
	/* 'default' enter sequence for region MCU */
	dog_state_react_firmware_running_MCU_no_dog_MCU__entry_Default(handle);
}

/* 'default' enter sequence for region MCU */
static void dog_state_enseq_firmware_running_MCU_dog_MCU_default(Dog_state* handle)
{
	/* 'default' enter sequence for region MCU */
	dog_state_react_firmware_running_MCU_dog_MCU__entry_Default(handle);
}

/* 'default' enter sequence for region TOF */
static void dog_state_enseq_firmware_running_TOF_default(Dog_state* handle)
{
	/* 'default' enter sequence for region TOF */
	dog_state_react_firmware_running_TOF__entry_Default(handle);
}

/* 'default' enter sequence for region TOF */
static void dog_state_enseq_firmware_initializing_TOF_default(Dog_state* handle)
{
	/* 'default' enter sequence for region TOF */
	dog_state_react_firmware_initializing_TOF__entry_Default(handle);
}

/* Default exit sequence for state no_dog */
static void dog_state_exseq_firmware_running_MCU_no_dog(Dog_state* handle)
{
	/* Default exit sequence for state no_dog */
	dog_state_exseq_firmware_running_MCU_no_dog_MCU(handle);
}

/* Default exit sequence for state sleeping */
static void dog_state_exseq_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle)
{
	/* Default exit sequence for state sleeping */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
	dog_state_exact_firmware_running_MCU_no_dog_MCU_sleeping(handle);
}

/* Default exit sequence for state reading_range */
static void dog_state_exseq_firmware_running_MCU_no_dog_MCU_reading_range(Dog_state* handle)
{
	/* Default exit sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state dog */
static void dog_state_exseq_firmware_running_MCU_dog(Dog_state* handle)
{
	/* Default exit sequence for state dog */
	dog_state_exseq_firmware_running_MCU_dog_MCU(handle);
}

/* Default exit sequence for state playing_no */
static void dog_state_exseq_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle)
{
	/* Default exit sequence for state playing_no */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
	dog_state_exact_firmware_running_MCU_dog_MCU_playing_no(handle);
}

/* Default exit sequence for state reading_range */
static void dog_state_exseq_firmware_running_MCU_dog_MCU_reading_range(Dog_state* handle)
{
	/* Default exit sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state handling_error */
static void dog_state_exseq_firmware_running_TOF_handling_error(Dog_state* handle)
{
	/* Default exit sequence for state handling_error */
	handle->stateConfVector[1] = Dog_state_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state waiting_for_range */
static void dog_state_exseq_firmware_running_TOF_waiting_for_range(Dog_state* handle)
{
	/* Default exit sequence for state waiting_for_range */
	handle->stateConfVector[1] = Dog_state_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state resetting_range_status */
static void dog_state_exseq_firmware_running_TOF_resetting_range_status(Dog_state* handle)
{
	/* Default exit sequence for state resetting_range_status */
	handle->stateConfVector[1] = Dog_state_last_state;
	handle->stateConfVectorPosition = 1;
}

/* Default exit sequence for state initializing */
static void dog_state_exseq_firmware_initializing(Dog_state* handle)
{
	/* Default exit sequence for state initializing */
	dog_state_exseq_firmware_initializing_TOF(handle);
}

/* Default exit sequence for state waiting_for_reset */
static void dog_state_exseq_firmware_initializing_TOF_waiting_for_reset(Dog_state* handle)
{
	/* Default exit sequence for state waiting_for_reset */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state writing_default_settings */
static void dog_state_exseq_firmware_initializing_TOF_writing_default_settings(Dog_state* handle)
{
	/* Default exit sequence for state writing_default_settings */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state writing_application_settings */
static void dog_state_exseq_firmware_initializing_TOF_writing_application_settings(Dog_state* handle)
{
	/* Default exit sequence for state writing_application_settings */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
	dog_state_exact_firmware_initializing_TOF_writing_application_settings(handle);
}

/* Default exit sequence for state waiting_for_device */
static void dog_state_exseq_firmware_initializing_TOF_waiting_for_device(Dog_state* handle)
{
	/* Default exit sequence for state waiting_for_device */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region firmware */
static void dog_state_exseq_firmware(Dog_state* handle)
{
	/* Default exit sequence for region firmware */
	/* Handle exit of all possible states (of dog_state.firmware) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_firmware_running_MCU_no_dog_MCU_sleeping :
		{
			dog_state_exseq_firmware_running_MCU_no_dog_MCU_sleeping(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_no_dog_MCU_reading_range :
		{
			dog_state_exseq_firmware_running_MCU_no_dog_MCU_reading_range(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_dog_MCU_playing_no :
		{
			dog_state_exseq_firmware_running_MCU_dog_MCU_playing_no(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_dog_MCU_reading_range :
		{
			dog_state_exseq_firmware_running_MCU_dog_MCU_reading_range(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_waiting_for_reset :
		{
			dog_state_exseq_firmware_initializing_TOF_waiting_for_reset(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_writing_default_settings :
		{
			dog_state_exseq_firmware_initializing_TOF_writing_default_settings(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_writing_application_settings :
		{
			dog_state_exseq_firmware_initializing_TOF_writing_application_settings(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_waiting_for_device :
		{
			dog_state_exseq_firmware_initializing_TOF_waiting_for_device(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of dog_state.firmware) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Dog_state_firmware_running_TOF_handling_error :
		{
			dog_state_exseq_firmware_running_TOF_handling_error(handle);
			break;
		}
		case Dog_state_firmware_running_TOF_waiting_for_range :
		{
			dog_state_exseq_firmware_running_TOF_waiting_for_range(handle);
			break;
		}
		case Dog_state_firmware_running_TOF_resetting_range_status :
		{
			dog_state_exseq_firmware_running_TOF_resetting_range_status(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region MCU */
static void dog_state_exseq_firmware_running_MCU(Dog_state* handle)
{
	/* Default exit sequence for region MCU */
	/* Handle exit of all possible states (of dog_state.firmware.running.MCU) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_firmware_running_MCU_no_dog_MCU_sleeping :
		{
			dog_state_exseq_firmware_running_MCU_no_dog_MCU_sleeping(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_no_dog_MCU_reading_range :
		{
			dog_state_exseq_firmware_running_MCU_no_dog_MCU_reading_range(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_dog_MCU_playing_no :
		{
			dog_state_exseq_firmware_running_MCU_dog_MCU_playing_no(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_dog_MCU_reading_range :
		{
			dog_state_exseq_firmware_running_MCU_dog_MCU_reading_range(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region MCU */
static void dog_state_exseq_firmware_running_MCU_no_dog_MCU(Dog_state* handle)
{
	/* Default exit sequence for region MCU */
	/* Handle exit of all possible states (of dog_state.firmware.running.MCU.no_dog.MCU) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_firmware_running_MCU_no_dog_MCU_sleeping :
		{
			dog_state_exseq_firmware_running_MCU_no_dog_MCU_sleeping(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_no_dog_MCU_reading_range :
		{
			dog_state_exseq_firmware_running_MCU_no_dog_MCU_reading_range(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region MCU */
static void dog_state_exseq_firmware_running_MCU_dog_MCU(Dog_state* handle)
{
	/* Default exit sequence for region MCU */
	/* Handle exit of all possible states (of dog_state.firmware.running.MCU.dog.MCU) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_firmware_running_MCU_dog_MCU_playing_no :
		{
			dog_state_exseq_firmware_running_MCU_dog_MCU_playing_no(handle);
			break;
		}
		case Dog_state_firmware_running_MCU_dog_MCU_reading_range :
		{
			dog_state_exseq_firmware_running_MCU_dog_MCU_reading_range(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region TOF */
static void dog_state_exseq_firmware_running_TOF(Dog_state* handle)
{
	/* Default exit sequence for region TOF */
	/* Handle exit of all possible states (of dog_state.firmware.running.TOF) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Dog_state_firmware_running_TOF_handling_error :
		{
			dog_state_exseq_firmware_running_TOF_handling_error(handle);
			break;
		}
		case Dog_state_firmware_running_TOF_waiting_for_range :
		{
			dog_state_exseq_firmware_running_TOF_waiting_for_range(handle);
			break;
		}
		case Dog_state_firmware_running_TOF_resetting_range_status :
		{
			dog_state_exseq_firmware_running_TOF_resetting_range_status(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region TOF */
static void dog_state_exseq_firmware_initializing_TOF(Dog_state* handle)
{
	/* Default exit sequence for region TOF */
	/* Handle exit of all possible states (of dog_state.firmware.initializing.TOF) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_firmware_initializing_TOF_waiting_for_reset :
		{
			dog_state_exseq_firmware_initializing_TOF_waiting_for_reset(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_writing_default_settings :
		{
			dog_state_exseq_firmware_initializing_TOF_writing_default_settings(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_writing_application_settings :
		{
			dog_state_exseq_firmware_initializing_TOF_writing_application_settings(handle);
			break;
		}
		case Dog_state_firmware_initializing_TOF_waiting_for_device :
		{
			dog_state_exseq_firmware_initializing_TOF_waiting_for_device(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state sleeping. */
static void dog_state_react_firmware_running_MCU_no_dog_MCU_sleeping(Dog_state* handle)
{
	/* The reactions of state sleeping. */
	dog_state_effect_firmware_running_lr1_lr1(handle);
	dog_state_effect_firmware_running_MCU_no_dog_MCU_sleeping_tr0(handle);
}

/* The reactions of state reading_range. */
static void dog_state_react_firmware_running_MCU_no_dog_MCU_reading_range(Dog_state* handle)
{
	/* The reactions of state reading_range. */
	dog_state_effect_firmware_running_lr1_lr1(handle);
	if (dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_tr0(handle);
	}  else
	{
		if (dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_tr1_tr1(handle) == bool_true)
		{ 
			dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_tr1(handle);
		}  else
		{
			if (dog_state_check_firmware_running_MCU_no_dog_MCU_reading_range_lr0_lr0(handle) == bool_true)
			{ 
				dog_state_effect_firmware_running_MCU_no_dog_MCU_reading_range_lr0_lr0(handle);
			} 
		}
	}
}

/* The reactions of state playing_no. */
static void dog_state_react_firmware_running_MCU_dog_MCU_playing_no(Dog_state* handle)
{
	/* The reactions of state playing_no. */
	dog_state_effect_firmware_running_lr1_lr1(handle);
	if (dog_state_check_firmware_running_MCU_dog_MCU_playing_no_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_running_MCU_dog_MCU_playing_no_tr0(handle);
	} 
}

/* The reactions of state reading_range. */
static void dog_state_react_firmware_running_MCU_dog_MCU_reading_range(Dog_state* handle)
{
	/* The reactions of state reading_range. */
	dog_state_effect_firmware_running_lr1_lr1(handle);
	if (dog_state_check_firmware_running_MCU_dog_MCU_reading_range_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_tr0(handle);
	}  else
	{
		if (dog_state_check_firmware_running_MCU_dog_MCU_reading_range_tr1_tr1(handle) == bool_true)
		{ 
			dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_tr1(handle);
		}  else
		{
			if (dog_state_check_firmware_running_MCU_dog_MCU_reading_range_lr0_lr0(handle) == bool_true)
			{ 
				dog_state_effect_firmware_running_MCU_dog_MCU_reading_range_lr0_lr0(handle);
			} 
		}
	}
}

/* The reactions of state handling_error. */
static void dog_state_react_firmware_running_TOF_handling_error(Dog_state* handle)
{
	/* The reactions of state handling_error. */
	dog_state_effect_firmware_running_TOF_handling_error_tr0(handle);
}

/* The reactions of state waiting_for_range. */
static void dog_state_react_firmware_running_TOF_waiting_for_range(Dog_state* handle)
{
	/* The reactions of state waiting_for_range. */
	if (dog_state_check_firmware_running_TOF_waiting_for_range_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_running_TOF_waiting_for_range_tr0(handle);
	}  else
	{
		dog_state_effect_firmware_running_TOF_waiting_for_range_lr0_lr0(handle);
	}
}

/* The reactions of state resetting_range_status. */
static void dog_state_react_firmware_running_TOF_resetting_range_status(Dog_state* handle)
{
	/* The reactions of state resetting_range_status. */
	dog_state_effect_firmware_running_TOF_resetting_range_status_tr0(handle);
}

/* The reactions of state waiting_for_reset. */
static void dog_state_react_firmware_initializing_TOF_waiting_for_reset(Dog_state* handle)
{
	/* The reactions of state waiting_for_reset. */
	if (dog_state_check_firmware_initializing_TOF_waiting_for_reset_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_initializing_TOF_waiting_for_reset_tr0(handle);
	} 
}

/* The reactions of state writing_default_settings. */
static void dog_state_react_firmware_initializing_TOF_writing_default_settings(Dog_state* handle)
{
	/* The reactions of state writing_default_settings. */
	if (dog_state_check_firmware_initializing_TOF_writing_default_settings_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_initializing_TOF_writing_default_settings_tr0(handle);
	} 
}

/* The reactions of state writing_application_settings. */
static void dog_state_react_firmware_initializing_TOF_writing_application_settings(Dog_state* handle)
{
	/* The reactions of state writing_application_settings. */
	if (dog_state_check_firmware_initializing_TOF_writing_application_settings_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_initializing_TOF_writing_application_settings_tr0(handle);
	} 
}

/* The reactions of state waiting_for_device. */
static void dog_state_react_firmware_initializing_TOF_waiting_for_device(Dog_state* handle)
{
	/* The reactions of state waiting_for_device. */
	if (dog_state_check_firmware_initializing_TOF_waiting_for_device_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_initializing_TOF_waiting_for_device_tr0(handle);
	} 
}

/* The reactions of state null. */
static void dog_state_react_firmware_running_TOF__choice_0(Dog_state* handle)
{
	/* The reactions of state null. */
	if (dog_state_check_firmware_running_TOF__choice_0_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_firmware_running_TOF__choice_0_tr0(handle);
	}  else
	{
		dog_state_effect_firmware_running_TOF__choice_0_tr1(handle);
	}
}

/* Default react sequence for initial entry  */
static void dog_state_react_firmware__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_firmware_initializing_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_firmware_running_MCU__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_firmware_running_MCU_no_dog_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_firmware_running_MCU_no_dog_MCU__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_firmware_running_MCU_no_dog_MCU_reading_range_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_firmware_running_MCU_dog_MCU__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_firmware_running_MCU_dog_MCU_playing_no_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_firmware_running_TOF__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_firmware_running_TOF_waiting_for_range_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_firmware_initializing_TOF__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_firmware_initializing_TOF_waiting_for_reset_default(handle);
}

/* The reactions of exit default. */
static void dog_state_react_firmware_initializing_TOF__exit_Default(Dog_state* handle)
{
	/* The reactions of exit default. */
	dog_state_effect_firmware_initializing_tr0(handle);
}


