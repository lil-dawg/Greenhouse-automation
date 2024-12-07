const int inner_limit = 8;
const int outer_limit = 9;

void setup() {
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  Serial.begin(9600);
}

void loop() {
  bool inner = digitalRead(inner_limit);
  Serial.print("inner: ");
  Serial.println(inner);

  bool outer = digitalRead(outer_limit);
  Serial.print("outer: ");
  Serial.println(outer);

  Serial.println(" ");
  delay(500);
}
