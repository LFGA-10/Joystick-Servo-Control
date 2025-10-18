#include <Servo.h>

const int JOYSTICK_X_PIN = A0;   
const int SERVO_PIN = 9;         

Servo myServo;

int rawValue = 0;               
float normalized = 0.0;         
int targetAngle = 90;           
int currentAngle = 90;         
const int SMOOTH_STEP = 2;       

void setup() {
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);

  myServo.write(currentAngle);
  Serial.println("🔧 SmoothServo Control Initialized");
  Serial.println("-----------------------------------");
}

void loop() {
  rawValue = analogRead(JOYSTICK_X_PIN);

  normalized = (float)rawValue / 1023.0;

  targetAngle = map(rawValue, 0, 1023, 0, 180);

  if (abs(targetAngle - currentAngle) > SMOOTH_STEP) {
    if (targetAngle > currentAngle) currentAngle += SMOOTH_STEP;
    else currentAngle -= SMOOTH_STEP;
    myServo.write(currentAngle);
  } else {
  
    currentAngle = targetAngle;
    myServo.write(currentAngle);
  }

  Serial.print("Raw: "); Serial.print(rawValue);
  Serial.print("\tNormalized: "); Serial.print(normalized, 2);
  Serial.print("\tTarget Angle: "); Serial.print(targetAngle);
  Serial.print("\tServo Pos: "); Serial.println(currentAngle);

  delay(20); 
}