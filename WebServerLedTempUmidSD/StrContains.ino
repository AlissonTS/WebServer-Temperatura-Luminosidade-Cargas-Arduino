        char StrContains(char *str, char *sfind)
        {
              char found = 0;
              char index = 0;
              char len;
            
              len = strlen(str);
            
              if (strlen(sfind) > len) {
                return 0;
              }
            
              while (index < len) {
                if (str[index] == sfind[found]) {
                  found++;
                  if (strlen(sfind) == found) {
                    return 1;
                  }
                }
                else {
                  found = 0;
                }
                index++;
              }
              return 0;
        }
