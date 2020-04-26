#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;

// allegro bitmaps
ALLEGRO_BITMAP* icon = NULL;
ALLEGRO_BITMAP* greenBlock = NULL;
ALLEGRO_BITMAP* redBlock = NULL;
ALLEGRO_BITMAP* yellowBlock = NULL;
ALLEGRO_BITMAP* blueBlock = NULL;

const int FPS = 1 / 1;

int level[] = {
	1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3,
	2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4,
	3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1,
	4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2
};

int draw() {
	al_clear_to_color(al_map_rgb(255, 0, 0));
	for (int i = 0; i < sizeof(level)/sizeof(level[0]); ++i) {
		if (level[i] == 1) {
			al_draw_bitmap(greenBlock, ((i % 15) * 50) - (((i - (i % 15)) / 15) * 25) + 140, (((i - (i % 15)) / 15) * 25)+10, 0);
		}
		else if (level[i] == 2) {
			al_draw_bitmap(redBlock, ((i % 15) * 50) - (((i - (i % 15)) / 15) * 25) + 140, (((i - (i % 15)) / 15) * 25) + 10, 0);
		}
		else if (level[i] == 3) {
			al_draw_bitmap(yellowBlock, ((i % 15) * 50) - (((i - (i % 15)) / 15) * 25) + 140, (((i - (i % 15)) / 15) * 25) + 10, 0);
		}
		else if (level[i] == 4) {
			al_draw_bitmap(blueBlock, ((i % 15) * 50) - (((i - (i % 15)) / 15) * 25) + 140, (((i - (i % 15)) / 15) * 25) + 10, 0);
		}
	}
	al_flip_display();
	return 0;
}

int main()
{
	// initialize allegro
	al_init();
	al_init_image_addon();

	// load bitmaps
	icon = al_load_bitmap("icon.jpg");
	greenBlock = al_load_bitmap("greenBlock.png");
	redBlock = al_load_bitmap("redBlock.png");
	yellowBlock = al_load_bitmap("yellowBlock.png");
	blueBlock = al_load_bitmap("blueBlock.png");

	// timer
	timer = al_create_timer(FPS);
	al_start_timer(timer);

	// create event queue
	event_queue = al_create_event_queue();

	// create allegro display
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	display = al_create_display(1080, 640);
	al_set_window_title(display, "Maze Game");
	al_set_display_icon(display, icon);

	// register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	bool running = true;

	while (running)
	{
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;

		al_init_timeout(&timeout, FPS);
		al_wait_for_event_until(event_queue, &event, &timeout);

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