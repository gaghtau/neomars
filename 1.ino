#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <DHT.h>

// === OLED настройки ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// === DHT11 ===
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// === MQ135 ===
#define MQ135_PIN A0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === LCD ===
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === Моторы ===
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

// === HC-SR04 ===
const int TRIG = 2;
const int ECHO = 3;
const int DISTANCE_THRESHOLD = 30;

// === Сервоприводы ===
const int SERVO1_PIN = 4;  // фронт
const int SERVO2_PIN = 7;  // радар
Servo servo1, servo2;

float angle1 = 50, step1 = 1;
float angle2 = 10, step2 = 1;

// === Таймер обновления LCD ===
unsigned long lastLCDUpdate = 0;
const unsigned long lcdInterval = 500;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  dht.begin();
  pinMode(MQ135_PIN, INPUT);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  float distance = getDistance();

  Serial.print("Расстояние: ");
  Serial.print(distance);
  Serial.println(" см");

  showRadar(distance);

  bool isMiddleAngle = (angle1 >= 85 && angle1 <= 95);
  bool isTooClose = (distance < DISTANCE_THRESHOLD);

  if (isMiddleAngle && isTooClose) {
    reverseOneMotor();
  } else {
    moveForward();
    moveServos();
  }

  if (millis() - lastLCDUpdate >= lcdInterval) {
    lastLCDUpdate = millis();
    updateLCD(distance);
  }

  delay(10);
}

float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  return duration * 0.034 / 2;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reverseOneMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveServos() {
  // Обновляем угол для обоих сервоприводов
  angle1 += step2;
  
  // Меняем направление на границах
  if (angle1 >= 170 || angle1 <= 10) {
    step2 = -step2;
    angle1 += step2;  // чтобы не залипал на границе
  }

  angle1 = constrain(angle1, 10, 170);
  angle2 = angle1;  // одинаковый угол

  servo1.write(angle1);
  servo2.write(angle2);
}



void showRadar(float d) {
  display.clearDisplay();
  const int cx = 64;
  const int cy = 63;
  const int r = 60;

  display.drawCircle(cx, cy, r, WHITE);
  display.drawCircle(cx, cy, r * 3 / 4, WHITE);
  display.drawCircle(cx, cy, r / 2, WHITE);
  display.drawCircle(cx, cy, r / 4, WHITE);

  for (int a = 0; a <= 180; a += 30) {
    float rad = radians(a);
    int x = cx + r * cos(rad);
    int y = cy - r * sin(rad);
    display.drawLine(cx, cy, x, y, WHITE);
  }

  float scannerAngle = constrain(angle2, 10, 170);  // Угол сервопривода на пине D4
  float scanDeg = map(scannerAngle, 10, 170, 0, 180);
  float rad = radians(scanDeg);
  int xScan = cx + r * cos(rad);
  int yScan = cy - r * sin(rad);
  display.drawLine(cx, cy, xScan, yScan, WHITE);

  float dd = min(d, (float)r);
  int xObj = cx + dd * cos(rad);
  int yObj = cy - dd * sin(rad);
  display.fillCircle(xObj, yObj, 2, WHITE);

  display.display();
}

void updateLCD(float distance) {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int gasValue = analogRead(MQ135_PIN);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A:");
  lcd.print((int)angle1);
  lcd.print(" D:");
  lcd.print((int)distance);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  if (!isnan(t) && !isnan(h)) {
    lcd.print("T:");
    lcd.print((int)t);
    lcd.print(" H:");
    lcd.print((int)h);
    lcd.setCursor(11, 1);
    lcd.print("G:");
    lcd.print(gasValue / 10);
  } else {
    lcd.print("DHT Ошибка ");
  }
}
