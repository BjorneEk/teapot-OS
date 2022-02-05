
////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../include/event.h"

static event_listener_t global_listeners[3];
uint8_t glob_list_cnt = 0;

static event_listener_t mouse_listeners[3];
uint8_t mouse_list_cnt = 0;

static event_listener_t keyboard_listeners[3];
uint8_t key_list_cnt = 0;

void init_listener(event_listener_t evt_listener, uint8_t listener_type) {
	switch (listener_type) {
		case GLOBAL_LISTENER:
			global_listeners[glob_list_cnt++] = evt_listener;
			break;
		case MOUSE_LISTENER:
			mouse_listeners[mouse_list_cnt++] = evt_listener;
			break;
		case KEY_LISTENER:
			keyboard_listeners[key_list_cnt++] = evt_listener;
			break;
	}
}

void create_mouse_event(event_t evt) {
	for (uint8_t i = 0; i < mouse_list_cnt; i++)
		mouse_listeners[i](evt);
	for (uint8_t i = 0; i < glob_list_cnt; i++)
		global_listeners[i](evt);
}

void create_keyboard_event(event_t evt) {
	for (uint8_t i = 0; i < key_list_cnt; i++)
		keyboard_listeners[i](evt);
	for (uint8_t i = 0; i < glob_list_cnt; i++)
		global_listeners[i](evt);
}
