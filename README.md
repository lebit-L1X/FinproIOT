# FinproIOT Kelompok 15

# Smart Door Lock with Face Recognition

## 1. Introduction to the problem and the solution

Keamanan rumah kita sangat penting, dan sistem keamanan tradisional seperti kunci fisik memiliki keterbatasan. Kunci dapat hilang, disalin tanpa izin, atau bahkan dimanipulasi oleh individu yang tidak berwenang. Untuk mengatasi masalah ini, diperlukan teknologi inovatif untuk menyediakan solusi yang canggih dan aman.

Salah satu inovasi tersebut adalah teknologi pengenalan wajah. Dengan mengidentifikasi karakteristik wajah secara unik, teknologi ini menawarkan tingkat keamanan yang lebih tinggi dibandingkan dengan metode konvensional seperti kunci atau PIN. Selain itu, pengenalan wajah juga menawarkan kenyamanan karena pengguna tidak perlu membawa perangkat tambahan seperti kartu atau kunci fisik.

Namun, mengintegrasikan teknologi pengenalan wajah ke dalam sistem keamanan rumah membutuhkan pendekatan komprehensif yang melibatkan perangkat keras, perangkat lunak, dan konektivitas jaringan yang stabil. Sistem yang ideal harus dapat mendeteksi wajah dengan akurasi tinggi, memproses data dengan cepat, dan memberikan respons yang sesuai tanpa mengorbankan privasi pengguna. Selain itu, teknologi ini harus mudah diakses dan dapat terhubung dengan perangkat pintar lainnya untuk memberikan pengalaman pengguna yang optimal.

Untuk mengatasi tantangan ini, kami memberikan sebuah solusi dengan membuat proyek Smart Door Lock with Face Recognition. Sistem keamanan modern ini menggunakan teknologi pengenalan wajah untuk menggantikan metode tradisional yang rentan terhadap risiko seperti kehilangan atau penyalahgunaan. Dengan menggunakan pengenalan wajah, hanya individu yang terdaftar yang dapat mengakses pintu, memberikan tingkat keamanan yang lebih tinggi untuk rumah atau properti.

Proyek ini mengintegrasikan teknologi berbasis IoT untuk memungkinkan operasi otomatis dan konektivitas dengan perangkat pengguna. Sistem ini dirancang untuk memanfaatkan konektivitas jaringan untuk transmisi data secara real-time dan kontrol akses jarak jauh melalui aplikasi khusus.

Proyek ini tidak hanya relevan untuk aplikasi rumah tangga tetapi juga dapat diimplementasikan dalam lingkungan yang lebih luas seperti kantor, gudang, atau fasilitas lainnya. Dengan pendekatan ini, kami bertujuan untuk menyediakan solusi praktis yang mendorong implementasi teknologi pintar untuk menciptakan lingkungan yang lebih aman dan efisien.

## 2. Hardware design and implementation details

Desain hardware pada proyek Smart Door Lock with Face Recognition menggunakan beberapa komponen utama, yaitu dua modul ESP32, breadboard, solenoid lock 12V, dan relay 5V. ESP32 pertama berfungsi sebagai modul utama untuk pengambilan gambar wajah melalui kamera yang terintegrasi, sementara ESP32 kedua bertindak sebagai server yang mengelola komunikasi data dan pengendalian aktuator. Komunikasi antara kedua modul ini dilakukan melalui jaringan mesh, yang memberikan konektivitas stabil dan latensi rendah.
Breadboard digunakan untuk membuat prototipe rangkaian elektronik secara modular, memungkinkan penyambungan komponen secara fleksibel. Solenoid lock 12V berfungsi sebagai mekanisme penguncian yang dikendalikan oleh relay 5V. Relay bertindak sebagai saklar elektronik yang menghubungkan atau memutus aliran daya ke solenoid berdasarkan sinyal kontrol dari ESP32. Desain ini memastikan solenoid hanya aktif saat wajah yang terdeteksi berhasil dikenali oleh sistem.

Implementasi proyek :
![Gambar 2.1 implementasi desain hardware](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Hardware%20design.JPG)

[Model 3D desain hardware](https://www.tinkercad.com/things/9tIslLEpA0q-finpro-iot)

## 3. Software implementation details

Pada sisi server, framework Flask digunakan untuk menangani API yang menerima permintaan HTTP GET dari ESP32. Ketika permintaan diterima, server mengaktifkan webcam laptop untuk menangkap gambar dan menyimpannya sebagai b.png di direktori lokal. Server ini juga memproses permintaan validasi gambar melalui API Face++ untuk membandingkan gambar yang diambil (a.png di sisi client) dengan b.png. Respons dalam format JSON dari API akan diteruskan ke client untuk dianalisis lebih lanjut.
Pada sisi client, ESP32 dikonfigurasi untuk berkomunikasi melalui WiFi menggunakan pustaka seperti WiFi.h dan HTTPClient.h. Dengan aplikasi Blynk, dua tombol kontrol disediakan: "Take a Photo" untuk memulai proses pengambilan gambar, dan "Validate Photo" untuk memvalidasi wajah menggunakan API. Proses validasi menghasilkan output berupa tingkat kepercayaan dan status akses (diberikan atau ditolak). Output ini dipublikasikan ke server MQTT dan ditampilkan pada aplikasi Blynk.

Implementasi perangkat lunak yang dibuat :
![Gambar 3.1 Server gambar yang dibuat untuk mengidentifikasi pengguna yang diperbolehkan untuk mengakses pintu tersebut](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Images%20Web%20Server.JPG)

## 4. Test results and implementation details

Proyek ini telah diuji menggunakan beberapa skenario pengujian, seperti :

- API Testing untuk memastikan bahwa sistem berfungsi dengan baik dan memberikan respons yang sesuai. Pengujian dilakukan dengan mengambil dua gambar wajah pengguna dan memvalidasi gambar tersebut dengan API Face++. Selain itu, pengujian juga dilakukan dengan membandingkan gambar yang tidak ada wajah dengan gambar yang memiliki wajah untuk memastikan bahwa sistem dapat membedakan wajah dengan benar.
  ![Gambar 4.1 Gambar yang terdapat pada server gambar](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Images%20Web%20Server.JPG)
  ![Gambar 4.2 Gambar yang diujikan](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Gambar%20yang%20diuji.JPG)

- Web Server berbasis Flask. Pengujian dilakukan dengan membandingkan 2 gambar pada server dengan 3 gambar klien yang berbeda. Pengujian ini dilakukan untuk memastikan bahwa server dapat menerima permintaan dari klien dan memberikan respons yang sesuai.
- ESP32 Klien dapat melakukan proses upload dan memanggil verifikasi wajah. Ini dilakukan melalui Blynk dan upload serta verifikasi dilakukan dengan mengakses web server. Oleh karena itu, dilakukan beberapa pengujian pada ESP32 client, antara lain memastikan client terhubung ke Blynk, memastikan pemanggilan permintaan HTTP pada webcam berhasil, serta pengiriman data atau publikasi ke MQTT berhasil.
- ESP32 Server dapat melakukan proses upload dan menerima data hasil verifikasi, serta mengirimkan warning ke blynk. Proses yang dilalui untuk upload wajah serupa dengan client sehingga pada ESP32 server testing, pengujian dilakukan terhadap keberhasilan blynk, akses HTTP, subscribe topic MQTT dan mengirimkan warning kepada blynk.
- Blynk app merupakan interface yang digunakan oleh client dan server dalam mengakses webcam. Pengujian pada blynk dilakukan dengan memastikan widget berjalan dengan seharusnya dan pengiriman perintah untuk mengakses webcam maupun penerimaan data akses invalid melalui terminal diterima secara sempurna.
- Hardware testing dilakukan dengan menguji ESP32 serta hardware yang terhubung, yaitu built in LED serta relay yang mengaktifkan solenoid lock.

Hasil pengujian sistem :

- Tes API
  Hasil perbandingan ketiga gambar tersebut dengan gambar yang ada pada server, yang merupakan gambar dari pengguna yang diperbolehkan :
  ![Gambar 4.3 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/API%20test%20results.JPG)

- Tes ESP32 Klien
  Koneksi Blynk dengan perangkat berhasil :
  ![Gambar 4.4 Hasil pengujian aplikasi Blynk](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Blynk_Client.png)
  Mengakses kamera melalui Blynk dari klien :
  ![Gambar 4.5 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Capture_LogClient.png)
  Foto yang tersimpan setelah berhasil mengakses kamera yang disimpan pada penyimpanan lokal :
  ![Gambar 4.6 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/a-client.png)
  Melakukan perbandingan menggunakan foto tersebut dengan foto yang ada pada server, yang merupakan foto dari pengguna yang diperbolehkan :
  ![Gambar 4.7 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Compare_Client_Valid.png)
  Melakukan perbandingan dengan menggunakan gambar yang lain yang tidak terdapat pada server gambar sehingga tidak diperbolehkan :
  ![Gambar 4.8 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Compare_Client_Invalid.png)
  Berhasil terhubung ke MQTT dan mengirimkan data hasil validasi :
  ![Gambar 4.9 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/MQTT_Client.PNG)

- Tes ESP32 Server
  Koneksi Blynk dengan perangkat berhasil :
  ![Gambar 4.10 Hasil pengujian aplikasi Blynk](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Blynk_Server.png)
  Berhasil mengakses kamera melalui Blynk dari server :
  ![Gambar 4.11 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Capture_LogServer.png)
  Foto yang tersimpan setelah berhasil mengakses kamera yang disimpan pada penyimpanan lokal :
  ![Gambar 4.12 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/b-server.png)
  Berhasil terhubung ke MQTT dan menerima data hasil validasi setelah berlangganan ke topik MQTT tersebut ketika pengguna yang diperbolehkan masuk :
  ![Gambar 4.13 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/MQTT_Server.PNG)
  dan ketika pengguna yang tidak diperbolehkan masuk :
  ![Gambar 4.14 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/MQTT_Server_Invalid.PNG)

- Blynk app testing
  Berhasil menghubungkan aplikasi Blynk dengan ESP32 klien dan server. Ketika terdapat pengguna yang tidak dikenali, maka aplikasi Blynk akan memberikan notifikasi berikut :
  ![Gambar 4.15 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Blynk_Server_Intruder.png)

- Hardware testing
  Berhasil mengaktifkan solenoid lock menggunakan relay 5V :
  ![Gambar 4.16 Hasil pengujian](https://raw.githubusercontent.com/lebit-L1X/FinproIOT/refs/heads/master/Pictures/Hardware%20testing.JPG)

## 5. Conclusion and future work

Kesimpulannya :

Kelompok 15 telah berhasil mengembangkan sistem Smart Lock berbasis Facial Recognition sebagai solusi untuk meningkatkan keamanan rumah. Sistem ini menggunakan mikrokontroler ESP32 dan platform Blynk untuk mengirimkan permintaan HTTP ke webcam yang terhubung melalui web server. Webcam memproses gambar wajah dan memberikan respons validitas hasil pengenalan wajah. Hasilnya diteruskan ke MQTT server untuk menentukan tindakan selanjutnya, seperti membuka pintu atau memberikan peringatan melalui aplikasi Blynk jika wajah tidak valid.

Sistem ini memanfaatkan teknologi IoT dan pengenalan wajah yang andal untuk meningkatkan keamanan dan efisiensi. ESP32 mendukung komunikasi data real-time, MQTT server memungkinkan pengelolaan data yang cepat, dan Blynk memberikan interface yang mudah diakses. Sistem ini juga dapat memberikan notifikasi jika ada upaya akses mencurigakan, meningkatkan pengawasan dan respon terhadap ancaman.

Sistem Smart Lock ini inovatif dan relevan untuk kebutuhan keamanan rumah modern. Potensinya dapat ditingkatkan dengan mendukung beberapa perangkat kamera, meningkatkan interface, dan mengembangkan komponen software dan hardware yang digunakan.

Selanjutnya, sistem ini dapat dikembangkan lagi dengan ditambahkan fitur berikut :

- Menambahkan fitur keamanan tambahan seperti PIN atau akses berbasis token untuk meningkatkan keamanan sistem.
- Mengintegrasikan sistem dengan perangkat pintar lainnya seperti sensor gerak untuk meningkatkan keamanan dan kenyamanan pengguna seperti memulai autentikasi wajah otomatis jika terdeteksi adanya gerakan.
- Mengembangkan infrastruktur IoT sehingga dapat mendukung lebih dari satu kamera
- Mengembangkan aplikasi Blynk dengan fitur tambahan seperti log akses untuk memberikan informasi yang lebih lengkap kepada pengguna.
- Mengimplementasikan enkripsi data untuk melindungi informasi pengguna dan mencegah akses yang tidak sah.

## References

[1] ESP32IO.com, “ESP32 controls servo motor via WebSocket,” ESP32 Tutorial, 2024. https://esp32io.com/tutorials/esp32-solenoid-lock (accessed Dec. 10, 2024).

[2] “ESP32-CAM Video Streaming and Face Recognition with Arduino IDE | Random Nerd Tutorials,” Random Nerd Tutorials, Dec. 10, 2019. https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/ (accessed Dec. 10, 2024).

[3] “Arduino/ESP32-CAM_Base64 at master · fustyles/Arduino,” GitHub, 2024. https://github.com/fustyles/Arduino/tree/master/ESP32-CAM_Base64 (accessed Dec. 10, 2024).
