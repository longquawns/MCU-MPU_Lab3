#include "fsm_automatic.h"
#include "fsm_setting.h"
#include "led_display.h"
#include "timer.h"
#include "main.h"

#define INIT 0
#define RUN  1

typedef enum { A_PHASE_RED, A_PHASE_GREEN, A_PHASE_AMBER } RoadAPhase;
typedef enum { B_PHASE_GREEN, B_PHASE_AMBER, B_PHASE_RED } RoadBPhase;

int auto_state = INIT;

static RoadAPhase phase_A;
static RoadBPhase phase_B;
static int time_A;
static int time_B;

static int valid_duration(int value) {
    if (value < 1) return 1;
    if (value > 99) return 99;
    return value;
}

static void load_display_buffers(void) {
    led_buffer_A[0] = time_A / 10;
    led_buffer_A[1] = time_A % 10;
    led_buffer_B[0] = time_B / 10;
    led_buffer_B[1] = time_B % 10;
}

static void apply_traffic_outputs(void) {
    clearAllLEDs();

    switch (phase_A) {
        case A_PHASE_RED:
            HAL_GPIO_WritePin(A_RED_GPIO_Port, A_RED_Pin, GPIO_PIN_RESET);
            break;
        case A_PHASE_GREEN:
            HAL_GPIO_WritePin(A_GREEN_GPIO_Port, A_GREEN_Pin, GPIO_PIN_RESET);
            break;
        case A_PHASE_AMBER:
            HAL_GPIO_WritePin(A_AMBER_GPIO_Port, A_AMBER_Pin, GPIO_PIN_RESET);
            break;
    }

    switch (phase_B) {
        case B_PHASE_GREEN:
            HAL_GPIO_WritePin(B_GREEN_GPIO_Port, B_GREEN_Pin, GPIO_PIN_RESET);
            break;
        case B_PHASE_AMBER:
            HAL_GPIO_WritePin(B_AMBER_GPIO_Port, B_AMBER_Pin, GPIO_PIN_RESET);
            break;
        case B_PHASE_RED:
            HAL_GPIO_WritePin(B_RED_GPIO_Port, B_RED_Pin, GPIO_PIN_RESET);
            break;
    }
}

static void advance_road_A(void) {
    if (time_A > 1) {
        time_A--;
        return;
    }

    switch (phase_A) {
        case A_PHASE_RED:
            phase_A = A_PHASE_GREEN;
            time_A = valid_duration(green_duration);
            break;
        case A_PHASE_GREEN:
            phase_A = A_PHASE_AMBER;
            time_A = valid_duration(amber_duration);
            break;
        case A_PHASE_AMBER:
        default:
            phase_A = A_PHASE_RED;
            time_A = valid_duration(red_duration);
            break;
    }
}

static void advance_road_B(void) {
    if (time_B > 1) {
        time_B--;
        return;
    }

    switch (phase_B) {
        case B_PHASE_GREEN:
            phase_B = B_PHASE_AMBER;
            time_B = valid_duration(amber_duration);
            break;
        case B_PHASE_AMBER:
            phase_B = B_PHASE_RED;
            time_B = valid_duration(red_duration);
            break;
        case B_PHASE_RED:
        default:
            phase_B = B_PHASE_GREEN;
            time_B = valid_duration(green_duration);
            break;
    }
}

void fsm_automatic_run(void) {
    if (auto_state == INIT) {
        phase_A = A_PHASE_RED;
        phase_B = B_PHASE_GREEN;
        time_A = valid_duration(red_duration);
        time_B = valid_duration(green_duration);

        apply_traffic_outputs();
        load_display_buffers();
        setTimer1(1000);
        auto_state = RUN;
        return;
    }

    if (timer1_flag == 1) {
        advance_road_A();
        advance_road_B();
        apply_traffic_outputs();
        load_display_buffers();
        setTimer1(1000);
    }
}
