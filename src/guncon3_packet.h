#ifndef GT_GUNCON3_PACKET_H_
#define GT_GUNCON3_PACKET_H_

#include <stdint.h>
#include <stdbool.h>

#define GC3_KEY_LEN     8
#define GC3_REPORT_LEN  15

typedef struct {
    uint16_t x;
    uint16_t y;
    bool trigger;
    bool reload;
    bool start;
    bool coin;
    bool btn_a;
    bool btn_c;
} gc3_input_t;

void gc3_set_key(const uint8_t key[GC3_KEY_LEN]);
void gc3_build_report(const gc3_input_t *in, uint8_t out[GC3_REPORT_LEN]);

#endif
