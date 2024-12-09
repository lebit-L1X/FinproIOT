# FinproIOT

References: https://esp32io.com/tutorials/esp32-solenoid-lock

https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/

https://github.com/fustyles/Arduino/tree/master/ESP32-CAM_Base64

## Penjelasan Sistem

Sistem menggunakan webcam dari laptop untuk mengambil gambar, ini dilakukan dengan menghosting sebuah flask server yang jika dipanggil akan mengambil foto dan menyimpannya dalam directory laptop. Foto pada client dinamakan a.png. Foto pada server dinamakan b.png. Server adalah muka orang yang teregister sedangkan client adalah orang yang ingin mencoba masuk dan di validasi.


Alur kerja dari client:

- Terdapat dua switch pada blynk, yaitu take a photo, dan validate photo
- Jika menekan switch take a photo, maka esp32 memanggil http request untuk mengaktifkan webcam dan mengambil gambar, yang kemudian disimpan pada laptop.
- Jika menekan switch validate, maka esp32 memanggil http request untuk menjalankan API Face++ untuk melakukan comparison antara file a.png dan b.png. Response dari API dalam bentuk JSON, akan di deserialize dan dimasukkan kedalam queue.
- Terdapat task yang berfungsi untuk membaca queue dan mempublishnya pada MQTT.
- Pada blynk akan ditampilkan apakah berhasil masuk atau tidak.


Alur kerja dari server:

- Terdapat satu buah switch pada blink, yaitu take a photo.
- Jika ditekan, akan memanggil http request untuk mengaktifkan webcam dan mengambil gambar yang disimpan dalam bentuk b.png. Ini adalah muka orang yang valid.
- Bertindak sebagai MQTT sub yang memiliki callback dan menampilkan apakah publisher mengizinkan access ("Access Granted") atau terdapat intruder ("Intruder Alert").
- Jika access granted, buka lock dengan memberikan high pada relay
- Jika Intruder, berikan notifikasi pada blynk dengan mengirimkan string.
