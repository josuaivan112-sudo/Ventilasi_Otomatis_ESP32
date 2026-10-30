# Sistem Ventilasi Otomatis Berbasis ESP32

## Deskripsi Proyek

Proyek ini merupakan prototipe sistem ventilasi otomatis yang dirancang untuk merespons aktivitas pergerakan manusia dan perubahan suhu ruangan.

Sistem menggunakan ESP32 sebagai pusat pengendali yang mengintegrasikan sensor PIR HC-SR501, sensor DHT22, dan motor servo SG90.

Proyek ini dikembangkan untuk memenuhi tugas Luminous Quest Mikrokontroler 2026, Quest S-2: Lautan Manusia.

## Komponen yang Digunakan

1. ESP32-WROOM
2. Sensor PIR HC-SR501
3. Sensor DHT22
4. Motor Servo SG90
5. Breadboard
6. Kabel jumper
7. Kabel USB

## Konfigurasi Pin

| Komponen | Pin ESP32 |
|---|---|
| PIR HC-SR501 (OUT) | GPIO 27 |
| DHT22 (DATA) | GPIO 4 |
| Servo SG90 (Signal) | GPIO 18 |

## Cara Kerja Sistem

1. ESP32 membaca aktivitas pergerakan melalui sensor PIR.
2. Sensor DHT22 mengukur suhu dan kelembapan udara.
3. Data kedua sensor diproses berdasarkan parameter yang telah ditentukan.
4. Ketika kriteria aktivitas dan kenaikan suhu terpenuhi, servo menggerakkan ventilasi menuju posisi terbuka.
5. Sistem melakukan pemantauan secara berkala untuk menentukan kondisi ventilasi berikutnya.

## Software dan Library

Software:
- Arduino IDE
- Wokwi

Library:
- DHT sensor library (Adafruit)
- Adafruit Unified Sensor
- ESP32Servo
- DHT sensor library for ESPx

## Link Simulasi

Simulasi Wokwi:

https://wokwi.com/projects/479211556043609089

## Dokumentasi Video

[MASUKKAN LINK VIDEO DEMONSTRASI]

## Anggota Kelompok

Kelompok: Obsidian

Anggota:
1. Muhammad Raihan Assidiq
2. Rinoa Annisa Permata
3. Aldino Fairuz
4. Ghisca Arvitasari
5. Reval Haidar Afan Nararya
6. Rafif Azzam Dzakwan Nuba
7. Muhammad Jawad Ahmadaly
8. Josua Ivan Devandra
9. Izz Muhandis
10. Lamorin Stevany Nainggolan
11. Matthew Deven Calovery Samboh
12. Jonathan Davion Renardo
13. Mitha Aulia Wijaya Puteri
14. Bandang Raditya Maheswara
15. Nauval Nadiy Azwar



## Referensi

- https://docs.arduino.cc/
- https://docs.wokwi.com/
- https://docs.espressif.com/
