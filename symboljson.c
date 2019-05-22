#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboljson.h"
#include "formatjson.h"

//函数声明
JsonSymbolGather CountSymbol(JsonString str);
ListSymbol InitListSymbol();
void CreatSymbolList(ListSymbol head,const int count);
ListSymbol CreatJsonSymbolList(JsonString json);
void ShowList(ListSymbol list);
int FindMax(int Array[],int count);
int FindMin(int Array[],int count);
int FindPair(int compare,int Array[],int count);
void SetMax(int Array[],int count);
void SetPair(int pair,int Array[]);
int PositiveCount(int Array[],int count);
void SymbolPair(JsonString json,ListSymbol list);
Information GetJsonColonInformation(LeftColon left);
Information GetJsonBrackestsInformation(JsonString json,Position leftposition,Position rightposition);
int JsonObjectCount(JsonString json);
bool KeyLeftQuotationMarks(char* ch);
char GetColonRightChar(LeftColon left);
Position FindPairPosition(ListSymbol list,Position position);
Information GetSimpleObjValue(LeftColon left);

//数出字符串中各个符号个数
JsonSymbolGather CountSymbol(JsonString str)
{
    JsonSymbolGather ret;
    int Colon = 0,QuotationMarks = 0,LeftMiddleBrackets = 0,LeftCurlyBraces = 0,RightMiddleBrackets = 0,RightCurlyBraces = 0,Comma = 0;
    ret = (JsonSymbolGather)malloc(sizeof(struct JsonSymbol));
    while(*str != '\0')
    {
        if(*str == ':')
            Colon++;
        if(*str == '\"')
            QuotationMarks++;
        if(*str == '[')
            LeftMiddleBrackets++;
        if(*str == '{')
            LeftCurlyBraces++;
        if(*str == ']')
            RightMiddleBrackets++;
        if(*str == '{')
            RightCurlyBraces++;
        if(*str == ',')
            Comma++;
        str++;
    }
    ret->Colon = Colon;
    ret->QuotationMarks = QuotationMarks;
    ret->LeftMiddleBrackets = LeftMiddleBrackets;
    ret->RightMiddleBrackets = RightMiddleBrackets;
    ret->LeftCurlyBraces = LeftCurlyBraces;
    ret->RightCurlyBraces = RightCurlyBraces;
    ret->Comma = Comma;
    return ret;
}

//初始化一个符号链表指针
ListSymbol InitListSymbol()
{
  ListSymbol ret;
  ret = NULL;
  ret = (ListSymbol)malloc(sizeof(struct SymbolList));
  ret->next = NULL;
  ret->symbol = (Symbol)malloc(sizeof(struct SymbolInformation));
  ret->symbol->position = 0;
  ret->symbol->pairposition = 0;
  ret->symbol->symboltype = Prepare;
  return ret;
}
//创建符号链表
void CreatSymbolList(ListSymbol head,const int count)
{
  ListSymbol p;
  ListSymbol ptr;
  p = head;
  int i;
  for(i = 0;i<count;i++)
  {
    ptr = NULL;
    ptr = (ListSymbol)malloc(sizeof(struct SymbolList));
    p->next = ptr;
    ptr->symbol = (Symbol)malloc(sizeof(struct SymbolInformation));
    ptr->symbol->position = 0;
    ptr->symbol->pairposition = 0;
    ptr->symbol->symboltype = Prepare;
    p = ptr;
  }
  p->next = NULL;
}
//构建针对json数据的符号链表
ListSymbol CreatJsonSymbolList(JsonString json)
{
  JsonSymbolGather gather;
  ListSymbol ret,ptr;
  Position position = 0;
  Number  count;//需要添加进入链表的符号个数
  gather = CountSymbol(json);
  count = gather->Comma + gather->LeftMiddleBrackets + gather->LeftCurlyBraces + gather->RightMiddleBrackets + gather->RightCurlyBraces;
  ret = InitListSymbol();
  CreatSymbolList(ret,count);
  ptr = ret->next;
  while(*json != '\0')
  {
      position++;
      if(*json == ',')
          ptr->symbol->symboltype = CommaType;
      if(*json == '[')
          ptr->symbol->symboltype = LeftMiddleBracketsType;
      if(*json == '{')
          ptr->symbol->symboltype = LeftCurlyBracesType;
      if(*json == ']')
          ptr->symbol->symboltype = RightMiddleBracketsType;
      if(*json == '}')
          ptr->symbol->symboltype = RightCurlyBracesType;
      if(*json == ',' || *json == '[' || *json == ']' || *json == '{' || *json == '}')
      {
        ptr->symbol->position = position;
        ptr = ptr->next;
      }

      json++;
  }
    return ret;
}
//统计出字符串中键值对的个数
int JsonObjectCount(JsonString json)
{
  JsonSymbolGather gather;
  gather = CountSymbol(json);
  return gather->Colon;
}
void ShowList(ListSymbol list)
{
  ListSymbol ptr;
  ptr = list->next;
  while(ptr != NULL)
  {
    printf("position = %d,pairposition = %d,type = %d\n",ptr->symbol->position,ptr->symbol->pairposition,ptr->symbol->symboltype);
    ptr = ptr->next;
  }
}
//从数组中找出最大值
int FindMax(int Array[],int count)
{
  int i;
  int max = 0;
  for( i = 0;i<count;i++)
  {
    if(Array[i]>max)
      max = Array[i];
  }
  return max;
}
//从数组中找出除0以外的最小值
int FindMin(int Array[],int count)
{
  int i;
  int min = FindMax(Array,count);
  for(i = 0;i<count;i++)
  {
    if(Array[i]<min && Array[i] != 0)
      min = Array[i];
  }
  return min;
}
//从数组中找出比compare大的最小值
int FindPair(int compare,int Array[],int count)
{
  int i;
  int tarray[count];
  int ret;
  for(i = 0;i<count;i++)
  {
    if(Array[i]>compare)
    {
      tarray[i] = Array[i]; 
    }
    else
      tarray[i] = 0;
  }
  ret = FindMin(tarray,count);
  return ret;
}
//将数组中的最大值置0
void SetMax(int Array[],int count)
{
  int max = FindMax(Array,count);
  int i = 0;
  while(Array[i] != max)
    i++;
  Array[i] = 0;
}
//将数组中值为pair的成员置0
void SetPair(int pair,int Array[])
{
  int min = pair;
  int i = 0;
  while(Array[i] != min)
    i++;
  Array[i] = 0;
}
//判断数组中有几个大于0的数
int PositiveCount(int Array[],int count)
{
  int i;
  int ret = 0;
  for(i = 0;i<count;i++)
  {
    if(Array[i]>0)
      ret++;
  }
  return ret;
}
//完善符号链表中每个符号的另一半的位置
//第一个参数是易读的Json字符串 
//第二个参数是已经完成填值的符号列表 
void SymbolPair(JsonString json,ListSymbol list)
{
  JsonSymbolGather gather;
  ListSymbol ptr = list->next;
  gather = CountSymbol(json);
  Position ML = gather->LeftMiddleBrackets;
  Position MR = gather->RightMiddleBrackets;
  Position CL = gather->LeftCurlyBraces;
  Position CR = gather->RightCurlyBraces;
  Position MidLeft[ML];
  Position MidRight[MR];
  Position CurLeft[CL];
  Position CurRight[CR];
  Position position = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int count = 0;
  int Max = 0;
  int Min = 0;
  while(ptr != NULL)
  {
    if(ptr->symbol->symboltype == LeftMiddleBracketsType)
    {
      MidLeft[i] = ptr->symbol->position;
      i++;
    }
    if(ptr->symbol->symboltype == RightMiddleBracketsType)
    {
      MidRight[j] = ptr->symbol->position;
      j++;
    }
    if(ptr->symbol->symboltype == LeftCurlyBracesType)
    {
      CurLeft[k] = ptr->symbol->position;
      k++;
    }
    if(ptr->symbol->symboltype == RightCurlyBracesType)
    {
      CurRight[l] = ptr->symbol->position;
      l++;
    }
    ptr = ptr->next;
  }
  while((FindMax(MidLeft,ML))>(FindMin(MidRight,MR)))
  {
      position = FindPair(FindMax(MidLeft,ML),MidRight,MR);
      ptr = list->next;
      while(ptr != NULL)
      {
        if(ptr->symbol->position == FindMax(MidLeft,ML))
        {
          ptr->symbol->pairposition = position;
        }
        if(ptr->symbol->position == position)
        {
          ptr->symbol->pairposition = FindMax(MidLeft,ML);
          SetMax(MidLeft,ML);
          SetPair(position,MidRight);
        }
        ptr = ptr->next;
      }
  }
  while((FindMax(CurLeft,CL))>(FindMin(CurRight,CR)))
  {
      position = FindPair(FindMax(CurLeft,CL),CurRight,CR);
      ptr = list->next;
      while(ptr != NULL)
      {     
        if(ptr->symbol->position == FindMax(CurLeft,CL))
        {
          ptr->symbol->pairposition = position;
        }
        if(ptr->symbol->position == position)
        {
          ptr->symbol->pairposition = FindMax(CurLeft,CL);
          SetMax(CurLeft,CL);
          SetPair(position,CurRight);
        }
        ptr = ptr->next;
      }
  }
  count = PositiveCount(MidLeft,ML);
  for(i = 0;i<count;i++)
  {
    Max = FindMax(MidLeft,ML);
    Min = FindMin(MidRight,MR);
    ptr = list->next;
    while(ptr != NULL)
    {
      if(ptr->symbol->position == Max)
      {
        ptr->symbol->pairposition = Min;
      }
      if(ptr->symbol->position == Min)
      {
        ptr->symbol->pairposition = Max;
        SetPair(Max,MidLeft);
        SetPair(Min,MidRight);
      }
      ptr = ptr->next;
    }
  }
  count = PositiveCount(CurLeft,CL);
  for(i = 0;i<count;i++)
  {
    Max = FindMax(CurLeft,CL);
    Min = FindMin(CurRight,CR);
    ptr = list->next;
    while(ptr != NULL)
    {
      if(ptr->symbol->position == Max)
      {
        ptr->symbol->pairposition = Min;
      }
      if(ptr->symbol->position == Min)
      {
        ptr->symbol->pairposition = Max;
        SetPair(Max,CurLeft);
        SetPair(Min,CurRight);
      }
      ptr = ptr->next;
    }
  }
}

//根据传入的位置寻找另一半的位置
Position FindPairPosition(ListSymbol list,Position position)
{
  ListSymbol ptr;
  ptr = list;
  Position ret = 0;
  while(ptr != NULL)
  {
    if(ptr->symbol->position == position)
    {
      ret = ptr->symbol->pairposition;
      break;
    }
    ptr = ptr->next;
  }
  return ret;
}

//判断一个符号是否是键左边的那个引号
bool KeyLeftQuotationMarks(char* ch)
{
  char* ptr = ch;
  bool ret = FALSE;
  if(*ptr == '\"')
  {
    ptr++;
    while(*ptr != '\"'&&*ptr != '\0')
      ptr++;
    if(*ptr == '\"')
    {
      ptr++;
      if(*ptr == ':')
        ret = TRUE;
    }
  }
  return ret;
}

//得到指定键值冒号右边的第一个字符
char GetColonRightChar(LeftColon left)
{
  char* ptr = left;
  char ret;
  ptr++;
  while(*ptr != '\"' && *ptr != '\0')
    ptr++;
  ptr++;
  ptr++;
  ret = *ptr;
  return ret;
}

//得到引号中包含的信息
//参数必须是左引号的地址
//这里函数名错把Quotationmarks写成了Colonl,有空再来改
Information GetJsonColonInformation(LeftColon left)
{
    Information ret;
    char *ptr = left;
    char *p;
    int len = 0,size,i;
    if(*ptr == '\"')
    {
        p = ptr;
        p++;
        while(*p != '\"' && *p != '\0')
        {
            p++;
            len++;
        }
        size = len + 1;
        if(*p == '\0')//冒号必须成对存在
        {
            printf("Colon Format error!\n");
            exit(-1);
        }
        p = (char *)malloc(sizeof(char *)*size);
        bzero(p,size);
        ptr++;
        ret = p;
        for(i = 0;i<len;i++)
        {
            *p = *ptr;
            p++;
            ptr++;
        }
        ret[size]  = '\0';
        return ret;
    }
    else
        return NULL;
}

//针对最简单的对象如“name":"xiaoming"
//通过输入键左边的引号地址，可以获取值
//得到值的字符串
Information GetSimpleObjValue(LeftColon left)
{
  char* ptr = left;
  ptr++;
  while(*ptr != '\"')
    ptr++;
  ptr++;
  ptr++;
  return GetJsonColonInformation(ptr);
}

//得到括号中的内容
//参数1是传入的字符串
//参数2是左括号的位置
//参数3是右括号的位置
Information GetJsonBrackestsInformation(JsonString json,Position leftposition,Position rightposition)
{
  Information ret,temp;
  JsonString ptr;
  Position position = 0;
  int tmp = 0;
  int Size = rightposition - leftposition;
  temp = (JsonString)malloc(sizeof(char)*Size);
  memset(temp,0,Size);
  temp[Size - 1] = '\0';
  ret = temp;
  ptr = json;
  while(*ptr != '\0')
  {
    position++;
    if(position == (leftposition +1))
      tmp = 1;
    if(position == rightposition)
    {
      tmp = 0;
      break;
    }
    if(tmp == 1)
    {
      *temp = *ptr;
      temp++;
    }
    ptr++;
  }
  return ret;
}

/*
char* jsonstr = "\
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
int main()
{
  ListSymbol sblist;
  JsonString  Recv;
  Recv = FormatJsonStorage(jsonstr);//转换为易存储的格式
  sblist = CreatJsonSymbolList(Recv);//创建符号链表
  SymbolPair(Recv,sblist);//完善符号链表
  ShowList(sblist);
//  printf("%d\n",FindPairPosition(sblist,1));
  printf("%s\n",GetJsonBrackestsInformation(Recv,1,302));
  printf("%s\n",GetJsonBrackestsInformation(Recv,12,301));
  printf("%s\n",GetJsonBrackestsInformation(Recv,40,300));
  printf("%s\n",GetJsonBrackestsInformation(Recv,41,105));
  printf("%s\n",GetJsonBrackestsInformation(Recv,74,104));
  printf("%s\n",GetJsonBrackestsInformation(Recv,82,103));
  return 0;
}
*/
