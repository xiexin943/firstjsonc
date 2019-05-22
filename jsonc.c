#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictlist.h"
#include "formatjson.h"
#include "symboljson.h"
#include "jsonc.h"


//函数声明
Json JsonInit(JsonString jsonstr);
void JsonShow(JsonString jsonstr);
JsonString JsonReady(JsonString jsonstr);
DictValue JsonGetValue(struct JSON *jsonobj,DictKey key);
void StorageKey(KeyValueListPtr head,JsonString json);
void StorageValue(ListSymbol sblist,KeyValueListPtr head,JsonString json);

//将易存储类型的json字符串按照键值对,将键先存储在list中
//第一个参数是完成初始化的双双向链表
//第二个参数是易存储的json字串
void StorageKey(KeyValueListPtr head,JsonString json)
{
  JsonString str = json;
  Information  keystr;
  int i = 0;
  while(*str != '\0')
  {
    if(KeyLeftQuotationMarks(str))
    {
      keystr = GetJsonColonInformation(str);
      SetKeyValueList(head,keystr,NULL,i+1);
      i++;
    }
    str++;
  }
}
//将易存储类型的json字符串按照键值对,将键先存储在list中
//第一个参数是完成填值的符号链表
void StorageValue(ListSymbol sblist,KeyValueListPtr head,JsonString json)
{
  StorageKey(head,json);//填充键值对链表
  KeyNodePtr keyptr = head->keyhead->Next;
  ValueNodePtr valueptr = head->valuehead->Next;
  JsonString ptr;
  Information keystr;
  Information valuestr;
  Position position;
  Position pairposition;
  char FirstLetter;
  int i = 0;
  while(keyptr != head->keyhead)
  {
    ptr = json;
    position = 0;
    while(*ptr != '\0')
    {
      position++;
      if(KeyLeftQuotationMarks(ptr))//到了键值最左边的那个引号
      {
        keystr = GetJsonColonInformation(ptr);
        if((strcmp(keystr,keyptr->key)) == 0)
        {
          FirstLetter = GetColonRightChar(ptr);
          switch(FirstLetter)
          {
            case '\"':
              valuestr = GetSimpleObjValue(ptr);
              SetKeyValueList(head,keystr,valuestr,i+1);
              break;
            case '[':
              position = position + strlen(keystr) + 3;
              pairposition = FindPairPosition(sblist,position);
              valuestr = GetJsonBrackestsInformation(json,position,pairposition);
              SetKeyValueList(head,keystr,valuestr,i+1);
              break;
            case '{':
              position = position + strlen(keystr) + 3;
              pairposition = FindPairPosition(sblist,position);
              valuestr = GetJsonBrackestsInformation(json,position,pairposition);
              SetKeyValueList(head,keystr,valuestr,i+1);
              break;
            default:
              printf("Json String Format Error!\n");
          }
        break;
        }
      }
      ptr++;
    }
    i++;
    keyptr = keyptr->Next;
    valueptr = valueptr->Next;
  }
}
//查看字符串函数，输入可以是自定义的也可以是易读的
void JsonShow(JsonString jsonstr)
{
  JsonString Recv;
  Recv = FormatJsonSend(jsonstr);
  ShowJsonString(Recv);
}

//将json字串转换成易读取的格式
//也就是容易发送的格式
//注意输入不能是易存储的格式
//将自定义格式的字串经过本函数就可以发送了
JsonString JsonReady(JsonString jsonstr)
{
  JsonString str;
  str = FormatJsonSend(jsonstr);
  return str;
}

//根据键寻找链表中的值
DictValue JsonGetValue(struct JSON *jsonobj,DictKey key)
{
  KeyNodePtr ptr;
  DictValue value;
  ValueNodePtr valueptr = jsonobj->KeyValueList->valuehead->Next;
  ptr = jsonobj->KeyValueList->keyhead->Next;
  while(ptr != jsonobj->KeyValueList->keyhead)
  {
    if((strcmp(ptr->key,key)) == 0 )
    {
      value = valueptr->value;
      break;
    }
    ptr = ptr->Next;
    valueptr = valueptr->Next;
  }
  return value;
}

//返回一个Json格式的对象
Json JsonInit(JsonString jsonstr)
{
  JsonString Recv;
  Json ret;
  ret = (Json)malloc(sizeof(struct JSON));
  Recv = FormatJsonSend(jsonstr);
  bzero(ret,sizeof(struct JSON));
  ret->String = Recv;

  ListSymbol sblist;
  Recv = FormatJsonStorage(Recv);
  sblist = CreatJsonSymbolList(Recv);
  SymbolPair(Recv,sblist);

  KeyValueListPtr head;
  Frequency count;
  count = JsonObjectCount(Recv);
  head = CreatKeyValueList(count);
  StorageValue(sblist,head,Recv);
  ret->KeyValueList = head;

  ret->Show = JsonShow;
  ret->Ready = JsonReady;
  ret->GetValue = JsonGetValue;
  return ret;
}

/*
JsonString jsonstr = "\
{\
    \"country\":{\
        \"name1\":\"china\",\
        \"province\":[{\
                \"name2\":\"heilongjiang\",\
                \"cities\":{\
                    \"city\":[\"haerbing\",\"daqiang\"]\
                }\
            },{\
                \"name3\":\"huangdong\",\
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
  JsonString Recv;
  Recv = FormatJsonSend(jsonstr);//假装这个Recv是接收到的json
  ShowJsonString(Recv);//按格式打印

  ListSymbol sblist;
  Recv = FormatJsonStorage(Recv);//转换为易存储的格式
  sblist = CreatJsonSymbolList(Recv);//创建符号链表
  SymbolPair(Recv,sblist);//完善符号链表

  KeyValueListPtr head;
  Frequency count;
  count = JsonObjectCount(Recv);//获取键值对个数
  head = CreatKeyValueList(count);//创建键值对链表
  StorageValue(sblist,head,Recv);//填充键值对链表
  ShowKeyVlaueList(head);
  return 0;
}
*/

