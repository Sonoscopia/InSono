// TEST MOTORS
#define MOTOR 3 // set motor pin
#define VIN 5  // set input voltage

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = Serial.parseInt();
  if(val>0 && val <= VIN) {
    analogWrite(MOTOR, voltage2int(val, VIN));
    Serial.println(val);
  }
  if(val< -1){
    Serial.println("OFF");
    digitalWrite(MOTOR, LOW);
  }
  //else analogWrite(MOTOR, LOW);
}

int voltage2int(int v, int vin){ // v = desired output voltage (must be < vin)
  return v * 255.f / vin; // returns value from 0~255 corresponding to the desired voltage, where 255 = vin
}
