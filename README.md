# SIMasjid - Sistem Informasi Masjid Digital Download Disini : https://drive.google.com/file/d/1ItRqmop1fuZb63NBzGR9wdZEt2Nh11zB/view?usp=drive_link

**SIMasjid** adalah aplikasi *Digital Signage* berbasis Flutter yang dirancang khusus untuk menampilkan informasi penting di layar TV Masjid. Aplikasi ini menggabungkan fungsi jadwal sholat akurat, media informasi visual, dan integrasi *Smart System* untuk memodernisasi manajemen informasi masjid.

Dibuat oleh: **KORNET INTER MEDIA | 2026**

---

## 🌟 Fitur Unggulan

### 1. 🕌 Jadwal Sholat & Penanggalan
*   **Otomatis (Online):** Mengambil jadwal sholat akurat berdasarkan lokasi (Kota/Kabupaten) menggunakan API MyQuran atau AlAdhan.
*   **Manual (Offline):** Dukungan input jadwal manual CSV/JSON jika tidak ada koneksi internet.
*   **Kalender Hijriyah:** Konversi otomatis tanggal Masehi ke Hijriyah.
*   **Hitung Mundur:** *Countdown* menuju waktu Iqomah setelah Adzan berkumandang.

### 2. 📢 Media & Informasi
*   **Slide Informasi:** Menampilkan pengumuman, petugas jumat, atau laporan kas dalam bentuk slide bergantian.
*   **Running Text:** Teks berjalan di bagian bawah layar untuk informasi singkat/himbauan.
*   **Jadwal Media (Kajian):** Memutar video atau gambar (poster kajian) secara terjadwal pada jam dan hari tertentu.
*   **Hadis Harian:** Menampilkan kutipan hadis secara acak dengan efek *auto-scroll* (mendukung mode offline).
*   **Agenda Kegiatan:** Menampilkan daftar acara/kegiatan masjid mendatang.

### 3. 📱 Web Admin (Remote Control)
*   Tidak perlu repot mengetik menggunakan remote TV.
*   Cukup buka browser di HP/Laptop yang terhubung ke WiFi yang sama (misal: `http://192.168.1.x:8088`).
*   Atur semua teks, jadwal, upload gambar background, dan aset lainnya langsung dari HP.

### 4. ⚡ Smart IoT Integration
*   **Otomatisasi Listrik:** Terintegrasi dengan mikrokontroler (ESP32/Arduino) via WiFi.
*   **Fitur:** Otomatis menyalakan Amplifier/Speaker saat video kajian diputar dan mematikannya saat selesai atau saat Adzan tiba.

### 5. 🎨 Kustomisasi Tampilan
*   **Tema Fleksibel:** Ganti Background, Header, Jam, dan aset grafis lainnya sesuai selera atau foto masjid asli.
*   **Typography:** Atur jenis font, ukuran, dan warna teks untuk setiap elemen layar.

---

## 📺 Tampilan Layar (Screen Flow)

1.  **Dashboard Utama:** Menampilkan Jam Besar, Jadwal Sholat 5 Waktu, Running Text, dan Identitas Masjid.
2.  **Mode Adzan:** Overlay layar penuh saat waktu sholat tiba.
3.  **Mode Iqomah:** Hitung mundur dan peringatan "Luruskan Shaf".
4.  **Mode Standby/Rotasi:** Secara otomatis berganti antara Dashboard, Info Slide, Hadis, dan Agenda jika tidak ada aktivitas.

---

## 🛠️ Perangkat yang Didukung

Aplikasi ini dioptimalkan untuk layar besar (TV) dengan orientasi **Landscape**.

| Perangkat | Keterangan |
| :--- | :--- |
| **Android TV / Google TV** | Disarankan (Sony, TCL, Coocaa, Xiaomi TV, dll). |
| **Android TV Box (STB)** | Solusi hemat untuk mengubah TV biasa/monitor menjadi Smart Display (Mi Box, IndiHome Unlock, dll). |
| **Tablet Android** | Cocok untuk display ukuran kecil/sedang. |
| **Smartphone** | Bisa digunakan (wajib mode Landscape/Auto-rotate). |

**Spesifikasi Minimum:**
*   OS: Android 5.0 (Lollipop) ke atas.
*   RAM: 2GB (Disarankan).
*   Penyimpanan: 100MB (plus ruang untuk aset video/gambar).
*   Koneksi: WiFi (untuk fitur API Jadwal, Web Admin, dan IoT).

---

## 🚀 Cara Instalasi & Penggunaan

1.  **Instalasi:** Pasang file `.apk` pada perangkat Android TV/Box.
2.  **Koneksi:** Pastikan perangkat terhubung ke jaringan WiFi/LAN.
3.  **Pengaturan Awal:**
    *   Buka Aplikasi.
    *   Masuk ke menu pengaturan rahasia dengan menekan tombol **Tengah (D-Pad Center)** atau **OK** pada remote sebanyak **3 kali**, atau klik ikon **Gear** jika menggunakan mouse/touchscreen.
    *   Atur Nama Masjid, Lokasi (untuk jadwal sholat), dan preferensi lainnya.
4.  **Web Admin:** Cek IP Address yang muncul di menu "Identitas", lalu buka di browser HP untuk pengaturan lebih mudah.

---

*© 2026 KORNET INTER MEDIA. Free for non-commercial use in Mosques.*
