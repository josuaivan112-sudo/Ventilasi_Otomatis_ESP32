
#include <DHT.h>
#include <ESP32Servo.h>

// Konfigurasi pin
#define PIR_PIN 27
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define SERVO_PIN 18

// Parameter sistem
const float BATAS_SUHU = 30.0;
const float KENAIKAN_SUHU = 0.5;

const unsigned long INTERVAL_BACA = 2500;
const unsigned long DURASI_AKTIVITAS = 30000;
const unsigned long MIN_WAKTU_BUKA = 10000;

// Inisialisasi komponen
DHT dht(DHT_PIN, DHT_TYPE);
Servo servoVentilasi;

// Variabel sistem
float suhuAcuan = NAN;

unsigned long waktuBaca = 0;
unsigned long waktuAktivitas = 0;
unsigned long waktuBuka = 0;

bool aktivitasTerdeteksi = false;
bool ventilasiTerbuka = false;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  dht.begin();

  servoVentilasi.setPeriodHertz(50);
  servoVentilasi.attach(SERVO_PIN, 500, 2400);
  servoVentilasi.write(0);

  Serial.println("========================");
  Serial.println("         SISTEM     ");
  Serial.println("========================");
  Serial.println("Inisialisasi berhasil!");
}

void loop() {

  unsigned long sekarang = millis();

  // 1. Deteksi aktivitas manusia
  if (digitalRead(PIR_PIN) == HIGH) {
    aktivitasTerdeteksi = true;
    waktuAktivitas = sekarang;
  }

  // 2. Interval pembacaan DHT22
  if (sekarang - waktuBaca < INTERVAL_BACA) {
    return;
  }

  waktuBaca = sekarang;

  // 3. Membaca suhu dan kelembapan
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Pembacaan DHT22 gagal!");
    return;
  }

  // 4. Menentukan suhu acuan
  if (isnan(suhuAcuan)) {
    suhuAcuan = suhu;
  }

  // 5. Evaluasi kondisi
  bool adaAktivitas =
    aktivitasTerdeteksi &&
    (sekarang - waktuAktivitas <= DURASI_AKTIVITAS);

  bool suhuTinggi = suhu >= BATAS_SUHU;

  bool suhuNaik =
    suhu >= (suhuAcuan + KENAIKAN_SUHU);

  bool bukaVentilasi =
    adaAktivitas && suhuTinggi && suhuNaik;

  // 6. Kendali servo
  if (bukaVentilasi && !ventilasiTerbuka) {

    servoVentilasi.write(90);

    ventilasiTerbuka = true;
    waktuBuka = sekarang;

    Serial.println(">>> VENTILASI TERBUKA");

  } else if (
    ventilasiTerbuka &&
    !bukaVentilasi &&
    sekarang - waktuBuka >= MIN_WAKTU_BUKA
  ) {

    servoVentilasi.write(0);

    ventilasiTerbuka = false;
    suhuAcuan = suhu;

    Serial.println(">>> VENTILASI TERTUTUP");
  }

  // Memperbarui suhu acuan saat ruangan tidak aktif
  if (!adaAktivitas && !ventilasiTerbuka) {
    suhuAcuan = suhu;
  }

  // 7. Serial Monitor
  Serial.println("------------------------");

  Serial.print("Suhu       : ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembapan : ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Suhu acuan : ");
  Serial.print(suhuAcuan);
  Serial.println(" C");

  Serial.print("Aktivitas  : ");
  Serial.println(adaAktivitas ? "TERDETEKSI" : "TIDAK");

  Serial.print("Ventilasi  : ");
  Serial.println(ventilasiTerbuka ? "TERBUKA" : "TERTUTUP");
}
