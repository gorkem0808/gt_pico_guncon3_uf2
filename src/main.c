#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "bsp/board.h"
#include "tusb.h"

#include "pins.h"
#include "guncon3_packet.h"

static void button_init(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

static bool button_pressed(uint pin) {
    return gpio_get(pin) == 0;
}

static void io_init(void) {
    adc_init();
    adc_gpio_init(PIN_X_ADC);
    adc_gpio_init(PIN_Y_ADC);

    button_init(PIN_TRIGGER);
    button_init(PIN_RELOAD);
    button_init(PIN_START);
    button_init(PIN_COIN);
    button_init(PIN_BTN_A);
    button_init(PIN_BTN_C);

    board_init();
}

static uint16_t read_adc_channel(uint channel) {
    adc_select_input(channel);
    sleep_us(10);
    return adc_read();
}

int main(void) {
    io_init();
    tusb_init();

    uint8_t key_buf[GC3_KEY_LEN];
    uint8_t report[GC3_REPORT_LEN];
    absolute_time_t next_report = make_timeout_time_ms(5);

    while (true) {
        tud_task();

        // Host/RPCS3 8 byte key gönderirse al.
        while (tud_vendor_available() >= GC3_KEY_LEN) {
            uint32_t n = tud_vendor_read(key_buf, GC3_KEY_LEN);
            if (n == GC3_KEY_LEN) {
                gc3_set_key(key_buf);
            }
        }

        // Yaklaşık 200 Hz rapor gönder.
        if (absolute_time_diff_us(get_absolute_time(), next_report) <= 0) {
            next_report = make_timeout_time_ms(5);

            gc3_input_t in = {
                .x = read_adc_channel(0),
                .y = read_adc_channel(1),
                .trigger = button_pressed(PIN_TRIGGER),
                .reload  = button_pressed(PIN_RELOAD),
                .start   = button_pressed(PIN_START),
                .coin    = button_pressed(PIN_COIN),
                .btn_a   = button_pressed(PIN_BTN_A),
                .btn_c   = button_pressed(PIN_BTN_C),
            };

            gc3_build_report(&in, report);

            if (tud_vendor_mounted()) {
                tud_vendor_write(report, GC3_REPORT_LEN);
                tud_vendor_flush();
            }
        }
    }
}
