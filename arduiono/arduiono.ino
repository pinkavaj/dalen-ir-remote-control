int LED_PIN = 3;

const char OFF[] = "110110110110111101101011011110101011011011010111111111111011111110111110111011110101101";
const int MOD_FREQ = 38285;
const int T_pulse_us = 422;
const int T_pulse_init1_us = 3500;
const int T_pulse_init2_us = 1650;
unsigned long t;


static void send_half_bit(const bool c, const int len_us) {
  t += len_us;
  if (c) {
    tone(LED_PIN, MOD_FREQ);
  }
  while (t > micros());
  noTone(LED_PIN);
}

static void send_bit(const char c) {
  send_half_bit(c == '1' ? HIGH : LOW, T_pulse_us);
  send_half_bit(LOW, T_pulse_us);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  t = micros();
  send_half_bit(HIGH, T_pulse_init1_us);
  send_half_bit(LOW, T_pulse_init2_us);
  for (int i = 0; i < sizeof(OFF) - 1; i++) {
    send_bit(OFF[i]);
  }

  delay(300);
}
