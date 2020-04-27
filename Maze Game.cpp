#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;

// allegro bitmaps
ALLEGRO_BITMAP* icon = NULL;
ALLEGRO_BITMAP* redBlock = NULL;
ALLEGRO_BITMAP* greenBlock = NULL;
ALLEGRO_BITMAP* blueBlock = NULL;
ALLEGRO_BITMAP* yellowBlock = NULL;
ALLEGRO_BITMAP* moveBlock = NULL;
ALLEGRO_BITMAP* mazePlayer = NULL;

// keys
bool key_up = false;
bool key_down = false;
bool key_right = false;
bool key_left = false;

const float FPS = 1.0 / 60;
int levelWidthPosition[225] = {};
int levelHeightPosition[225] = {};

int level[] = {
	0, 0, 0, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5,
	6, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1,
	3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
	4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3,
	5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4,
	1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5,
	2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1,
	3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
	4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3,
	5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4,
	1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5,
	2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1,
	3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2,
	4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3,
	5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4
};

int playerPos = 15;

int getLevelPositioning() {
	for (int i = 0; i < 225; i++) {
		levelWidthPosition[i] = ((i % 15) * 50) - (((i - (i % 15)) / 15) * 25) + 350;
		levelHeightPosition[i] = (((i - (i % 15)) / 15) * 25) + 160;
	}
	return 0;
}

int draw() {
	al_clear_to_color(al_map_rgb(255, 0, 0));
	for (int i = 0; i < 225; ++i) {
		switch (level[i]) {
		case 1:
			al_draw_bitmap(redBlock, levelWidthPosition[i], levelHeightPosition[i], 0);
			break;
		case 2:
			al_draw_bitmap(greenBlock, levelWidthPosition[i], levelHeightPosition[i], 0);
			break;
		case 3:
			al_draw_bitmap(blueBlock, levelWidthPosition[i], levelHeightPosition[i], 0);
			break;
		case 4:
			al_draw_bitmap(yellowBlock, levelWidthPosition[i], levelHeightPosition[i], 0);
			break;
		case 5:
			al_draw_bitmap(moveBlock, levelWidthPosition[i], levelHeightPosition[i], 0);
			break;
		case 6:
			al_draw_bitmap(mazePlayer, levelWidthPosition[i], levelHeightPosition[i], 0);
			break;
		}
	}
	al_flip_display();
	return 0;
}

int checkKeys(ALLEGRO_KEYBOARD_STATE state) {
	if (al_key_down(&state, ALLEGRO_KEY_RIGHT)) {
		if (key_right == false) {
			key_right = true;
		}
	}
	else if (key_right == true) {
		key_right = false;
		if (level[playerPos + 1] == 0 && playerPos + 1 <= 254) {
			level[playerPos + 1] = 6;
			level[playerPos] = 0;
			playerPos += 1;
		}
	}

	if (al_key_down(&state, ALLEGRO_KEY_LEFT)) {
		if (key_left == false) {
			key_left = true;
		}
	}
	else if (key_left == true) {
		key_left = false;
		if (level[playerPos - 1] == 0 && playerPos - 1 >= 0) {
			level[playerPos - 1] = 6;
			level[playerPos] = 0;
			playerPos -= 1;
		}
	}

	if (al_key_down(&state, ALLEGRO_KEY_UP)) {
		if (key_up == false) {
			key_up = true;
		}
	}
	else if (key_up == true) {
		key_up = false;
		if (level[playerPos - 15] == 0 && playerPos - 15 >= 0) {
			level[playerPos - 15] = 6;
			level[playerPos] = 0;
			playerPos -= 15;
		}
	}

	if (al_key_down(&state, ALLEGRO_KEY_DOWN)) {
		if (key_down == false) {
			key_down = true;
		}
	}
	else if (key_down == true) {
		key_down = false;
		if (level[playerPos + 15] == 0 && playerPos + 15 <= 254) {
			level[playerPos + 15] = 6;
			level[playerPos] = 0;
			playerPos += 15;
		}
	}
	return 0;
}

int main()
{
	// initialize allegro
	al_init();
	al_init_image_addon();
	al_install_keyboard();

	// load bitmaps
	icon = al_load_bitmap("icon.jpg");
	redBlock = al_load_bitmap("redBlock.png");
	greenBlock = al_load_bitmap("greenBlock.png");
	blueBlock = al_load_bitmap("blueBlock.png");
	yellowBlock = al_load_bitmap("yellowBlock.png");
	moveBlock = al_load_bitmap("moveBlock.png");
	mazePlayer = al_load_bitmap("mazePlayer.png");

	// timer
	timer = al_create_timer(FPS);
	al_start_timer(timer);

	// create event queue
	event_queue = al_create_event_queue();

	// create allegro display
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	display = al_create_display(1125, 640);
	al_set_window_title(display, "Maze Game");
	al_set_display_icon(display, icon);

	// register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	// create map positioning
	getLevelPositioning();

	bool running = true;

	while (running)
	{
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		ALLEGRO_KEYBOARD_STATE state;

		al_init_timeout(&timeout, FPS);
		al_get_keyboard_state(&state);
		al_wait_for_event_until(event_queue, &event, &timeout);

		checkKeys(state);

		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			running = false;
			break;
		case ALLEGRO_EVENT_TIMER:
			draw();
			break;
		}
	}
}