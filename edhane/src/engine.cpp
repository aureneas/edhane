#include <cstdlib>
#include <cmath>
#include <string>
#include <functional>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

#include "../include/state.h"


ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* event_timer;


void show_error_message(std::string header, std::string body) {
    long long code = static_cast<long long>(std::hash<std::string>{}(header+body));
    char strcode[9];
    long long hshr = 0x10000000;
    for (int i = 0; i < 8; i++) {
        int j = static_cast<int>(code/hshr);
        strcode[i] = (char)(j > 9 ? j+55 : j+48);
        hshr = hshr/0x10;
    }
    strcode[8] = '\0';
    std::string title("Error code: 0x");
    title.append(strcode);

    al_show_native_message_box(display, title.data(), header.data(), body.data(),
                               NULL, ALLEGRO_MESSAGEBOX_ERROR);
}


void init(State* s) {
    display = NULL;
    event_queue = NULL;
    event_timer = NULL;

    if (!al_init()) {
        throw std::string("Allegro library failed to initialize.");
    }

    if (!al_install_mouse()) {
        throw std::string("Allegro mouse addon failed to initialize.");
    }

    if (!al_install_keyboard()) {
        throw std::string("Allegro keyboard addon failed to initialize.");
    }

    if (!al_init_image_addon()) {
        throw std::string("Allegro image addon failed to initialize.");
    }

    if (!al_init_font_addon()) {
        throw std::string("Allegro font addon failed to initialize.");
    }

    if (!al_init_ttf_addon()) {
        throw std::string("Allegro ttf addon failed to initialize.");
    }

    event_timer = al_create_timer(1.0/30);
    if (!event_timer) {
        throw std::string("Allegro timer failed to initialize.");
    }

    display = al_create_display(640, 400);
    if (!display) {
        throw std::string("Allegro display failed to initialize.");
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        throw std::string("Allegro event queue failed to initialize.");
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(event_timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_hide_mouse_cursor(display);
}

void run(State* s) {
    al_start_timer(event_timer);

    ALLEGRO_EVENT* e;
    RunResult result = RunResult::CONTINUE;
    while (result >= RunResult::CONTINUE) {
        al_wait_for_event(event_queue, e);
        if (e->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return;
        } else {
            result = s->run(e);
        }
    }
    return;
}
