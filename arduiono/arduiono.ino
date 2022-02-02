int led_pin = 3;

const char OFF[] = "110110110110111101101011011110101011011011010111111111111011111110111110111011110101101";
const int T_mod_us = 26;
const int T_pulse_us = 420;
const int T_pulse_init1_us = 3500;
const int T_pulse_init2_us = 1600;

void send_half_bit(char c, int len_us) {
  for (int i = 0; i < len_us / T_mod_us; ++i) {
    digitalWrite(led_pin, c);
    delayMicroseconds(T_mod_us);  
    digitalWrite(led_pin, LOW);
    delayMicroseconds(T_mod_us);  
  }
}

void send_bit(char c) {
  send_half_bit(c == "1" ? HIGH : LOW, T_pulse_us);
  send_half_bit(LOW, T_pulse_us);
}

void setup() {
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

void loop() {
  send_half_bit("1", T_pulse_init1_us);
  send_half_bit("0", T_pulse_init2_us);
  
  for (int i = 0; i < sizeof(OFF) - 1; i++) {
    send_bit(OFF[i]);
  }

  delay(200);
}
