//======================================================================================

void acionamentos()
{ //Abre função acionamento()

  //LED Verde
  if(A1_estado) //Se o botão da página estiver em estado ON
  { 
    digitalWrite(9, HIGH);  

    delay(15); //Aguarda 15 milissegundos    
  }
   else digitalWrite(LED_Verde,LOW); //Senão, apaga o LED Verde
  //=========================================================================================================================

}

//======================================================================================

