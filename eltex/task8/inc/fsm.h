#ifndef __FSM_H__
#define __FSM_H__

#define EVENTS_COUNT 4
#define STATES_COUNT 4
#define EVENTS_QUEUE_SIZE 4

typedef enum state_t {
	STATE_ERROR,
	STATE_IDLE,
	STATE_RESPONSE,
	STATE_DEAD
} STATE;

typedef enum event_t {
	EVENT_INIT,
	EVENT_RECV,
	EVENT_SEND,
	EVENT_KILL
} EVENT;



#endif
