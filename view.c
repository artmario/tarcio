// todo parte relacionada a telas fica aqui
// para facilitar usar tela diferentes que vou comrar no futuro
void telaInit()// por enquanto iniciando apenas para um tipo
{
    if(1)//mudar no assim que escolher a proxima tela
    {

      u8g2.begin();
      u8g2.drawXBMP(31,0,64,64,Boobs);
      u8g2.sendBuffer();
      delay(8000);
      Serial.println("Starting");
      Serial.println("Battery Checker v0.8");
      Serial.println("time   battVolt   current     mAh");	
      u8g2.drawXBMP(0,0,128,64,Empty); 
      u8g2.drawFrame(0,0,127,63);
      u8g2.drawXBMP(2,2,17,10,Battery);
      u8g2.drawXBMP(27,2,17,10,Thunder);
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_baby_tr);
    }
}