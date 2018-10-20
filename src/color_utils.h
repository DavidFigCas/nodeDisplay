/*******************************
  Color utilities

  Para hacer combinaciones de colores
  y convertir entre los modelos RGB y HSL

  Los colores en RGB se representan con arrays de bytes
  cada elemento del array es un canal
  uint8_t colorRGB[3] = {255, 255, 255};

  Los colores en HSL se representan con array de floats
  cada elemento del array debe tener un valor
  entre 0 (inclusivo) y 1 (exclusivo)
  float colorHSL[3] = {0.0, 1.0, 0.5};
*******************************/

//float colorHSL1[3] = {1.0 / 3.0, 1.0, 0.5};
//float colorHSL2[3] = {1.0 / 3.0, 1.0, 0.5};
//float colorHSL3[3]; //guardara el resultado
//uint8_t colorRGB1[3];

//-------------------------------------------------------------------
void mixColorsHSL(float* c1, float* c2, float* c3) {
  // c1 y c2 son punteros a arrays con colores hsl
  // c3 es un puntero a un array que guardara el resultado

  // Mix hue
  c3[0] = (c1[0] + c2[0]) / 2; //promedio
  if (abs(c1[0] + c2[0]) > 0.5) { //si no es el camino mas corto
    if (c3[0] < 0.5) c3[0] += 0.5; //girar 90 grados
    else c3[0] -= 0.5;
  }

  // Mix saturation
  c3[1] = (c1[1] + c2[1]) / 2; //promedio

  // Mix lightness
  c3[2] = (c1[2] + c2[2]) / 2; //promedio
}

//--------------------------------------------------------------------
void colorHSLtoRGB(float* c1, uint8_t* c2) {
  // c1 puntero a un array que contiene un color en HSL
  // definido con 3 valores flotantes de 0 a 1
  // c2 puntero a un array que guardara el resultado
  float H, S, L, R, G, B;
  H = 6.0 * c1[0];
  S = c1[1];
  L = 2.0 * c1[2];
  
  // Hue (funciones definidas a trozos)
  switch (uint8_t(H)) {
    case 0: R=1;   G=H;   B=0;   break;
    case 1: R=2-H; G=1;   B=0;   break;
    case 2: R=0;   G=1;   B=H-2; break;
    case 3: R=0;   G=4-H; B=1;   break;
    case 4: R=H-4; G=0;   B=1;   break;
    case 5: R=1;   G=0;   B=6-H; break;
    //default: //motrar error?
  }
  
  // Saturation
  // con saturacion 0 se generan grises (y el valor del matiz ya no tienen efecto)
  // con saturacion igual al rango completo se generan colores brillantes
  R = (R - 0.5)*S + 0.5;
  G = (G - 0.5)*S + 0.5;
  B = (B - 0.5)*S + 0.5;
  
  // Lightness (luminosidad)
  // si la luminosidad es menor a la mitad del rango, el color se oscurece
  // si la luminosidad es mayor a la mitad del rango, el color se blanquea
  if( L <= 1 ){ R*=L; G*=L; B*=L; }
  else{
    R += (1-R)*(L-1);
    G += (1-G)*(L-1);
    B += (1-B)*(L-1);
  }

  // Resultado
  c2[0] = uint8_t(R*255.0);
  c2[1] = uint8_t(G*255.0);
  c2[2] = uint8_t(B*255.0);
}
