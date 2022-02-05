
#ifndef EVENT_H
#define EVENT_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../../libc/include/int.h"

/**
 *    used when calling init_listener
 *    in order to specify what kind of listener
 *    should be created
 **/
#define GLOBAL_LISTENER     0
#define MOUSE_LISTENER      1
#define KEY_LISTENER        2


#define MOUSE_LEFT_BUTTON   0
#define MOUSE_RIGHT_BUTTON  1
#define MOUSE_MIDDLE_BUTTON 2

/**
 *    used in event to know what caused the event
 **/
typedef enum event_type {
	Key_pressed,
	Key_released,
	Mouse_pressed,
	Mouse_released,
	Mouse_moved
} event_type_t;

struct key_event {

	char key_char;  /**
                    *   char representation of the pressed button
                    **/

	uint8_t scancode;  /**
                       *   keyboard scancode of pressed button
                       **/
};

struct mouse_event {

	uint8_t button;  /**
                     *   which button the event
                     *   is related to
                     **/

	uint32_t x;  /**
                 *   the x and y coordinates the mouse
                 *   cursor had when the event occured
                 **/
	uint32_t y;
};

typedef struct event {

	event_type_t type;  /**
                        *   which event type the event represents
                        *   see: enum event_type
                        **/

	union {
     /**
      *   keyboard button event;
      **/
		struct key_event key;
     /**
      *   mouse button and motion event
      **/
		struct mouse_event mouse;
     /**
      *   mouse motion event.
      *   same layout as mouse button events
      *   only difference being that there is no
      *   button info here.
      **/
	};

} event_t;

typedef void (*event_listener_t)(event_t);

/**
 *    initialize a event_listener function
 *    so that it starts recieving events.
 *
 *    @param listener_type represents what kind of events
 *           it is suposed to listen for
 **/
void init_listener(event_listener_t evt_listener, uint8_t listener_type);


/**
 *    used bo keyboard an mouse drivers to
 *    create events when they occure
 **/
void create_mouse_event(event_t evt);

void create_keyboard_event(event_t evt);

#endif /* EVENT_H */
