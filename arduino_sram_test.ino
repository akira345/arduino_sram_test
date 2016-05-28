//Arduino UNO



//pin define
#define ADDRESS0 14
#define ADDRESS1 15
#define ADDRESS2 16
#define ADDRESS3 17
#define ADDRESS4 18
#define ADDRESS5 19


#define DATA1 6
#define DATA2 7
#define DATA3 8
#define DATA4 9
#define DATA5 10
#define DATA6 11
#define DATA7 12
#define DATA8 13
#define CS 4
#define OE 3
#define WE 2

void sram_write_byte(unsigned int addr, char data) {
  // Address Set
  PORTC = addr;
  //OE HIGH
  digitalWrite(OE, HIGH);
  //CS Low
  digitalWrite(CS, LOW);
  //WE High
  digitalWrite(WE, HIGH);

  //Data Write
  //ポート出力設定
  DDRB = DDRB | B11111111;
  DDRD = DDRD | B11000000;
  //ポートへ出力
  PORTB = data >> 2; //8-13 上位6bit
  PORTD = (data & B00000011) << 6;    //6-7 下位2bit
  //WE Low
  digitalWrite(WE, LOW);

  //CS,WE High
  digitalWrite(WE, HIGH);
  digitalWrite(CS, HIGH);

}
char sram_read_byte(unsigned int addr) {
  uint8_t high;
  uint8_t low;
  char data;
  //Serial.println(addr);
  // Adress Set
  PORTC = addr;

  //WE High
  digitalWrite(WE, HIGH);
  //CS Low
  digitalWrite(CS, LOW);
  //OE Low
  digitalWrite(OE, LOW);

  //Data Read
  //ポート入力設定
  DDRB = B00000000; //上位6bit
  DDRD = B00111101; //下位2bit
  //ポート入力
  high = PINB;
  low = PIND & B11000000;
  //Serial.println(high);
  //Serial.println(low);
  data = (high << 2 ) + (low >> 6);

  //OE High
  digitalWrite(OE, HIGH);
  //CS High
  digitalWrite(CS, HIGH);

  //Serial.print("data=");
  //Serial.println(data);
  return data;
}
void setup() {
  pinMode(ADDRESS0, OUTPUT);
  pinMode(ADDRESS1, OUTPUT);
  pinMode(ADDRESS2, OUTPUT);
  pinMode(ADDRESS3, OUTPUT);
  pinMode(ADDRESS4, OUTPUT);
  pinMode(ADDRESS5, OUTPUT);

  pinMode(CS, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(WE, OUTPUT);

  digitalWrite(CS, HIGH);

  // Setup Serial Speed
  Serial.begin(9600);
  while (!Serial) {
    ; //wait
  }


  Serial.println("START");
  Serial.println("SRAM Test Test Test ...");
  Serial.println("---------------");
  char string[] = "SRAM Test Test Test ...";
  Serial.print("WriteString:");
  Serial.println(string);
  Serial.println("----------------");
  
  unsigned int len;
  len = strlen(string);
  for (unsigned int i = 0; i < len; ++i) {
    //Serial.println(string[i]);
    sram_write_byte(i, string[i]);
  }
  Serial.print("ReadString:");
  len = strlen(string);
  for (unsigned int i = 0; i < len; ++i) {
    Serial.print(sram_read_byte(i));
  }
  Serial.print("\n");
  Serial.println("-----------------");

  Serial.println("END");

}
void loop() {
  //write


}
