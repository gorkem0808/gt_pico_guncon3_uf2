# GT Pico GunCon3 - GitHub Starter

Bu proje Raspberry Pi Pico'yu GunCon3 benzeri USB Vendor cihazı olarak göstermeyi hedefler.

## Şu anki V1 hedefi

- Pico USB descriptor: NAMCO / GunCon3
- VID: 0x0B9A
- PID: 0x0800
- Vendor Specific interface
- OUT endpoint: 0x02, interrupt, 8 byte
- IN endpoint: 0x82, interrupt, 15 byte
- Potansiyometre X/Y okuma
- Buton okuma
- GitHub Actions ile otomatik UF2 üretme

## Önemli not

Bu V1 sürüm öncelikle USB tanıtma ve RPCS3 görme testi içindir.
Oyun içinde tam çalışması için sonraki sürümde GunCon3 key/checksum/encode algoritması eklenecek.

## GitHub'da kurulum

1. GitHub hesabına gir.
2. Sağ üstten `+` > `New repository` seç.
3. Repository adı: `GT-PICO-GUNCON3`
4. `Public` veya `Private` seçebilirsin.
5. `Create repository` butonuna bas.
6. Bu klasördeki dosyaların hepsini GitHub'a yükle.
7. `Actions` sekmesine gir.
8. Workflow kendiliğinden çalışmazsa `Build Pico UF2` > `Run workflow` seç.
9. Build bitince `Artifacts` kısmından `gt_pico_guncon3_uf2` dosyasını indir.
10. Pico'nun BOOTSEL tuşuna basılı tutarak USB'ye tak.
11. İndirdiğin `.uf2` dosyasını Pico sürücüsüne sürükle.

## Pico bağlantıları

| Görev | Pico pini |
|---|---|
| X pot orta uç | GP26 / ADC0 |
| Y pot orta uç | GP27 / ADC1 |
| Pot uçları | 3.3V ve GND |
| Tetik | GP8 + GND |
| Reload / pedal | GP7 + GND |
| Start | GP19 + GND |
| Coin / yardımcı | GP18 + GND |
| A buton | GP6 + GND |
| C / Hide | GP17 + GND |

## Windows testi

1. Pico'yu normal tak.
2. Aygıt Yöneticisi'ni aç.
3. Cihaz ayrıntılarında `VID_0B9A&PID_0800` görünmeli.
4. RPCS3 USB Devices tarafında GunCon3 olarak test edilir.

## Lisans notu

Bu starter kodu test amaçlıdır. Gerçek GunCon3 encode algoritması eklenirken kaynak olarak Beardypig'in GPL-2.0 GunCon3 Linux sürücüsü incelenecektir. O koddan birebir algoritma veya tablo alınırsa proje GPL uyumlu tutulmalıdır.
