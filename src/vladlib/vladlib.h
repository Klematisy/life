#pragma once

#include "deps/include/GL/glew.h"
#include "deps/include/GLFW/glfw3.h"

#include <stdint.h>

//-----------OpenGL_abstraction-----------//
#include "utils/shaders.h"
#include "utils/vertex_buffer_object.h"
#include "utils/vertex_array_object.h"
#include "utils/index_buffer_obj.h"
//----------------------------------------//

#define nullptr NULL

typedef int bool;
#define true  1
#define false 0

typedef GLFWwindow* MAIN_LIB_WINDOW;

typedef struct ObjectOfData {
    uint32_t vao;
    uint32_t shader_program;
} ObjectOfData;

typedef struct VL_Color {
    float r;
    float g;
    float b;
} VL_Color;

typedef struct VL_ColorAlpha {
    float r;
    float g;
    float b;
    float a;
} VL_ColorAlpha;

typedef struct VL_Rect {
    float x;
    float y;
    float width;
    float height;

    VL_Color color;
} VL_Rect;

typedef struct Object2 {
    float x;
    float y;
} Object2;

// UTILS
void BindObjectOfData(const ObjectOfData *ood);

// INIT LIB
void* vl_init_lib(const uint16_t width, const uint16_t height, const char* window_name);
void  vl_deinit_lib(void);
bool  vl_window_open(void);

// INIT DRAW
void vl_draw(void);
void vl_end_draw(void);

// DRAW FUNCTIONS
void vl_draw_rect(VL_Rect *rect);

// INPUT KEYBOARD FUNCTIONS
bool vl_left_pressed(void);
bool vl_up_pressed(void);
bool vl_down_pressed(void);
bool vl_right_pressed(void);
bool vl_lshift_pressed(void);
bool vl_rshift_pressed(void);
bool vl_equal_pressed(void);
bool vl_plus_pressed(void);
bool vl_minus_pressed(void);
bool vl_esc_pressed(void);
bool vl_space_pressed(void);
bool vl_e_pressed(void);

// INPUT MOUSE FUNCTIONS
bool vl_mouse_left_pressed(void);
bool vl_mouse_right_pressed(void);
Object2 vl_get_cursor_pos(void);
void vl_set_cursor_pos(Object2 position);