//======================================================================================

void acionamentos1()
{ //Abre função acionamento()

  //LED Verde
  if(A1_estado) //Se o botão da página estiver em estado ON
  { 
    digitalWrite(LED_Verde, HIGH);  

    delay(15); //Aguarda 15 milissegundos    
  }
  else digitalWrite(LED_Verde,LOW); //Senão, apaga o LED Verde
  //=========================================================================================================================

}

//======================================================================================

void acionamentos2()
{ //Abre função acionamento()

  //LED Verde
  if(A2_estado) //Se o botão da página estiver em estado ON
  { 
    digitalWrite(LED_Amarelo, HIGH);  

    delay(15); //Aguarda 15 milissegundos    
  }
  else digitalWrite(LED_Amarelo,LOW); //Senão, apaga o LED Verde
  //=========================================================================================================================

}

//======================================================================================

void acionamentos3()
{ //Abre função acionamento()

  //LED Verde
  if(A3_estado) //Se o botão da página estiver em estado ON
  { 
    digitalWrite(LED_Vermelho, HIGH);  

    delay(15); //Aguarda 15 milissegundos    
  }
  else digitalWrite(LED_Vermelho,LOW); //Senão, apaga o LED Verde
  //=========================================================================================================================

}

//======================================================================================
