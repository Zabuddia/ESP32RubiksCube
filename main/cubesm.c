#include "cubesm.h"

static RubiksCube rubiks_cube;

static int32_t dcx, dcy;

enum cubesm_states {
    CUBE_INIT,
    CUBE_A,
    CUBE_B,
    CUBE_START,
    CUBE_SELECT,
    CUBE_UP,
    CUBE_RIGHT,
    CUBE_DOWN,
    CUBE_LEFT,
    CUBE_FRONT,
    CUBE_FRONT2,
    CUBE_WAITING
} cubesm_state;

void cube_init() {
    resetcube(&rubiks_cube);
    cubesm_state = CUBE_INIT;
}

void cube_tick() {
    // Transitions
    switch (cubesm_state) {
        case CUBE_INIT:
            if (!pin_get_level(BTN_A)) {
                cubesm_state = CUBE_A;
            } else if (!pin_get_level(BTN_B)) {
                cubesm_state = CUBE_B;
            } else if (!pin_get_level(BTN_START)) {
                cubesm_state = CUBE_START;
            } else if (!pin_get_level(BTN_SELECT)) {
                cubesm_state = CUBE_SELECT;
            } else if (dcy < -200) {
                cubesm_state = CUBE_UP;
            } else if (dcx > 200) {
                cubesm_state = CUBE_RIGHT;
            } else if (dcy > 200) {
                cubesm_state = CUBE_DOWN;
            } else if (dcx < -200) {
                cubesm_state = CUBE_LEFT;
            } else if (!pin_get_level(BTN_OPTION)) {
                cubesm_state = CUBE_FRONT;
            } else if (!pin_get_level(BTN_MENU)) {
                cubesm_state = CUBE_FRONT2;
            }
            break;
        case CUBE_A:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_B:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_START:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_SELECT:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_UP:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_RIGHT:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_DOWN:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_LEFT:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_FRONT:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_FRONT2:
            cubesm_state = CUBE_WAITING;
            break;
        case CUBE_WAITING:
            if (pin_get_level(BTN_A) && pin_get_level(BTN_B) && pin_get_level(BTN_START) && pin_get_level(BTN_SELECT) && pin_get_level(BTN_OPTION) && pin_get_level(BTN_MENU) && (-200 < dcx) && (200 > dcx) && (-200 < dcy) && (200 > dcy)) {
                cubesm_state = CUBE_INIT;
            }
            break;
    }

    // Actions
    switch (cubesm_state) {
        case CUBE_INIT:
            joy_get_displacement(&dcx, &dcy);
            break;
        case CUBE_A:
            X(&rubiks_cube);
            break;
        case CUBE_B:
            Xi(&rubiks_cube);
            break;
        case CUBE_START:
            Yi(&rubiks_cube);
            break;
        case CUBE_SELECT:
            Y(&rubiks_cube);
            break;
        case CUBE_UP:
            R(&rubiks_cube);
            break;
        case CUBE_RIGHT:
            Ui(&rubiks_cube);
            break;
        case CUBE_DOWN:
            Ri(&rubiks_cube);
            break;
        case CUBE_LEFT:
            U(&rubiks_cube);
            break;
        case CUBE_FRONT:
            F(&rubiks_cube);
            break;
        case CUBE_FRONT2:
            Fi(&rubiks_cube);
            break;
        case CUBE_WAITING:
            joy_get_displacement(&dcx, &dcy);
            break;
    }
    display_draw_rubiks_cube(rubiks_cube);
}