//======================================================================================

float temperatura(){
  
  delay(15); //Aguarda 15 milissegundos
  
  if(Tmp){
    float t = dht.readTemperature(); //Faz a leitura da temperatura do ambiente  
  
    if(isnan(t)){ //Caso haja problema na leitura da temperatura do ambiente por parte do DHT
      return -1; //Retorna negativo já que o DHT11 não mede temperatura negativa
    }
    else{ //Caso a leitura tenha sucesso
      return t;
    }
  }
  return -2;  
}

//======================================================================================
