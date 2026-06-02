#include "tusb.h"
#include <string.h>

// GunCon3 USB kimliği.
// UYARI: Bu VID/PID kişisel test içindir; ticari cihazda kendi VID/PID kullanılmalıdır.
#define USB_VID_NAMCO_GUNCON3  0x0B9A
#define USB_PID_GUNCON3        0x0800

#define EPNUM_GC3_OUT          0x02
#define EPNUM_GC3_IN           0x82

enum {
    ITF_NUM_VENDOR = 0,
    ITF_NUM_TOTAL
};

tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,

    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,

    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = USB_VID_NAMCO_GUNCON3,
    .idProduct          = USB_PID_GUNCON3,
    .bcdDevice          = 0x0100,

    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,

    .bNumConfigurations = 0x01
};

uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

#define GC3_VENDOR_DESC_LEN  (TUD_INTERFACE_DESC_LEN + 2 * TUD_ENDPOINT_DESC_LEN)
#define CONFIG_TOTAL_LEN      (TUD_CONFIG_DESC_LEN + GC3_VENDOR_DESC_LEN)

uint8_t const desc_configuration[] = {
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),

    // Vendor Specific interface, iki interrupt endpoint: OUT 0x02, IN 0x82.
    TUD_INTERFACE_DESCRIPTOR(ITF_NUM_VENDOR, 0, 2, TUSB_CLASS_VENDOR_SPECIFIC, 0x00, 0x00, 0),
    TUD_ENDPOINT_DESCRIPTOR(EPNUM_GC3_OUT, TUSB_XFER_INTERRUPT, 8, 1),
    TUD_ENDPOINT_DESCRIPTOR(EPNUM_GC3_IN,  TUSB_XFER_INTERRUPT, 15, 1),
};

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void) index;
    return desc_configuration;
}

char const *string_desc_arr[] = {
    (const char[]) { 0x09, 0x04 }, // 0: English
    "NAMCO",
    "GunCon3",
    "GT-PICO-GC3-0001",
};

static uint16_t _desc_str[32];

uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void) langid;

    uint8_t chr_count;

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    } else {
        if (index >= sizeof(string_desc_arr) / sizeof(string_desc_arr[0])) return NULL;
        const char *str = string_desc_arr[index];
        chr_count = (uint8_t) strlen(str);
        if (chr_count > 31) chr_count = 31;

        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
    }

    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);
    return _desc_str;
}
