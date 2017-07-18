      void SetCarga1(){
            if(flag1 == 0){
              digitalWrite(carga1, HIGH);
              flag1 = 1;
            }
            else{
              digitalWrite(carga1, LOW);
              flag1 = 0;
            }
      }
