
#include <stdlib.h>
#include <string.h>
#include "../src/sc_types.h"
#include "Dog_state.h"
#include "Dog_stateRequired.h"
/*! \file Implementation of the state machine 'dog_state'
*/

/* prototypes of all internal functions */
static sc_boolean dog_state_check_main_region_running_lr0_lr0(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_sleeping_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_reading_range_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_reading_range_tr1_tr1(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_reading_range_lr0_lr0(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_dog_r1_playing_no_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_dog_r1_reading_range_tr0_tr0(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_dog_r1_reading_range_tr1_tr1(const Dog_state* handle);
static sc_boolean dog_state_check_main_region_running_r1_dog_r1_reading_range_lr0_lr0(const Dog_state* handle);
static void dog_state_effect_main_region_running_lr0_lr0(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_no_dog_r1_sleeping_tr0(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_tr0(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_tr1(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_lr0_lr0(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_dog_r1_playing_no_tr0(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_dog_r1_reading_range_tr0(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_dog_r1_reading_range_tr1(Dog_state* handle);
static void dog_state_effect_main_region_running_r1_dog_r1_reading_range_lr0_lr0(Dog_state* handle);
static void dog_state_enact_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle);
static void dog_state_enact_main_region_running_r1_dog_r1_playing_no(Dog_state* handle);
static void dog_state_exact_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle);
static void dog_state_exact_main_region_running_r1_dog_r1_playing_no(Dog_state* handle);
static void dog_state_enseq_main_region_running_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_no_dog_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_no_dog_r1_sleeping_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_no_dog_r1_reading_range_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_dog_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_dog_r1_playing_no_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_dog_r1_reading_range_default(Dog_state* handle);
static void dog_state_enseq_main_region_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_no_dog_r1_default(Dog_state* handle);
static void dog_state_enseq_main_region_running_r1_dog_r1_default(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_no_dog(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_no_dog_r1_reading_range(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_dog(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_dog_r1_playing_no(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_dog_r1_reading_range(Dog_state* handle);
static void dog_state_exseq_main_region(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_no_dog_r1(Dog_state* handle);
static void dog_state_exseq_main_region_running_r1_dog_r1(Dog_state* handle);
static void dog_state_react_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle);
static void dog_state_react_main_region_running_r1_no_dog_r1_reading_range(Dog_state* handle);
static void dog_state_react_main_region_running_r1_dog_r1_playing_no(Dog_state* handle);
static void dog_state_react_main_region_running_r1_dog_r1_reading_range(Dog_state* handle);
static void dog_state_react_main_region_running_r1__entry_Default(Dog_state* handle);
static void dog_state_react_main_region_running_r1_no_dog_r1__entry_Default(Dog_state* handle);
static void dog_state_react_main_region_running_r1_dog_r1__entry_Default(Dog_state* handle);
static void dog_state_react_main_region__entry_Default(Dog_state* handle);
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

}

void dog_state_enter(Dog_state* handle)
{
	/* Default enter sequence for statechart dog_state */
	dog_state_enseq_main_region_default(handle);
}

void dog_state_exit(Dog_state* handle)
{
	/* Default exit sequence for statechart dog_state */
	dog_state_exseq_main_region(handle);
}

sc_boolean dog_state_isActive(const Dog_state* handle)
{
	sc_boolean result;
	if (handle->stateConfVector[0] != Dog_state_last_state)
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
		case Dog_state_main_region_running_r1_no_dog_r1_sleeping :
		{
			dog_state_react_main_region_running_r1_no_dog_r1_sleeping(handle);
			break;
		}
		case Dog_state_main_region_running_r1_no_dog_r1_reading_range :
		{
			dog_state_react_main_region_running_r1_no_dog_r1_reading_range(handle);
			break;
		}
		case Dog_state_main_region_running_r1_dog_r1_playing_no :
		{
			dog_state_react_main_region_running_r1_dog_r1_playing_no(handle);
			break;
		}
		case Dog_state_main_region_running_r1_dog_r1_reading_range :
		{
			dog_state_react_main_region_running_r1_dog_r1_reading_range(handle);
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
		case Dog_state_main_region_running :
			result = (sc_boolean) (handle->stateConfVector[0] >= Dog_state_main_region_running
				&& handle->stateConfVector[0] <= Dog_state_main_region_running_r1_dog_r1_reading_range);
			break;
		case Dog_state_main_region_running_r1_no_dog :
			result = (sc_boolean) (handle->stateConfVector[0] >= Dog_state_main_region_running_r1_no_dog
				&& handle->stateConfVector[0] <= Dog_state_main_region_running_r1_no_dog_r1_reading_range);
			break;
		case Dog_state_main_region_running_r1_no_dog_r1_sleeping :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_main_region_running_r1_no_dog_r1_sleeping
			);
			break;
		case Dog_state_main_region_running_r1_no_dog_r1_reading_range :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_main_region_running_r1_no_dog_r1_reading_range
			);
			break;
		case Dog_state_main_region_running_r1_dog :
			result = (sc_boolean) (handle->stateConfVector[0] >= Dog_state_main_region_running_r1_dog
				&& handle->stateConfVector[0] <= Dog_state_main_region_running_r1_dog_r1_reading_range);
			break;
		case Dog_state_main_region_running_r1_dog_r1_playing_no :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_main_region_running_r1_dog_r1_playing_no
			);
			break;
		case Dog_state_main_region_running_r1_dog_r1_reading_range :
			result = (sc_boolean) (handle->stateConfVector[0] == Dog_state_main_region_running_r1_dog_r1_reading_range
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}




/* implementations of all internal functions */

static sc_boolean dog_state_check_main_region_running_lr0_lr0(const Dog_state* handle)
{
	return bool_true;
}

static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_sleeping_tr0_tr0(const Dog_state* handle)
{
	return bool_true;
}

static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_reading_range_tr0_tr0(const Dog_state* handle)
{
	return dog_stateIface_dog_detected(handle);
}

static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_reading_range_tr1_tr1(const Dog_state* handle)
{
	return (handle->internal.ticks - handle->internal.last_detection_time_ticks > DOG_STATE_DOG_STATEINTERNAL_DETECTION_TIMEOUT_TICKS) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_main_region_running_r1_no_dog_r1_reading_range_lr0_lr0(const Dog_state* handle)
{
	return ((bool_true) && (dog_stateIface_object_detected(handle))) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_main_region_running_r1_dog_r1_playing_no_tr0_tr0(const Dog_state* handle)
{
	return dog_stateIface_is_done_playing_no(handle);
}

static sc_boolean dog_state_check_main_region_running_r1_dog_r1_reading_range_tr0_tr0(const Dog_state* handle)
{
	return (! dog_stateIface_dog_detected(handle)) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_main_region_running_r1_dog_r1_reading_range_tr1_tr1(const Dog_state* handle)
{
	return (handle->internal.ticks - handle->internal.last_no_time_ticks > DOG_STATE_DOG_STATEINTERNAL_NO_REPLAY_TIME_TICKS) ? bool_true : bool_false;
}

static sc_boolean dog_state_check_main_region_running_r1_dog_r1_reading_range_lr0_lr0(const Dog_state* handle)
{
	return ((bool_true) && (dog_stateIface_object_detected(handle))) ? bool_true : bool_false;
}

static void dog_state_effect_main_region_running_lr0_lr0(Dog_state* handle)
{
	handle->internal.ticks += 1;
}

static void dog_state_effect_main_region_running_r1_no_dog_r1_sleeping_tr0(Dog_state* handle)
{
	dog_state_exseq_main_region_running_r1_no_dog_r1_sleeping(handle);
	dog_state_enseq_main_region_running_r1_no_dog_r1_reading_range_default(handle);
}

static void dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_tr0(Dog_state* handle)
{
	dog_state_exseq_main_region_running_r1_no_dog(handle);
	dog_state_enseq_main_region_running_r1_dog_default(handle);
}

static void dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_tr1(Dog_state* handle)
{
	dog_state_exseq_main_region_running_r1_no_dog_r1_reading_range(handle);
	dog_state_enseq_main_region_running_r1_no_dog_r1_sleeping_default(handle);
}

static void dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_lr0_lr0(Dog_state* handle)
{
	handle->internal.last_detection_time_ticks = handle->internal.ticks;
}

static void dog_state_effect_main_region_running_r1_dog_r1_playing_no_tr0(Dog_state* handle)
{
	dog_state_exseq_main_region_running_r1_dog_r1_playing_no(handle);
	dog_state_enseq_main_region_running_r1_dog_r1_reading_range_default(handle);
}

static void dog_state_effect_main_region_running_r1_dog_r1_reading_range_tr0(Dog_state* handle)
{
	dog_state_exseq_main_region_running_r1_dog(handle);
	dog_state_enseq_main_region_running_r1_no_dog_default(handle);
}

static void dog_state_effect_main_region_running_r1_dog_r1_reading_range_tr1(Dog_state* handle)
{
	dog_state_exseq_main_region_running_r1_dog_r1_reading_range(handle);
	dog_state_enseq_main_region_running_r1_dog_r1_playing_no_default(handle);
}

static void dog_state_effect_main_region_running_r1_dog_r1_reading_range_lr0_lr0(Dog_state* handle)
{
	handle->internal.last_detection_time_ticks = handle->internal.ticks;
}

/* Entry action for state 'sleeping'. */
static void dog_state_enact_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle)
{
	/* Entry action for state 'sleeping'. */
	dog_stateIface_on_sleep(handle);
}

/* Entry action for state 'playing_no'. */
static void dog_state_enact_main_region_running_r1_dog_r1_playing_no(Dog_state* handle)
{
	/* Entry action for state 'playing_no'. */
	dog_stateIface_on_play_no(handle);
}

/* Exit action for state 'sleeping'. */
static void dog_state_exact_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle)
{
	/* Exit action for state 'sleeping'. */
	handle->internal.last_detection_time_ticks = handle->internal.ticks;
}

/* Exit action for state 'playing_no'. */
static void dog_state_exact_main_region_running_r1_dog_r1_playing_no(Dog_state* handle)
{
	/* Exit action for state 'playing_no'. */
	handle->internal.last_no_time_ticks = handle->internal.ticks;
}

/* 'default' enter sequence for state running */
static void dog_state_enseq_main_region_running_default(Dog_state* handle)
{
	/* 'default' enter sequence for state running */
	dog_state_enseq_main_region_running_r1_default(handle);
}

/* 'default' enter sequence for state no_dog */
static void dog_state_enseq_main_region_running_r1_no_dog_default(Dog_state* handle)
{
	/* 'default' enter sequence for state no_dog */
	dog_state_enseq_main_region_running_r1_no_dog_r1_default(handle);
}

/* 'default' enter sequence for state sleeping */
static void dog_state_enseq_main_region_running_r1_no_dog_r1_sleeping_default(Dog_state* handle)
{
	/* 'default' enter sequence for state sleeping */
	dog_state_enact_main_region_running_r1_no_dog_r1_sleeping(handle);
	handle->stateConfVector[0] = Dog_state_main_region_running_r1_no_dog_r1_sleeping;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state reading_range */
static void dog_state_enseq_main_region_running_r1_no_dog_r1_reading_range_default(Dog_state* handle)
{
	/* 'default' enter sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_main_region_running_r1_no_dog_r1_reading_range;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state dog */
static void dog_state_enseq_main_region_running_r1_dog_default(Dog_state* handle)
{
	/* 'default' enter sequence for state dog */
	dog_state_enseq_main_region_running_r1_dog_r1_default(handle);
}

/* 'default' enter sequence for state playing_no */
static void dog_state_enseq_main_region_running_r1_dog_r1_playing_no_default(Dog_state* handle)
{
	/* 'default' enter sequence for state playing_no */
	dog_state_enact_main_region_running_r1_dog_r1_playing_no(handle);
	handle->stateConfVector[0] = Dog_state_main_region_running_r1_dog_r1_playing_no;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state reading_range */
static void dog_state_enseq_main_region_running_r1_dog_r1_reading_range_default(Dog_state* handle)
{
	/* 'default' enter sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_main_region_running_r1_dog_r1_reading_range;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void dog_state_enseq_main_region_default(Dog_state* handle)
{
	/* 'default' enter sequence for region main region */
	dog_state_react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void dog_state_enseq_main_region_running_r1_default(Dog_state* handle)
{
	/* 'default' enter sequence for region r1 */
	dog_state_react_main_region_running_r1__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void dog_state_enseq_main_region_running_r1_no_dog_r1_default(Dog_state* handle)
{
	/* 'default' enter sequence for region r1 */
	dog_state_react_main_region_running_r1_no_dog_r1__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void dog_state_enseq_main_region_running_r1_dog_r1_default(Dog_state* handle)
{
	/* 'default' enter sequence for region r1 */
	dog_state_react_main_region_running_r1_dog_r1__entry_Default(handle);
}

/* Default exit sequence for state no_dog */
static void dog_state_exseq_main_region_running_r1_no_dog(Dog_state* handle)
{
	/* Default exit sequence for state no_dog */
	dog_state_exseq_main_region_running_r1_no_dog_r1(handle);
}

/* Default exit sequence for state sleeping */
static void dog_state_exseq_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle)
{
	/* Default exit sequence for state sleeping */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
	dog_state_exact_main_region_running_r1_no_dog_r1_sleeping(handle);
}

/* Default exit sequence for state reading_range */
static void dog_state_exseq_main_region_running_r1_no_dog_r1_reading_range(Dog_state* handle)
{
	/* Default exit sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state dog */
static void dog_state_exseq_main_region_running_r1_dog(Dog_state* handle)
{
	/* Default exit sequence for state dog */
	dog_state_exseq_main_region_running_r1_dog_r1(handle);
}

/* Default exit sequence for state playing_no */
static void dog_state_exseq_main_region_running_r1_dog_r1_playing_no(Dog_state* handle)
{
	/* Default exit sequence for state playing_no */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
	dog_state_exact_main_region_running_r1_dog_r1_playing_no(handle);
}

/* Default exit sequence for state reading_range */
static void dog_state_exseq_main_region_running_r1_dog_r1_reading_range(Dog_state* handle)
{
	/* Default exit sequence for state reading_range */
	handle->stateConfVector[0] = Dog_state_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
static void dog_state_exseq_main_region(Dog_state* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of dog_state.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_main_region_running_r1_no_dog_r1_sleeping :
		{
			dog_state_exseq_main_region_running_r1_no_dog_r1_sleeping(handle);
			break;
		}
		case Dog_state_main_region_running_r1_no_dog_r1_reading_range :
		{
			dog_state_exseq_main_region_running_r1_no_dog_r1_reading_range(handle);
			break;
		}
		case Dog_state_main_region_running_r1_dog_r1_playing_no :
		{
			dog_state_exseq_main_region_running_r1_dog_r1_playing_no(handle);
			break;
		}
		case Dog_state_main_region_running_r1_dog_r1_reading_range :
		{
			dog_state_exseq_main_region_running_r1_dog_r1_reading_range(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void dog_state_exseq_main_region_running_r1(Dog_state* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of dog_state.main_region.running.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_main_region_running_r1_no_dog_r1_sleeping :
		{
			dog_state_exseq_main_region_running_r1_no_dog_r1_sleeping(handle);
			break;
		}
		case Dog_state_main_region_running_r1_no_dog_r1_reading_range :
		{
			dog_state_exseq_main_region_running_r1_no_dog_r1_reading_range(handle);
			break;
		}
		case Dog_state_main_region_running_r1_dog_r1_playing_no :
		{
			dog_state_exseq_main_region_running_r1_dog_r1_playing_no(handle);
			break;
		}
		case Dog_state_main_region_running_r1_dog_r1_reading_range :
		{
			dog_state_exseq_main_region_running_r1_dog_r1_reading_range(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void dog_state_exseq_main_region_running_r1_no_dog_r1(Dog_state* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of dog_state.main_region.running.r1.no_dog.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_main_region_running_r1_no_dog_r1_sleeping :
		{
			dog_state_exseq_main_region_running_r1_no_dog_r1_sleeping(handle);
			break;
		}
		case Dog_state_main_region_running_r1_no_dog_r1_reading_range :
		{
			dog_state_exseq_main_region_running_r1_no_dog_r1_reading_range(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void dog_state_exseq_main_region_running_r1_dog_r1(Dog_state* handle)
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of dog_state.main_region.running.r1.dog.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Dog_state_main_region_running_r1_dog_r1_playing_no :
		{
			dog_state_exseq_main_region_running_r1_dog_r1_playing_no(handle);
			break;
		}
		case Dog_state_main_region_running_r1_dog_r1_reading_range :
		{
			dog_state_exseq_main_region_running_r1_dog_r1_reading_range(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state sleeping. */
static void dog_state_react_main_region_running_r1_no_dog_r1_sleeping(Dog_state* handle)
{
	/* The reactions of state sleeping. */
	dog_state_effect_main_region_running_lr0_lr0(handle);
	dog_state_effect_main_region_running_r1_no_dog_r1_sleeping_tr0(handle);
}

/* The reactions of state reading_range. */
static void dog_state_react_main_region_running_r1_no_dog_r1_reading_range(Dog_state* handle)
{
	/* The reactions of state reading_range. */
	dog_state_effect_main_region_running_lr0_lr0(handle);
	if (dog_state_check_main_region_running_r1_no_dog_r1_reading_range_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_tr0(handle);
	}  else
	{
		if (dog_state_check_main_region_running_r1_no_dog_r1_reading_range_tr1_tr1(handle) == bool_true)
		{ 
			dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_tr1(handle);
		}  else
		{
			if (dog_state_check_main_region_running_r1_no_dog_r1_reading_range_lr0_lr0(handle) == bool_true)
			{ 
				dog_state_effect_main_region_running_r1_no_dog_r1_reading_range_lr0_lr0(handle);
			} 
		}
	}
}

/* The reactions of state playing_no. */
static void dog_state_react_main_region_running_r1_dog_r1_playing_no(Dog_state* handle)
{
	/* The reactions of state playing_no. */
	dog_state_effect_main_region_running_lr0_lr0(handle);
	if (dog_state_check_main_region_running_r1_dog_r1_playing_no_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_main_region_running_r1_dog_r1_playing_no_tr0(handle);
	} 
}

/* The reactions of state reading_range. */
static void dog_state_react_main_region_running_r1_dog_r1_reading_range(Dog_state* handle)
{
	/* The reactions of state reading_range. */
	dog_state_effect_main_region_running_lr0_lr0(handle);
	if (dog_state_check_main_region_running_r1_dog_r1_reading_range_tr0_tr0(handle) == bool_true)
	{ 
		dog_state_effect_main_region_running_r1_dog_r1_reading_range_tr0(handle);
	}  else
	{
		if (dog_state_check_main_region_running_r1_dog_r1_reading_range_tr1_tr1(handle) == bool_true)
		{ 
			dog_state_effect_main_region_running_r1_dog_r1_reading_range_tr1(handle);
		}  else
		{
			if (dog_state_check_main_region_running_r1_dog_r1_reading_range_lr0_lr0(handle) == bool_true)
			{ 
				dog_state_effect_main_region_running_r1_dog_r1_reading_range_lr0_lr0(handle);
			} 
		}
	}
}

/* Default react sequence for initial entry  */
static void dog_state_react_main_region_running_r1__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_main_region_running_r1_no_dog_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_main_region_running_r1_no_dog_r1__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_main_region_running_r1_no_dog_r1_reading_range_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_main_region_running_r1_dog_r1__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_main_region_running_r1_dog_r1_playing_no_default(handle);
}

/* Default react sequence for initial entry  */
static void dog_state_react_main_region__entry_Default(Dog_state* handle)
{
	/* Default react sequence for initial entry  */
	dog_state_enseq_main_region_running_default(handle);
}


