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

Sistem Smart Door Lock with Face Recognition ini menggunakan beberapa komponen perangkat keras untuk mengimplementasikan fungsionalitasnya. Perangkat keras yang digunakan dalam proyek ini adalah sebagai berikut:

- Webcam / Kamera : Sistem ini menggunakan webcam dari laptop sebagai perangkat untuk mengambil gambar wajah pengguna. Webcam ini terhubung ke laptop melalui kabel USB dan digunakan untuk mengambil gambar wajah pengguna saat proses pengenalan wajah.

- ESP32: ESP32 adalah mikrokontroler yang digunakan dalam sistem ini. Mikrokontroler ini bertanggung jawab untuk mengendalikan operasi sistem secara keseluruhan. ESP32 terhubung ke webcam melalui koneksi USB dan juga terhubung ke jaringan WiFi untuk mengirimkan data dan menerima instruksi dari server.

- Relay : Relay digunakan untuk mengendalikan kunci pintu secara otomatis. Ketika sistem mendeteksi wajah yang terdaftar dan memberikan akses yang valid, relay akan diaktifkan untuk membuka kunci pintu. Relay ini terhubung ke ESP32 dan dapat dikendalikan melalui sinyal output dari mikrokontroler.

Implementasi proyek ini :
![Gambar 2.1 implementasi hardware](https://)

## 3. Software implementation details

Selain perangkat keras, sistem Smart Door Lock with Face Recognition ini juga membutuhkan implementasi solusi perangkat lunak yang tepat untuk mengoperasikan sistem secara efisien. Komponen perangkat lunak yang digunakan pada proyek ini adalah sebagai berikut:

- Flask Server: Sistem menggunakan Flask Server untuk meng-host server yang akan menerima permintaan dari ESP32 dan mengambil foto dari webcam. Flask Server ini berjalan di laptop dan berfungsi sebagai jembatan antara ESP32 dan webcam.

- HTTP Request: Sistem menggunakan HTTP Request untuk berkomunikasi antara ESP32 dan Flask Server. Ketika pengguna menekan tombol "take a photo" atau "validate photo" pada aplikasi Blynk, ESP32 akan mengirimkan permintaan HTTP ke Flask Server untuk mengambil foto atau menjalankan API Face++ untuk memvalidasi foto.

- API Face++: Sistem menggunakan API Face++ untuk melakukan pemrosesan pengenalan wajah. Ketika pengguna memvalidasi foto, ESP32 akan mengirimkan foto yang diambil ke API Face++ untuk membandingkannya dengan foto wajah yang terdaftar. API Face++ akan memberikan respons dalam bentuk JSON yang akan di-deserialize dan dimasukkan ke dalam antrian.

- MQTT: Sistem menggunakan protokol MQTT (Message Queuing Telemetry Transport) untuk mengirimkan data dari ESP32 ke aplikasi Blynk. Data hasil validasi wajah akan dipublikasikan melalui MQTT dan ditampilkan pada aplikasi Blynk untuk memberikan informasi apakah akses diberikan atau tidak.

- Task: Sistem menggunakan task untuk membaca antrian data hasil validasi wajah dan mempublikasikannya melalui MQTT. Task ini berjalan di ESP32 dan memastikan bahwa data hasil validasi wajah dikirimkan ke aplikasi Blynk secara real-time.

- Blynk: Blynk adalah platform IoT yang digunakan dalam sistem ini. Platform ini digunakan untuk membuat antarmuka pengguna yang memungkinkan pengguna untuk mengontrol sistem melalui aplikasi ponsel mereka. Pengguna dapat menggunakan aplikasi Blynk untuk mengambil foto, memvalidasi foto, dan melihat status akses pintu.

## 4. Test results and implementation details

Proyek ini telah diuji menggunakan beberapa skenario pengujian untuk memastikan bahwa sistem berfungsi dengan baik dan memberikan respons yang sesuai. Pengujian dilakukan dengan mengambil gambar wajah pengguna, memvalidasi gambar tersebut dengan API Face++, dan mengontrol akses pintu menggunakan relay. Berikut adalah hasil pengujian yang diperoleh:

Hasil pengujian sistem :
![Gambar 4.1 Hasil pengujian](https://)

## 5. Conclusion and future work

Kesimpulannya :

-
-
-

Selanjutnya, sistem ini dapat dikembangkan lagi dengan ditambahkan fitur berikut :

- Menambahkan fitur keamanan tambahan seperti PIN atau akses berbasis token untuk meningkatkan keamanan sistem.
- Mengintegrasikan sistem dengan perangkat pintar lainnya seperti sensor gerak untuk meningkatkan keamanan dan kenyamanan pengguna seperti memulai autentikasi wajah otomatis jika terdeteksi adanya gerakan.
- Mengoptimalkan algoritma pengenalan wajah untuk meningkatkan akurasi dan respons sistem.
- Mengembangkan aplikasi Blynk dengan fitur tambahan seperti log akses untuk memberikan informasi yang lebih lengkap kepada pengguna.
- Mengimplementasikan enkripsi data untuk melindungi informasi pengguna dan mencegah akses yang tidak sah.

## References

https://esp32io.com/tutorials/esp32-solenoid-lock

https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/

https://github.com/fustyles/Arduino/tree/master/ESP32-CAM_Base64
