#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>

#include "vladlib/vladlib.h"

#include "game.h"

/* MAIN GAME VARIABLES */
static uint32_t *game_field;
static uint32_t field_width;
static uint32_t field_height;

static bool game_is_running;
static bool life_is_running;

static struct timeval fps_start, fps_end;

float velocity = 1.0f;
/* MAIN GAME VARIABLES */

static void game_end() {
    if (vl_esc_pressed()) {
        game_is_running = false;
    }
}

static void enable_cell(const uint16_t screen_width, const uint16_t screen_height) {
    if (vl_mouse_left_pressed()) {
        Object2 obj = vl_get_cursor_pos();
        uint32_t x = (uint32_t) obj.x;
        uint32_t y = (uint32_t) obj.y;

        uint32_t fragmentation_x = screen_width  / field_width;
        uint32_t fragmentation_y = screen_height / field_height;

        uint32_t element = (int)(x / fragmentation_x) + (int)(y / fragmentation_y) * field_width;

        game_field[element] = (game_field[element] == 0) ? 1 : 0;
        usleep(150000);
    }
}

static void check_rules(uint16_t neighbours, const uint32_t *arr, uint32_t element) {
    if (neighbours < 2 && arr[element]) {
        game_field[element] = 0;
    } else if (neighbours == 3 && arr[element] == 0) {
        game_field[element] = 1;
    } else if (3 < neighbours && arr[element]) {
        game_field[element] = 0;
    }
}

static bool fps(float frames) {
    float elapsed_time = (fps_end.tv_sec - fps_start.tv_sec) +
                         (fps_end.tv_usec - fps_start.tv_usec) / 1e6;
    gettimeofday(&fps_end, NULL);

    if (1.0f / frames < elapsed_time) {
        gettimeofday(&fps_start, NULL);
        return true;
    }
    return false;
}

static void time_gap() {
    if (vl_plus_pressed()) {
        velocity *= 2.0f;
        usleep(200000);
    }

    if (vl_minus_pressed()) {
        velocity /= 2;
        usleep(200000);
    }
}

static void life_run() {
    uint32_t new_arr[field_width * field_height];

    for (uint32_t i = 0; i < field_height; i++) {
        for (uint32_t j = 0; j < field_width; j++) {
            new_arr[j + i * field_width] = game_field[j + i * field_width];
        }
    }

    for (uint32_t i = 0; i < field_height; i++) {
        for (uint32_t j = 0; j < field_width; j++) {
            uint16_t neighbours = 0;
            for (int m = -1; m <= 1; m++) {
                for (int n = -1; n <= 1; n++) {
                    if (!(m == 0 && n == 0) && 0 <= (i + m) && (i + m) < field_height && 0 <= (j + n) && (j + n) < field_width) {
                        uint32_t element = ((i + m) * field_width) + j + n;
                        if (new_arr[element] == 1) {
                            neighbours++;
                        }
                    }
                }
            }
            check_rules(neighbours, new_arr, i * field_width + j);
        }
    }
}

void game_update(const uint16_t screen_width, const uint16_t screen_height) {
    game_end();
    enable_cell(screen_width, screen_height);


    if (vl_space_pressed()) {
        life_is_running = !life_is_running;
        usleep(200000);
    }

    if (life_is_running && fps(velocity)) {
        life_run();
    }
    time_gap();
}

void game_draw(void) {
    vl_draw_rect(&(VL_Rect){0.0f, 0.0f, 1.0f, 1.0f, (VL_Color) {1.0f, 1.0f, 1.0f}});
    for (uint32_t i = 0; i < field_height; i++) {
        for (uint32_t j = 0; j < field_width; j++) {
            int element = i * field_width + j;
            if (game_field[element] == 1) {
                VL_Rect rect = {j * 1.0f / field_width, i * 1.0f / field_height, 1.0f / field_width, 1.0f/ field_height, (VL_Color) {0.0f, 0.0f, 0.0f}};
                vl_draw_rect(&rect);
            }
        }
    }
}

void game_init(void) {
    field_width  = 40;
    field_height = 40;
    game_field = (uint32_t*) malloc(sizeof(uint32_t) * field_width * field_height);

    for (uint32_t i = 0; i < field_height; i++) {
        for (uint32_t j = 0; j < field_width; j++) {
            game_field[i * field_width + j] = 0;
        }
    }

    velocity = 0.5f;

    game_is_running = true;
}

void game_deinit(void) {
    free(game_field);
}

void game_run(const uint16_t screen_width, const uint16_t screen_height) {
    game_init();

    while (vl_window_open() && game_is_running) {
        game_update(screen_width, screen_height);
        vl_draw();
            game_draw();
        vl_end_draw();
    }

    game_deinit();
}