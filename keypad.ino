#include <Keypad.h>

#define ROW_NUM     4 // quatro linhas
#define COLUMN_NUM  4 // quatro colunas

char pass[] = {'1', '5', '5'};
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM]      = {26, 25, 33, 32}; // Conecte GPIO19, GPIO18, GPIO5, GPIO17 às linhas
byte pin_column[COLUMN_NUM] = {13, 12, 14, 27};   // Conecte GPIO16, GPIO4, GPIO0, GPIO2 às colunas

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

int keyPress = 0;

void setup() {
  // Inicialização do código aqui, para ser executado uma vez:
  Serial.begin(115200);
  Serial.println("Olá, ESP32!");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == pass[keyPress]) {
      Serial.print("Tecla permitida pressionada: ");
      Serial.println(key);
      
      keyPress++; // Avança para a próxima sequência
      
      // Verifica se a sequência foi concluída
      if (keyPress >= sizeof(pass)) {
        Serial.println("Sequência de teclas correta!");
        keyPress = 0; // Reinicia a sequência
      }
    } else {
      // Tecla pressionada está errada, redefina a sequência
      keyPress = 0;
      Serial.println("Tecla incorreta. Reiniciando a sequência.");
    }
  }
}
