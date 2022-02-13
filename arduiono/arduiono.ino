const byte LED_PIN = 3;

const char CMD_OFF[] =         "110110110110111101101011011110101011011011010111111111111011111110111110111011110101101";
const char CMD_ON[] =          "110110110110111101101011011110101011011011010111111111110110110101011011111011101111011011";
const char CMD_BRIGHT[] =      "110110110110111101101011011110101011011011010111111111110111010111101111101110111101111";
const char CMD_DIM[] =         "110110110110111101101011011110101011011011010111111111110111110111011111011101111101101";
const char CMD_COOL[] =        "11011011011011110110101101111010101101101101011111111111011011011101011111011101111011011";
const char CMD_WARM[] =        "110110110110111101101011011110101011011011010111111111110110111110101111101110111111011";
const char CMD_WHOLE_LIGHT[] = "1101101101101111011010110111101010110110110101111111111101111111101111101110111111101";
const char CMD_NIGHT_LIGHT[] = "11011011011011110110101101111010101101101101011111111111011011011110111110111011110110101";
const char CMD_GLARE_FREE[] =  "11011011011011110110101101111010101101101101011111111111011110101110111110111011110101011";
const char CMD_SLEEP[] =       "1101101101101111011010110111101010110110110101111111111101111110110111110111011111101010";
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
  Serial.begin(9600, SERIAL_8N1);
}

void send_cmd(const char cmd) {
  const char *seq = NULL;

  if (cmd == 'f') {
    seq = CMD_OFF;
  } else if (cmd == 'o') {
    seq = CMD_ON;
  } else if (cmd == 'b') {
    seq = CMD_BRIGHT;
  } else if (cmd == 'd') {
    seq = CMD_DIM;
  } else if (cmd == 'c') {
    seq = CMD_COOL;
  } else if (cmd == 'w') {
    seq = CMD_WARM;
  } else if (cmd == 'l') {
    seq = CMD_WHOLE_LIGHT;
  } else if (cmd == 'n') {
    seq = CMD_NIGHT_LIGHT;
  } else if (cmd == 'g') {
    seq = CMD_GLARE_FREE;
  } else if (cmd == 's') {
    seq = CMD_SLEEP;
  }

  if (!seq) {
    return;
  }

  t = micros();
  send_half_bit(HIGH, T_pulse_init1_us);
  send_half_bit(LOW, T_pulse_init2_us);
  for (byte i = 0; seq[i]; i++) {
    send_bit(seq[i]);
  }
}

void loop() {
  const char cmd = Serial.read();

  if (cmd == 'h') {
    Serial.println("On oFf Bright Dim Cool Warm whole_Light Night_light Glare_free Sleep");
  } else {
    send_cmd(cmd);
  }

}
