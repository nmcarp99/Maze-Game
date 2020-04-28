#include "functions.h"

int main()
{
	initializeAllegro();
	loadBitmaps();
	setupSound();
	setupTimer();
	// create event queue
	event_queue = al_create_event_queue();
	setupDisplay();
	registerEventSources();
	// create map positioning
	getLevelPositioning();
	al_play_sample_instance(mainIntroInstance);

	bool running = true;
	bool introDone = false;

	while (running)
	{
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_KEYBOARD_STATE keyboard;

		al_init_timeout(&timeout, FPS);
		al_get_keyboard_state(&keyboard);

		if (!introDone) {
			if (!al_get_sample_instance_playing(mainIntroInstance)) {
				introDone = true;
				al_play_sample_instance(mainLoopInstance);
			}
		}

		checkKeys(keyboard);

		if (playerPos != 224) {
			al_wait_for_event_until(event_queue, &event, &timeout);

			switch (event.type)
			{
			case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
				checkJoystick(event);
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				running = false;
				break;
			case ALLEGRO_EVENT_TIMER:
				draw();
				break;
			}
		}
		else {
			al_stop_sample_instance(mainLoopInstance);
			al_stop_sample_instance(mainIntroInstance);
			al_play_sample_instance(finishedNoiseInstance);
			while (al_get_sample_instance_playing(finishedNoiseInstance)) {}
			return 0;
		}
	}
}