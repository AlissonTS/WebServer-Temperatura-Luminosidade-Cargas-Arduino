#define LED_Verde 9//Define Lamp como 9
#define LED_Amarelo 8//Define Lamp como 8
#define LED_Vermelho 7//Define Lamp como 7

#include <SPI.h> //Inclui a biblioteca SPI.h
#include <Ethernet2.h> //Inclui a biblioteca Ethernet.h
// #include <Ethernet.h> //Inclui a biblioteca Ethernet2.h

#include "DHT.h" // Inclusão da Biblioteca do sensor DHT11 de temperatura e umidade
#define dhtpin A1 // Constante definida
#define dhttype DHT11 // DHT11

DHT dht(dhtpin, dhttype); // Inicia o sensor DHT11

// Configurações para o Ethernet Shield
// byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0x0C, 0xF1 }; // Entre com o valor do MAC ATUALIZADO 1
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x6D, 0x9D }; // Entre com o valor do MAC ATUALIZADO 2

IPAddress ip(192,168,90, 215); // Configure um IP válido 
byte gateway[] = { 192 , 168, 80, 1 }; //Entre com o IP do Computador onde a Câmera esta instalada
byte subnet[] = { 255, 255, 240, 0 }; //Entre com a Máskara de Subrede
EthernetServer server(80); //Inicializa a biblioteca EthernetServer com os valores de IP acima citados e configura a porta de acesso(80)
//======================================================================================

boolean A1_estado=false; //Variável para armazenar o estado do primeiro botão
boolean A2_estado=false; //Variável para armazenar o estado do segundo botão
boolean A3_estado=false; //Variável para armazenar o estado do terceiro botão
boolean Tmp=false; //Variável para armazenar estado do segundo botão
boolean Umd=false; //Variável para armazenar o estado do terceiro botão
boolean Lmd=false; //Variável para armazenar o estado do quarto botão

const int sensor=2; //Pino analógico em que o sensor será conectado
int valorSensor=0; //Sensor de luminosidade sendo setado em 0;
float temp=0; //Setando valor de temperatura em 0;
float umid=0; //Setando valor de umidade em 0;

//======================================================================================
/*
void acionamentos(); //Vai para a função que executa o acionamento dos botões
float temperatura(); //Vai para a função que executa a verificação de temperatura
float umidade(); //Vai para a função que executa a verificação de umidade
int luminosidade(); //Vai para a função que executa a verificação de luminosidade
*/
//======================================================================================
       
void setup()
{
  pinMode(LED_Verde,OUTPUT); //Define o pino 9 como saída
  pinMode(LED_Vermelho,OUTPUT); //Define o pino 7 como saída
  pinMode(LED_Amarelo,OUTPUT); //Define o pino 8 como saída
  dht.begin();
  
  Ethernet.begin(mac, ip);// Inicializa o Server com o IP e Mac atribuido acima
  server.begin();
}

//======================================================================================

void loop()
{
  
  EthernetClient client = server.available();// Verifica se tem alguém conectado

  if (client)
  {

    boolean currentLineIsBlank = true; // A requisição HTTP termina com uma linha em branco Indica o fim da linha
    String valPag;

    while (client.connected())
    {

      if (client.available())
      {
        char c = client.read(); //Variável para armazenar os caracteres que forem recebidos
        valPag.concat(c); // Pega os valor após o IP do navegador ex: 192.168.1.2/0001        

        //Compara o que foi recebido
        if(valPag.endsWith("0001")) //Se o que for pego após o IP for igual a 0001
        {
          A1_estado = !A1_estado; //Inverte o estado do primeiro acionamento
          
          acionamentos1(); //Vai para a função que executa o acionamento dos botões
        }
        
         if(valPag.endsWith("0010")) //Se o que for pego após o IP for igual a 0010
        {
          A2_estado = !A2_estado; //Inverte o estado do primeiro acionamento
          
          acionamentos2(); //Vai para a função que executa o acionamento dos botões
        }
        
         if(valPag.endsWith("0011")) //Se o que for pego após o IP for igual a 0011
        {
          A3_estado = !A3_estado; //Inverte o estado do primeiro acionamento
          
          acionamentos3(); //Vai para a função que executa o acionamento dos botões
        }
        
        else if(valPag.endsWith("0100")) //Senão se o que for pego após o IP for igual a 0100
        {
          Tmp = !Tmp;  //Inverte o estado do segundo acionamento 
           
          temp = temperatura(); //Vai para a função que executa a verificação de temperatura      
        }
        
        else if(valPag.endsWith("0101")) //Senão se o que for pego após o IP for igual a 0101
        {
          Umd = !Umd;  //Inverte o estado do terceiro acionamento
          
          umid = umidade(); //Vai para a função que executa a verificação de umidade      
        }
        
        else if(valPag.endsWith("0110")) //Senão se o que for pego após o IP for igual a 0110
        {
          Lmd = !Lmd;  //Inverte o estado do quarto acionamento
    
          valorSensor = luminosidade(); //Vai para a função que executa a verificação de luminosidade      
        }
        
        //=========================================================================================================================
        
        if (c == '\n' && currentLineIsBlank)
        {
          //Inicia página HTML
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: text/html"));
          client.println();
          client.print(F("<HTML>"));
          client.println(F("<BR><center></B></I></U><a href=\"http://csi.ufsm.br\"> <img src=http://sites.multiweb.ufsm.br/sisint/images/banner.png></a></B></I></U></center>"));
          client.println(F("<BR><center></B></I></U><h2>- Gerenciamento de Cargas - Temperatura e Umidade - Luminosidade - </h2></B></I></U></center>"));
          //=========================================================================================================================
          
          //=========================================================================================================================

          client.print(F("<BR>"));

          //Primeiro BOTAO - LED Verde
          client.print(F("<center><h3>Carga 1</h3></center>"));
          client.print(F("<center><button style=\"width:150; heigth:300;\" onclick=\"window.location.href='http://192.168.90.215/0001'\">\0</button> > Codigo: 0001 > "));
          if(A1_estado)
          {            
            client.print(F("<B><span style=\"color: #00ff00;\">"));   
            client.print(F("Carga - ON"));     
            client.print(F("</span></B></center>"));
          }         
          else
          {
            client.print(F("<B><span style=\"color: #ff0000;\">"));
            client.print(F("Carga - OFF"));
            client.print(F("</span></B></center>"));
          }
          //=========================================================================================================================
        
          client.print(F("<br>"));
        
          //Segundo BOTAO - LED Amarelo
          client.print(F("<center><h3>Carga 2</h3></center>"));
          client.print(F("<center><button style=\"width:150; heigth:300;\" onclick=\"window.location.href='http://192.168.90.215/0010'\">\0</button> > Codigo: 0010 > "));
          if(A2_estado)
          {            
            client.print(F("<B><span style=\"color: #00ff00;\">"));   
            client.print(F("Carga - ON"));     
            client.print(F("</span></B></center>"));
          }         
          else
          {
            client.print(F("<B><span style=\"color: #ff0000;\">"));
            client.print(F("Carga - OFF"));
            client.print(F("</span></B></center>"));
          }
          //=========================================================================================================================
          
          client.print(F("<br>"));
          
          //Terceiro BOTAO - LED Vermelho
          client.print(F("<center><h3>Carga 3</h3></center>"));
          client.print(F("<center><button style=\"width:150; heigth:300;\" onclick=\"window.location.href='http://192.168.90.215/0011'\">\0</button> > Codigo: 0011 > "));
          if(A3_estado)
          {            
            client.print(F("<B><span style=\"color: #00ff00;\">"));   
            client.print(F("Carga - ON"));     
            client.print(F("</span></B></center>"));
          }         
          else
          {
            client.print(F("<B><span style=\"color: #ff0000;\">"));
            client.print(F("Carga - OFF"));
            client.print(F("</span></B></center>"));
          }
          //=========================================================================================================================
      
          client.print(F("<br>"));
          
          client.print(F("<center><h3>Temperatura:</h3></center>"));
          //Quarto BOTAO - Temperatura
          client.print(F("<center><button style=\"width:150; heigth:300;\" onclick=\"window.location.href='http://192.168.90.215/0100'\">\0</button> > Codigo: 0100 > "));
          if(Tmp)
          {
            client.print(F("<B><span>Temperatura"));
            if(temp>-1){
              client.print(F(" - "));
              client.print(temp);
              client.print(F("*C"));
            }  
            client.print(F("</span></B></center> "));
          }
          else
          {
            client.print(F("<B><span>Temperatura - Verificar</span></B></center>"));;
          }
          //=========================================================================================================================
  
          client.print(F("<br>"));
  
          client.print(F("<center><h3>Umidade:</h3></center>"));
          client.print(F("<center><button style=\"width:150; heigth:300;\" onclick=\"window.location.href='http://192.168.90.215/0101'\">\0</button> > Codigo: 0101 > "));
          if(Umd)
          {
            client.print(F("<B><span>Umidade"));
            if(umid>-1){
              client.print(F(" - "));
              client.print(umid);
              client.print(F(" Porcento"));
            }  
            client.print(F("</span></B></center> "));
          }
          else
          {
            client.print(F("<B><span>Umidade"));
            client.print(F(" - Verificar"));
            client.print(F("</span></B></center> "));
          }
          //=========================================================================================================================
          
          client.print(F("<br>"));
          
          //Sexto BOTAO - Luminosidade
          client.print(F("<center><h3>Luminosidade:</h3></center>"));
          client.print(F("<center><button style=\"width:150; heigth:300;\" onclick=\"window.location.href='http://192.168.90.215/0110'\">\0</button> > Codigo: 0110 > "));
          if(Lmd)
          {
            client.print(F("<B><span>Luminosidade"));
            if(valorSensor>-1){
              client.print(F(" - "));
              client.print(valorSensor);
              
              //Luminosidade baixa
              if (valorSensor < 750) {
                 client.print(F(" - Baixa"));
              }
              //Luminosidade média.
              if (valorSensor >= 750 && valorSensor <= 800) {
                 client.print(F(" - Media"));
              }
              //Luminosidade alta.
              if (valorSensor > 800) {
                 client.print(F(" - Alta"));
              }
              
            }  
            client.print(F("</span></B></center> "));
          }
          else
          {
            client.print(F("<B><span>Luminosidade"));
            client.print(F(" - Verificar"));
            client.print(F("</span></B></center> "));
          }
             
          
          //=========================================================================================================================      

          // client.print(F("<BR>"));
          //=========================================================================================================================

          // client.print(" <meta http-equiv=\"refresh\" content=\"5; url=http://192.168.90.215/\"> "); // Atualiza a Página

          client.println(F("<BR><center></B></I></U><h2>Por: Alisson Trindade Souza</h2></B></I></U></center>"));
          client.println(F("</HTML>"));

          break;

        } //Fecha if (c == '\n' && currentLineIsBlank)
        
      } //Fecha if (client.available())
      
    } //Fecha While (client.connected())
    
    delay(3);// Espera um tempo para o navegador receber os dados
    client.stop(); // Fecha a conexão
    
  } //Fecha if(client)
  
} //Fecha loop

//======================================================================================
