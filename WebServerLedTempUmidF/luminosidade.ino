//======================================================================================

int luminosidade(){
  
   delay(15); //Aguarda 15 milissegundos   
  
   if(Lmd){
      int valor = analogRead(sensor);
      
      return valor;
   }  
   int sensor=2; //Pino analógico em que o sensor será conectado   
} 

//======================================================================================
