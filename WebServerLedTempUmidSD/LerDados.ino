void LerDados(EthernetClient novoCliente) {
        
        float umidade = dht.readHumidity(); //Faz a leitura da umidade do ambiente
        novoCliente.print(umidade);
        novoCliente.println("%");
        
        novoCliente.print("|");
  
        float temperatura = dht.readTemperature(); //Faz a leitura da temperatura do ambiente  
        novoCliente.print(temperatura);
        novoCliente.println("*C");
        
        novoCliente.print("|");
        
        luz = analogRead(LDR);
        luz = map(luz, 0, 1023, 0, 100);
        novoCliente.print(luz);
        novoCliente.println("%");
        
        novoCliente.print("|");
        
        novoCliente.print(flag1);
        
        novoCliente.print("|");
        
        //espero receber algo como 90%|25*C|100%|0
}
