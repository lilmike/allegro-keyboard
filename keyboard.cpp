include "keyboard.h"

keyboard::keyboard(void)
{
	if(!al_is_keyboard_installed()) {
		al_install_keyboard();
	}
	keys_down = new bool[ALLEGRO_KEY_MAX];
	keys_pressed = new bool[ALLEGRO_KEY_MAX];
	for(int x = 0; x<ALLEGRO_KEY_MAX; x++) {
		keys_down[x] = keys_pressed[x] = false;
	}
	queue =  NULL;
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
}


keyboard::~keyboard(void)
{
	delete[] keys_down;
	delete[] keys_pressed;
	al_destroy_event_queue(queue);
}

bool keyboard::poll(ALLEGRO_EVENT& event) {
	ALLEGRO_EVENT ev;
	if(al_get_next_event(queue, &ev)) {
		switch (ev.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
			keys_pressed[ev.keyboard.keycode] = keys_down[ev.keyboard.keycode] = true;
		break;
		case ALLEGRO_EVENT_KEY_UP:
			keys_pressed[ev.keyboard.keycode] = keys_down[ev.keyboard.keycode] = false;
		break;
		}
		event = ev;
		return true;
	}
	else {
		event = ev;
		return false;
	}
}

bool keyboard::key_down(int key) {
	if(key >= ALLEGRO_KEY_MAX || key < 0) {
		return false;
	}
	else {
		ALLEGRO_EVENT ev;
		while(poll(ev)) {
			al_rest(0.005);
		}
		return keys_down[key];
	}
}

bool keyboard::key_pressed(int key) {
	if(key >= ALLEGRO_KEY_MAX || key < 0) {
		return false;
	}
	else {
		ALLEGRO_EVENT ev;
		while(poll(ev)) {
			al_rest(0.005);
		}
		bool val = keys_pressed[key];
		keys_pressed[key] = false;
		return val;
	}
}
