#include <Stepper.h>

// Tentukan jumlah langkah per putaran motor (untuk motor 28BYJ-48 dengan gearbox)
const int stepsPerRevolution = 2048;  // 64 (step) * 32 (gear ratio)

// Tentukan pin yang terhubung ke motor driver ULN2003
const int motorPin1 = 8;
const int motorPin2 = 9;
const int motorPin3 = 10;
const int motorPin4 = 11;

// Inisialisasi stepper library pada jumlah langkah per putaran
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

// Variabel untuk melacak posisi saat ini
int currentAngle = 0;

void setup() {
  Serial.begin(9600);  // Memulai komunikasi serial
  myStepper.setSpeed(10);  // Atur kecepatan motor (RPM)
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readString();
    int targetAngle = data.toInt();  // Konversi data menjadi integer

    // Hitung perbedaan sudut yang perlu ditempuh
    int angleDifference = targetAngle - currentAngle;

    // Normalisasi perbedaan sudut agar berada dalam rentang -180 hingga 180 derajat
    if (angleDifference > 180) {
      angleDifference -= 360;
    } else if (angleDifference < -180) {
      angleDifference += 360;
    }

    // Konversi perbedaan sudut menjadi langkah motor
    int stepsToMove = map(angleDifference, -180, 180, -stepsPerRevolution / 2, stepsPerRevolution / 2);

    // Gerakkan motor ke sudut target
    myStepper.step(stepsToMove);

    // Perbarui posisi saat ini
    currentAngle = targetAngle;
  }
}
