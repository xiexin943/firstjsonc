#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsonc.h"

JsonString jsonstr = "\
{\
    \"country\":{\
        \"name\":\"china\",\
        \"province\":[{\
                \"name\":\"heilongjiang\",\
                \"cities\":{\
                    \"city\":[\"haerbing\",\"daqiang\"]\
                }\
            },{\
                \"name\":\"huangdong\",\
                \"cities\":{\
                    \"city\":[\"guangzhou\",\"shenzhen\",\"zhuhai\"]\
                },\
                \"size\":200,\
                \"temperature\":35,\
                \"hunidity\":[37,33,88,98,58,46,65,68],\
                \"attribute\":[\"big\",140,\"pretty\"]\
            }]\
    }\
}\
";
int main(int argc,char* argv[])
{
  Json myjson;
  char* send;
  char* value;
  myjson = JsonInit(jsonstr);
  myjson->Show(myjson->String);
  send = myjson->Ready(myjson->String);
  printf("send = %s\n",send);
  value = myjson->GetValue(myjson,"country");
  printf("value = %s\n",value);
  return 0;
}
