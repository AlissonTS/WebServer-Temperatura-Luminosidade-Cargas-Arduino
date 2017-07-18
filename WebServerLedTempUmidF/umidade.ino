//======================================================================================

float umidade(){
  
  delay(15); //Aguarda 15 milissegundos
  
  if(Umd){
    float h = dht.readHumidity(); //Faz a leitura da umidade do ambiente
  
    if(isnan(h)){ //Caso haja problema na leitura da umidade do ambiente por parte do DHT
       return -1;  // Retorna valor negativo;
    }
    else{
       return h;
    }   
  } 
  return -2;  
}

//======================================================================================
