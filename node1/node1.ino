String datareceive;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    char datareceive = Serial.read();
    Serial.print(datareceive);
  }

}
