#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <Preferences.h>

// --- KONFIGURASI ---
const int RELAY_PIN = 2; // Ganti dengan pin Relay Anda (misal: 4, 5, 12, dll). Pin 2 biasanya Built-in LED.
const bool RELAY_ACTIVE_HIGH = true; // Ubah ke false jika relay Anda aktif saat LOW (Active Low)

// --- OBJEK GLOBAL ---
WebServer server(80);
DNSServer dnsServer;
Preferences preferences;

// --- VARIABEL ---
bool isAPMode = false;

// HTML untuk Portal Konfigurasi WiFi
const char* htmlConfig = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>SIMasjid IoT Setup</title>
  <style>
    body { font-family: sans-serif; text-align: center; padding: 20px; background-color: #f4f4f9; }
    h2 { color: #2c3e50; }
    form { background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); max-width: 400px; margin: auto; }
    input { padding: 10px; margin: 10px 0; width: 100%; box-sizing: border-box; border: 1px solid #ddd; border-radius: 4px; }
    button { background-color: #009688; color: white; padding: 12px; border: none; border-radius: 4px; width: 100%; cursor: pointer; font-size: 16px; }
    button:hover { background-color: #00796b; }
  </style>
</head>
<body>
  <h2>SIMasjid IoT Setup</h2>
  <p>Hubungkan perangkat ini ke Wi-Fi Masjid agar bisa dikontrol oleh aplikasi.</p>
  <form action="/save" method="POST">
    <label style="float:left; font-weight:bold;">Nama Wi-Fi (SSID)</label>
    <input type="text" name="ssid" placeholder="Contoh: Masjid_Al_Muntaha" required>
    
    <label style="float:left; font-weight:bold;">Kata Sandi</label>
    <input type="password" name="pass" placeholder="Password Wi-Fi">
    
    <button type="submit">Simpan & Restart</button>
  </form>
</body>
</html>
)rawliteral";

// Fungsi untuk mengontrol Relay
void setRelay(bool on) {
  if (RELAY_ACTIVE_HIGH) {
    digitalWrite(RELAY_PIN, on ? HIGH : LOW);
  } else {
    digitalWrite(RELAY_PIN, on ? LOW : HIGH);
  }
}

// Memulai Mode Access Point (Portal)
void startAP() {
  isAPMode = true;
  WiFi.mode(WIFI_AP);
  WiFi.softAP("SIMasjid-IoT-Setup"); // Nama Hotspot yang akan muncul di HP
  
  Serial.println("Masuk Mode AP. Silakan hubungkan HP ke 'SIMasjid-IoT-Setup'");
  Serial.print("IP Address AP: "); Serial.println(WiFi.softAPIP());

  // Redirect semua request DNS ke IP ESP (Captive Portal)
  dnsServer.start(53, "*", WiFi.softAPIP());

  // Endpoint Halaman Utama Portal
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlConfig);
  });

  // Endpoint untuk menangani Captive Portal Android/iOS
  server.on("/generate_204", HTTP_GET, []() { server.send(200, "text/html", htmlConfig); });
  server.on("/fwlink", HTTP_GET, []() { server.send(200, "text/html", htmlConfig); });

  // Endpoint Simpan Konfigurasi
  server.on("/save", HTTP_POST, []() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    
    if (ssid.length() > 0) {
      preferences.putString("ssid", ssid);
      preferences.putString("pass", pass);
      server.send(200, "text/html", "<h1>Disimpan!</h1><p>Perangkat sedang restart untuk terhubung ke Wi-Fi...</p>");
      delay(2000);
      ESP.restart();
    } else {
      server.send(400, "text/plain", "SSID tidak boleh kosong.");
    }
  });

  server.begin();
}

// Memulai Mode Station (Terhubung ke WiFi Masjid)
void startServer() {
  isAPMode = false;
  
  // Endpoint Cek Status
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "SIMasjid IoT Controller is Online.");
  });

  // Endpoint Nyalakan Relay
  server.on("/on", HTTP_GET, []() {
    setRelay(true);
    server.send(200, "text/plain", "Relay ON");
    Serial.println("Command: Relay ON");
  });

  // Endpoint Matikan Relay
  server.on("/off", HTTP_GET, []() {
    setRelay(false);
    server.send(200, "text/plain", "Relay OFF");
    Serial.println("Command: Relay OFF");
  });

  // Endpoint Reset Pengaturan WiFi (Jika ingin ganti WiFi)
  server.on("/reset_wifi", HTTP_GET, []() {
    preferences.clear();
    server.send(200, "text/plain", "Pengaturan WiFi dihapus. Restarting ke Mode AP...");
    delay(1000);
    ESP.restart();
  });

  server.begin();
  Serial.println("Web Server Started.");
}

void setup() {
  Serial.begin(115200);
  
  // Setup Relay
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false); // Default mati saat nyala

  // Setup Penyimpanan (NVS)
  preferences.begin("wifi-config", false);
  String ssid = preferences.getString("ssid", "");
  String pass = preferences.getString("pass", "");

  if (ssid == "") {
    Serial.println("Konfigurasi Wi-Fi belum ada.");
    startAP();
  } else {
    Serial.print("Mencoba terhubung ke: "); Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());

    // Tunggu koneksi max 20 detik
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 40) {
      delay(500);
      Serial.print(".");
      retry++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nTerhubung ke Wi-Fi!");
      Serial.print("IP Address: "); Serial.println(WiFi.localIP());
      startServer();
    } else {
      Serial.println("\nGagal terhubung. Masuk ke Mode AP untuk konfigurasi ulang.");
      startAP();
    }
  }
}

void loop() {
  if (isAPMode) {
    dnsServer.processNextRequest(); // Penting untuk Captive Portal
  }
  server.handleClient();
}
