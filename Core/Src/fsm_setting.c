#include "fsm_setting.h"
#include "input_reading.h"
#include "led_display.h"
#include "timer.h"
#include "main.h"
#include "fsm_automatic.h"
int traffic_mode = 1;

// Các biến lưu trữ thời gian của 3 loại đèn
int red_duration = 5;
int amber_duration = 2; // Bổ sung cho Bài 8
int green_duration = 3; // Bổ sung cho Bài 9
int temp_duration = 0;  // Biến tạm để tăng/giảm khi đang ở Mode cài đặt

// Các biến lưu trạng thái để bắt xung cạnh (tránh tăng liên tục khi giữ đè nút)
uint8_t prev_btn1 = 0, prev_btn2 = 0, prev_btn3 = 0;

void fsm_mode_processing(void) {
    uint8_t curr_btn1 = is_button_pressed(0); // Button 1 - Chuyển Mode
    uint8_t curr_btn2 = is_button_pressed(1); // Button 2 - Tăng giá trị
    uint8_t curr_btn3 = is_button_pressed(2); // Button 3 - Xác nhận lưu

    // ---------------- LOGIC CHUYỂN MODE (NÚT 1) ----------------
    if (curr_btn1 == 1 && prev_btn1 == 0) {
            traffic_mode++;
            if (traffic_mode > 4) {
                traffic_mode = 1;
                auto_state = 0; // Ép trạng thái về INIT để tải lại thời gian đếm ngược mới nhất
            }

            clearAllLEDs();
            if (traffic_mode == 2) temp_duration = red_duration;
            else if (traffic_mode == 3) temp_duration = amber_duration;
            else if (traffic_mode == 4) temp_duration = green_duration;
        }
        prev_btn1 = curr_btn1;

    // ---------------- LOGIC TĂNG GIÁ TRỊ (NÚT 2) DÙNG CHUNG ----------------
    if (traffic_mode >= 2 && traffic_mode <= 4) {
        if (curr_btn2 == 1 && prev_btn2 == 0) {
            temp_duration++;
            if (temp_duration > 99) temp_duration = 1;
        }
    }
    prev_btn2 = curr_btn2;

    // ---------------- LOGIC XỬ LÝ THEO TỪNG MODE ----------------
    switch (traffic_mode) {
        case 1: // Mode 1: Hoạt động bình thường
        	fsm_automatic_run(); // Gọi hàm tự động đếm ngược
        	            break;

        case 2: // Bài 7: Chỉnh đèn Đỏ (Mode 2)
            led_buffer_A[0] = temp_duration / 10;
            led_buffer_A[1] = temp_duration % 10;
            led_buffer_B[0] = 0;
            led_buffer_B[1] = 2; // Hiện Mode 02

            // Nháy 4 đèn Đỏ ở tần số 2Hz (Chu kỳ 500ms -> Toggle mỗi 250ms)
            if (timer3_flag == 1) {
                HAL_GPIO_TogglePin(GPIOA, A_RED_Pin | B_RED_Pin);
                setTimer3(250);
            }

            // Nút 3: Lưu giá trị
            if (curr_btn3 == 1 && prev_btn3 == 0) {
                red_duration = temp_duration;
            }
            break;

        case 3: // Bài 8: Chỉnh đèn Vàng (Mode 3)
            led_buffer_A[0] = temp_duration / 10;
            led_buffer_A[1] = temp_duration % 10;
            led_buffer_B[0] = 0;
            led_buffer_B[1] = 3; // Hiện Mode 03

            // Nháy 4 đèn Vàng
            if (timer3_flag == 1) {
                HAL_GPIO_TogglePin(GPIOA, A_AMBER_Pin | B_AMBER_Pin);
                setTimer3(250);
            }

            // Nút 3: Lưu giá trị
            if (curr_btn3 == 1 && prev_btn3 == 0) {
                amber_duration = temp_duration;
            }
            break;

        case 4: // Bài 9: Chỉnh đèn Xanh (Mode 4)
            led_buffer_A[0] = temp_duration / 10;
            led_buffer_A[1] = temp_duration % 10;
            led_buffer_B[0] = 0;
            led_buffer_B[1] = 4; // Hiện Mode 04

            // Nháy 4 đèn Xanh
            if (timer3_flag == 1) {
                HAL_GPIO_TogglePin(GPIOA, A_GREEN_Pin | B_GREEN_Pin);
                setTimer3(250);
            }

            // Nút 3: Lưu giá trị
            if (curr_btn3 == 1 && prev_btn3 == 0) {
                green_duration = temp_duration;
            }
            break;
    }

    prev_btn3 = curr_btn3; // Cập nhật trạng thái Nút 3
}
