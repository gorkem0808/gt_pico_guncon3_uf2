#ifndef GT_TUSB_CONFIG_H_
#define GT_TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CFG_TUSB_MCU
#error CFG_TUSB_MCU must be defined by Pico SDK
#endif

#define CFG_TUSB_RHPORT0_MODE       (OPT_MODE_DEVICE)
#define CFG_TUD_ENDPOINT0_SIZE      64

#define CFG_TUD_CDC                 0
#define CFG_TUD_MSC                 0
#define CFG_TUD_HID                 0
#define CFG_TUD_MIDI                0
#define CFG_TUD_VENDOR              1

// Gerçek GunCon3 raporu 15 byte, init/key paketi 8 byte.
// Endpoint packet size 64 tutuluyor; firmware 15 byte gönderiyor.
#define CFG_TUD_VENDOR_EPSIZE       64

#ifdef __cplusplus
}
#endif

#endif
