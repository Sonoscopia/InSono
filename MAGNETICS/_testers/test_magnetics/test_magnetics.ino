#define M1 3
#define M2 5 
#define M3 6
#define M4 2
#define M5 4
#define M6 7 
#define M7 8

#define L1 9 
#define L2 10
#define L3 11
#define L4 12
#define L5 13
#define L6 13

int testPin = M1; // pin to test
int delayTime = 250; // ms

void setup() {
  pinMode(testPin, OUTPUT);

}

void loop() {
  digitalWrite(testPin, HIGH);
  delay(delayTime);
  digitalWrite(testPin, LOW);
  delay(delayTime);
}
