//keyboard.h
//By Michael Taboada
//Provided under the unlicense
//see UNLICENSE for details
#include <allegro5/allegro5.h>


#pragma once
class keyboard
{
public:
	keyboard(void);
	~keyboard(void);
	bool poll(ALLEGRO_EVENT& event);
	bool key_down(int key);
	bool key_pressed(int key);
private:
	bool* keys_down;
	bool* keys_pressed;
	ALLEGRO_EVENT_QUEUE* queue;
};

