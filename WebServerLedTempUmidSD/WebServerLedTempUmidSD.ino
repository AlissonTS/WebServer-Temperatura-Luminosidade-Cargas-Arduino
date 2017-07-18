//#include <Ethernet_v2.h> //para segunda geracao do shield ethernet

#include <Ethernet.h> //para primeira geracao do shield ethernet
#include <SD.h>
#include <SPI.h>

#include "DHT.h" // Inclusão da Biblioteca do sensor DHT11 de temperatura e umidade
#define dhtpin A1 // Constante definida
#define dhttype DHT11 // DHT11

#define carga1 9//Define Lamp como 9

// Configurações para o Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0x0C, 0xF1 }; // Entre com o valor do MAC ATUALIZADO 1
// byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x6D, 0x9D }; // Entre com o valor do MAC ATUALIZADO 2

IPAddress ip(192,168,90,215); // Configure um IP válido 
byte gateway[] = { 192 , 168, 80, 1 }; //Entre com o IP do Computador onde a Câmera esta instalada
byte subnet[] = { 255, 255, 240, 0 }; //Entre com a Máskara de Subrede
EthernetServer server(80); //Inicializa a biblioteca EthernetServer com os valores de IP acima citados e configura a porta de acesso(80)

DHT dht(dhtpin, dhttype); // Inicia o sensor DHT11

File webFile;

#define REQ_BUF_SZ 50
char HTTP_req[REQ_BUF_SZ] = { 0 };
char req_index = 0;

const int LDR = A2;

int luz = 0;
int temperatura = 0;
int umidade = 0;

int flag1 = 0;

void setup() {
        pinMode(carga1, OUTPUT);
        analogReference(INTERNAL);
      
        Ethernet.begin(mac, ip);
        server.begin();
      
        Serial.begin(9600);
      
        Serial.println(F("Inicializando cartao MicroSD..."));
        if (!SD.begin(4)) {
          Serial.println(F("ERRO - iniciallizacao do cartao falhou!"));
          return;
        }
        Serial.println(F("SUCESSO - cartao MicroSD inicializado."));
      
        if (!SD.exists("index.htm")) {
          Serial.println(F("ERRO - index.htm nao foi encontrado!"));
          return;
        }
        Serial.println(F("SUCESSO - Encontrado arquivo index.htm."));
}

void loop() {
        EthernetClient client = server.available();
      
        if (client) {
          boolean currentLineIsBlank = true;
          while (client.connected()) {
            if (client.available()) {
      
              char c = client.read();
      
              if (req_index < (REQ_BUF_SZ - 1)) {
                HTTP_req[req_index] = c;
                req_index++;
              }
      
              if (c == '\n' && currentLineIsBlank) {
                client.println(F("HTTP/1.1 200 OK"));
                client.println(F("Content-Type: text/html"));
                client.println(F("Connection: close"));
                client.println();
      
                if (StrContains(HTTP_req, "ajax_LerDados")) {
                  LerDados(client);
                }
      
                if (StrContains(HTTP_req, "ajax_carga1")){
                  SetCarga1();
                }
      
                else {
      
                  webFile = SD.open("index.htm");
                  if (webFile) {
                    while (webFile.available()) {
                      client.write(webFile.read());
                    }
                    webFile.close();
                  }
                }
                Serial.println(HTTP_req);
                req_index = 0;
                StrClear(HTTP_req, REQ_BUF_SZ);
                break;
              }
      
              if (c == '\n') {
                currentLineIsBlank = true;
              }
              else if (c != '\r') {
                currentLineIsBlank = false;
              }
            }
          }
      
          delay(1);
          client.stop();
      
        }

}
