#include <stdio.h>

#include "vladlib/vladlib.h"

#include "game.h"

int main(void) {
    const uint16_t screen_width  = 640;
    const uint16_t screen_height = 640;
    vl_init_lib(screen_width, screen_height, "VLAD");

    game_run(screen_width, screen_height);

    vl_deinit_lib();
    return 0;
}