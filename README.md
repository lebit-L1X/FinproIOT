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
![Gambar 2.1 implementasi hardware](https://)

## 3. Software implementation details

Pada sisi server, framework Flask digunakan untuk menangani API yang menerima permintaan HTTP GET dari ESP32. Ketika permintaan diterima, server mengaktifkan webcam laptop untuk menangkap gambar dan menyimpannya sebagai b.png di direktori lokal. Server ini juga memproses permintaan validasi gambar melalui API Face++ untuk membandingkan gambar yang diambil (a.png di sisi client) dengan b.png. Respons dalam format JSON dari API akan diteruskan ke client untuk dianalisis lebih lanjut.
Pada sisi client, ESP32 dikonfigurasi untuk berkomunikasi melalui WiFi menggunakan pustaka seperti WiFi.h dan HTTPClient.h. Dengan aplikasi Blynk, dua tombol kontrol disediakan: "Take a Photo" untuk memulai proses pengambilan gambar, dan "Validate Photo" untuk memvalidasi wajah menggunakan API. Proses validasi menghasilkan output berupa tingkat kepercayaan dan status akses (diberikan atau ditolak). Output ini dipublikasikan ke server MQTT dan ditampilkan pada aplikasi Blynk.

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

[1] ESP32IO.com, “ESP32 controls servo motor via WebSocket,” ESP32 Tutorial, 2024. https://esp32io.com/tutorials/esp32-solenoid-lock (accessed Dec. 10, 2024).

[2] “ESP32-CAM Video Streaming and Face Recognition with Arduino IDE | Random Nerd Tutorials,” Random Nerd Tutorials, Dec. 10, 2019. https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/ (accessed Dec. 10, 2024).

[3] “Arduino/ESP32-CAM_Base64 at master · fustyles/Arduino,” GitHub, 2024. https://github.com/fustyles/Arduino/tree/master/ESP32-CAM_Base64 (accessed Dec. 10, 2024).
