#define BLYNK_TEMPLATE_ID "TMPL62XjoQ5b1"
#define BLYNK_TEMPLATE_NAME "Fanfan"
#define BLYNK_AUTH_TOKEN "YDnUu6_cHooKhHxSXjGba8qqrf0UttWA"

// กำหนดขา GPIO ที่จะใช้
#define BT1 22
#define BT2 21
#define BT3 19

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiManager.h> // ใช้ WiFiManager สำหรับ ESP32

WidgetLCD lcd1(V0);
WidgetLED BT1Blynk(V10);
WidgetLED BT2Blynk(V11);
WidgetLED BT3Blynk(V12);

char auth[] = BLYNK_AUTH_TOKEN;

// รับค่าจากปุ่มในแอป Blynk
BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(BT1, value);
  BT1Blynk.setValue(value);
}

BLYNK_WRITE(V2) {
  int value = param.asInt();
  digitalWrite(BT2, value);
  BT2Blynk.setValue(value);
}

BLYNK_WRITE(V3) {
  int value = param.asInt();
  digitalWrite(BT3, value);
  BT3Blynk.setValue(value);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // เรียก WiFiManager
  WiFiManager wifiManager;

  // ถ้าเชื่อมต่อ WiFi ไม่ได้ จะสร้าง AP ชื่อ SmartFan_AP
  wifiManager.autoConnect("SmartFan_AP");

  Serial.println("WiFi Connected!");

  // เชื่อมต่อ Blynk โดยใช้ config
  Blynk.config(auth);
  
  // รอจนกว่า WiFi จะเชื่อมต่อก่อนดำเนินการต่อ
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi failed!");
    while (true);
  }

  // กำหนดขา OUTPUT สำหรับรีเลย์ควบคุมพัดลม
  pinMode(BT1, OUTPUT);
  pinMode(BT2, OUTPUT);
  pinMode(BT3, OUTPUT);

  // ปิดพัดลมทั้งหมดตอนเริ่มต้น
  digitalWrite(BT1, LOW);
  digitalWrite(BT2, LOW);
  digitalWrite(BT3, LOW);

  // แสดงข้อความใน LCD widget
  lcd1.clear();
  lcd1.print(3, 0, "Smart Fan");
  lcd1.print(5, 1, "Controller");
}

void loop() {
  Blynk.run();
}
