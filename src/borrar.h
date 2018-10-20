uint32_t mixColors(uint32_t c1, uint32_t c2, uint8_t pc) {
  // c1 - color 1
  // c2 - color 2
  // pc - percent 0 -> c1 only, 50 -> equal mix, 100 -> c2 only
  uint8_t pcinv = 100 - pc; //inverse
  
  uint32_t r1 = (c1 & 0xFF0000) * pcinv;
  uint32_t r2 = (c2 & 0xFF0000) * pc;
  uint32_t r3 = (r1 + r2) / 100;

  uint32_t g1 = (c1 & 0xFF00) * pcinv;
  uint32_t g2 = (c2 & 0xFF00) * pc;
  uint32_t g3 = (g1 + g2) / 100;

  uint32_t b1 = (c1 & 0xFF) * pcinv;
  uint32_t b2 = (c2 & 0xFF) * pc;
  uint32_t b3 = (b1 + b2) / 100;

  return r3 + g3 + b3;
}

void setup()
{
  Serial.begin(9600);
  uint32_t m = mixColors(0xFF0000, 0x00FF00, 50);
  Serial.print(m, HEX);
}

void loop()
{
}
