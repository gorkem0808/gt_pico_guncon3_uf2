#include "guncon3_packet.h"
#include <string.h>

// İlk GitHub sürümü: USB descriptor + endpoint testi için çalışır.
// Bu dosyada paket boyutu ve X/Y alanları hazırlanır.
// Sonraki sürümde gerçek GunCon3 key/checksum/encode algoritması buraya eklenecek.
// Kaynak araştırma notu: Beardypig GunCon3 Linux sürücüsü 8 byte key, 15 byte rapor,
// X=data[3..4], Y=data[5..6] ve button bitlerini ters mühendislik etmişti.

static uint8_t g_key[GC3_KEY_LEN] = {0x01, 0x12, 0x6F, 0x32, 0x24, 0x60, 0x17, 0x21};

void gc3_set_key(const uint8_t key[GC3_KEY_LEN]) {
    memcpy(g_key, key, GC3_KEY_LEN);
}

static uint16_t adc12_to_gc3(uint16_t adc) {
    // 0..4095 ADC değerini yaklaşık 0..65535 GunCon3 eksen değerine çevir.
    return (uint16_t)((uint32_t)adc * 65535u / 4095u);
}

void gc3_build_report(const gc3_input_t *in, uint8_t out[GC3_REPORT_LEN]) {
    memset(out, 0, GC3_REPORT_LEN);

    uint16_t x = adc12_to_gc3(in->x);
    uint16_t y = adc12_to_gc3(in->y);

    // NOT: Bu alan düzeni, decode sonrası düz veri düzenidir.
    // V1 enumerasyon/test içindir. RPCS3 oyun içi tam uyum için encode/checksum eklenecek.
    if (in->btn_a)   out[0] |= 0x04;
    if (in->btn_c)   out[1] |= 0x80;
    if (in->trigger) out[1] |= 0x20;
    if (in->reload)  out[1] |= 0x04;
    if (in->start)   out[2] |= 0x80;
    if (in->coin)    out[2] |= 0x40;

    out[3] = (uint8_t)(x & 0xFF);
    out[4] = (uint8_t)(x >> 8);
    out[5] = (uint8_t)(y & 0xFF);
    out[6] = (uint8_t)(y >> 8);

    // Joystick değerleri merkezde.
    out[9]  = 127;
    out[10] = 127;
    out[11] = 127;
    out[12] = 127;

    // Key'i tamamen atmayalım; testte paket değişimini görmek için son iki bayta koyuyoruz.
    // Tam encode sürümünde out[13] checksum, out[14] offset/key alanı olarak kullanılacak.
    out[13] = g_key[7];
    out[14] = 0x00;
}
