int fib(int n) {
  if (n < 2) {
    return n;
  } else {
    return fib(n - 1) + fib(n - 2);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("system initialized"));
}

void loop() {
  Serial.println(fib(38));
}
