#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

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

// samples and sample instances
ALLEGRO_SAMPLE* mainIntro = NULL;
ALLEGRO_SAMPLE* mainLoop = NULL;
ALLEGRO_SAMPLE* finishedNoise = NULL;

ALLEGRO_SAMPLE_INSTANCE* mainIntroInstance = NULL;
ALLEGRO_SAMPLE_INSTANCE* mainLoopInstance = NULL;
ALLEGRO_SAMPLE_INSTANCE* finishedNoiseInstance = NULL;

// keys
bool key_up = false;
bool key_down = false;
bool key_right = false;
bool key_left = false;

const float FPS = 1.0 / 60;
int levelWidthPosition[225] = {};
int levelHeightPosition[225] = {};

int level[] = {
	6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
	1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1,
	1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1,
	0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
};

int playerPos = 0;

int getLevelPositioning()
{
	for (int i = 0; i < 225; i++) {
		levelWidthPosition[i] = ((i % 15) * 50) - (((i - (i % 15)) / 15) * 25) + 197.5 + ((1080 / 2) - 387.5);
		levelHeightPosition[i] = (((i - (i % 15)) / 15) * 25) + 160 + ((640 / 2) - 292.5);
	}
	return 0;
}

int draw()
{
	al_clear_to_color(al_map_rgb(255, 0, 0));
	for (int i = 0; i < 225; ++i) {
		al_draw_bitmap(greenBlock, levelWidthPosition[i], levelHeightPosition[i] + 50, 0);
	}
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

int checkJoystick(ALLEGRO_EVENT event)
{
	switch (event.joystick.button) {
	case 11: // left
		if (level[playerPos - 1] == 0 && playerPos - 1 >= 0) {
			level[playerPos - 1] = 6;
			level[playerPos] = 0;
			playerPos -= 1;
		}
		break;
	case 12: // down
		if (level[playerPos + 15] == 0 && playerPos + 15 <= 224) {
			level[playerPos + 15] = 6;
			level[playerPos] = 0;
			playerPos += 15;
		}
		break;
	case 13: // up
		if (level[playerPos - 15] == 0 && playerPos - 15 >= 0) {
			level[playerPos - 15] = 6;
			level[playerPos] = 0;
			playerPos -= 15;
		}
		break;
	case 10: // right
		if (level[playerPos + 1] == 0 && playerPos + 1 <= 224) {
			level[playerPos + 1] = 6;
			level[playerPos] = 0;
			playerPos += 1;
		}
		break;
	case 0:
		playerPos = playerPos;
		break;
	}
	return 0;
}

int checkKeys(ALLEGRO_KEYBOARD_STATE state)
{
	if (al_key_down(&state, ALLEGRO_KEY_RIGHT)) {
		if (key_right == false) {
			key_right = true;
		}
	}
	else if (key_right == true) {
		key_right = false;
		if (level[playerPos + 1] == 0 && playerPos + 1 <= 224) {
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
		if (level[playerPos + 15] == 0 && playerPos + 15 <= 224) {
			level[playerPos + 15] = 6;
			level[playerPos] = 0;
			playerPos += 15;
		}
	}
	return 0;
}

int initializeAllegro()
{
	// initialize allegro
	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_install_joystick();
	al_init_acodec_addon();
	al_install_audio();
	return 0;
}

int loadBitmaps()
{
	// load bitmaps
	icon = al_load_bitmap("icon.jpg");
	redBlock = al_load_bitmap("redBlock.png");
	greenBlock = al_load_bitmap("greenBlock.png");
	blueBlock = al_load_bitmap("blueBlock.png");
	yellowBlock = al_load_bitmap("yellowBlock.png");
	moveBlock = al_load_bitmap("moveBlock.png");
	mazePlayer = al_load_bitmap("mazePlayer.png");
	return 0;
}

int setupSound()
{
	// sound
	al_reserve_samples(3);
	mainIntro = al_load_sample("mainIntro.wav");
	mainLoop = al_load_sample("mainLoop.wav");
	finishedNoise = al_load_sample("finishedNoise.wav");

	mainIntroInstance = al_create_sample_instance(mainIntro);
	mainLoopInstance = al_create_sample_instance(mainLoop);
	finishedNoiseInstance = al_create_sample_instance(finishedNoise);

	al_attach_sample_instance_to_mixer(mainIntroInstance, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(mainLoopInstance, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(finishedNoiseInstance, al_get_default_mixer());

	al_set_sample_instance_playmode(mainLoopInstance, ALLEGRO_PLAYMODE_LOOP);
	return 0;
}

int setupTimer()
{
	// timer
	timer = al_create_timer(FPS);
	al_start_timer(timer);
	return 0;
}

int setupDisplay()
{
	// create allegro display
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	display = al_create_display(1125, 640);
	al_set_window_title(display, "Maze Game");
	al_set_display_icon(display, icon);
	return 0;
}

int registerEventSources()
{
	// register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_joystick_event_source());
	return 0;
}