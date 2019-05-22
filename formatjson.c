#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatjson.h"


//函数声明
char * InsertChar(char* str,Position position,char ch);
Frequency InsertColonFrequency(JsonString json);
JsonString FormatColonJson(JsonString json);
Frequency InsertCommaFrequency(JsonString json);
JsonString FormatCommaJson(JsonString json);
Frequency InsertMiddleBracketsFrequency(JsonString json);
JsonString FormatMiddleBracketsJson(JsonString json);
JsonString RemoveSpace(JsonString str);
void NextLineIncrease();
void NextLineReduce();
void NextLine();
void ShowJsonString(JsonString json);
JsonString FormatJsonStorage(JsonString json);
JsonString FormatJsonSend(JsonString json);


/*用于将json字符串转换成c语言字符串*/
//算出冒号后面的值需要添加引号的次数
//向字符串中插入一个字符
char * InsertChar(char* str,Position position,char ch)
{
    char* ptr = str;
    int len,i,size;
    while(*ptr != '\0')
    {
        ptr++;
        len++;
    }
    if(position>len)
    {
        printf("Position error!\n");
        exit(-1);
    }
    size = len + 2;
    char *ret;
    ret = (char *)malloc(sizeof(char)*size);
    bzero(ret,size);
    for(i = 0;i<position - 1;i++)
    {
        *ret = *str;
        ret++;
        str++;
    }
    *ret = ch;
    ret++;
    i++;
    for(;i<size - 1;i++)
    {
        *ret = *str;
        ret++;
        str++;
    }
    for(;i > 0;i--)
        ret --;
    return ret;
}
//算出冒号后面的值需要添加引号的次数
Frequency InsertColonFrequency(JsonString json)
{
    JsonString str = json;
    Frequency count = 0;
    while(*str != '\0')
    {
        if(*str == ':')
        {
            str++;
            if(*str != '[' && *str != '{' && *str != '\"')//需要添加引号的地方
            {
                count++;
                while(1)
                {
                    str++;
                    if(*str == ',' || *str == '}' || *str == ']')
                    {
                        count++;
                        break;
                    }
                }
            }           
        }
        str++;
    }
    return count;
}
//给Json字符串添加上引号
JsonString FormatColonJson(JsonString json)
{
    JsonString str = json;
    Position position = 0;
    Frequency count = InsertColonFrequency(json);
    int ppos[count],i,j;
    bzero(ppos,sizeof(int)*count);
    count = 0;
    while(*str != '\0')
    {
        position++;
        if(*str == ':')
        {
            str++;
            position++;
            if(*str != '[' && *str != '{' && *str != '\"')//需要添加引号的地方
            {
                ppos[count] = position;
                count++;
                while(1)
                {
                    str++;
                    position++;
                    if(*str == ',' || *str == '}' || *str == ']')
                    {
                        ppos[count] = position;
                        count++;
                        break;
                    }
                }
            }           
        }
        str++;
    }
    for(i = 0;i<count;i++)
    {
        json = InsertChar(json,ppos[i],'\"');
        for(j = i;j<count;j++)
            ppos[j] = ppos[j]+1;
    }
    return json;
}


Frequency InsertCommaFrequency(JsonString json)
{
    JsonString str = json;
    Frequency count = 0;
    while(*str != '\0')
    {
        if(*str == ',')
        {
            str++;
            if(*str != '[' && *str != '{' && *str != '\"')//需要添加引号的地方
            {
                count++;
                while(1)
                {
                    str++;
                    if(*str == ',' || *str == '}' || *str == ']')
                    {
                        count++;
                        break;
                    }
                }
            }           
        }
        str++;
    }
    return count;
}
//给Json字符串添加上引号
JsonString FormatCommaJson(JsonString json)
{
    JsonString str = json;
    Position position = 0;
    Frequency count = InsertCommaFrequency(json);
    int ppos[count],i,j;
    bzero(ppos,sizeof(int)*count);
    count = 0;
    while(*str != '\0')
    {
        position++;
        if(*str == ',')
        {
            str++;
            position++;
            if(*str != '[' && *str != '{' && *str != '\"')//需要添加引号的地方
            {
                ppos[count] = position;
                count++;
                while(1)
                {
                    str++;
                    position++;
                    if(*str == ',' || *str == '}' || *str == ']')
                    {
                        ppos[count] = position;
                        count++;
                        break;
                    }
                }
            }           
        }
        str++;
    }
    for(i = 0;i<count;i++)
    {
        json = InsertChar(json,ppos[i],'\"');
        for(j = i;j<count;j++)
            ppos[j] = ppos[j]+1;
    }
    return json;
}
//[后应该添加的冒号
Frequency InsertMiddleBracketsFrequency(JsonString json)
{
    JsonString str = json;
    Frequency count = 0;
    while(*str != '\0')
    {
        if(*str == '[')
        {
            str++;
            if( *str != '{' && *str != '\"')//需要添加引号的地方
            {
                count++;
                while(1)
                {
                    str++;
                    if(*str == ','  || *str == ']')
                    {
                        count++;
                        break;
                    }
                }
            }           
        }
        str++;
    }
    return count;
}
//给Json字符串添加上引号
JsonString FormatMiddleBracketsJson(JsonString json)
{
    JsonString str = json;
    Position position = 0;
    Frequency count = InsertMiddleBracketsFrequency(json);
    int ppos[count],i,j;
    bzero(ppos,sizeof(int)*count);
    count = 0;
    while(*str != '\0')
    {
        position++;
        if(*str == '[')
        {
            str++;
            position++;
            if(*str != '{' && *str != '\"')//需要添加引号的地方
            {
                ppos[count] = position;
                count++;
                while(1)
                {
                    str++;
                    position++;
                    if(*str == ',' || *str == '}' || *str == ']')
                    {
                        ppos[count] = position;
                        count++;
                        break;
                    }
                }
            }           
        }
        str++;
    }
    for(i = 0;i<count;i++)
    {
        json = InsertChar(json,ppos[i],'\"');
        for(j = i;j<count;j++)
            ppos[j] = ppos[j]+1;
    }
    return json;
}
//清理掉字串中的空格
JsonString RemoveSpace(JsonString str)
{
    JsonString ret;
    JsonString p = str;
    int size = 0;
    while(*p != '\0')
    {
        if(*p != ' ')
            size++;
        p++;
    }
    size++;
    ret = (JsonString)malloc(sizeof(char)*size);
    bzero(ret,size);
    while(*str != '\0')
    {
        if(*str != ' ')
        {
            *ret = *str;
            ret++;
        }
        str++;
    }
    *ret = '\0';
    for(;size>1;size--)
        ret--;
    return ret;
}
Indent indent = 0;
//换行并且多打印两个个空格
void NextLineIncrease()
{
  int i;
  indent = indent + 2;
  printf("\n");
  for(i = 0;i<indent;i++)
    printf(" ");
}
//换行并且少打印两个个空格
void NextLineReduce()
{
  int i;
  indent = indent - 2;
  printf("\n");
  for(i = 0;i<indent;i++)
    printf(" ");
}
//换行并且保留原缩进
void NextLine()
{
  int i;
  printf("\n");
  for(i = 0;i<indent;i++)
    printf(" ");
}
//将容易读取的格式展开json字符串
void ShowJsonString(JsonString json)
{
  JsonString ch;
  char ret;
  JsonString chtemp;
  ch = json;
  indent = 0;
  while(*ch != '\0')
  {
    ret = *ch;
    printf("%c",ret);
    if(*ch == '{')
      NextLineIncrease();
    if(*ch == ']')
    {
      chtemp = ch;
      chtemp++;
      if(*chtemp != ',')
        NextLineReduce();
    }
    if(*ch == '}')
    {
      chtemp = ch;
      chtemp++;
      if(*chtemp != ',' && *chtemp != ']')
        NextLineReduce();
    }
    if(*ch == ',')
    {
      chtemp = ch;
      chtemp++;
      if(*chtemp == '\"')
      {
        chtemp++;
        while(*chtemp != '\"')
          chtemp++;
          chtemp++;
        if(*chtemp == ':')
          NextLine();
      }
    }
    ch++;
  }
  printf("\n");
}
//将接收到的json字串或者自定义的json字串转换为易存取的格式
JsonString FormatJsonStorage(JsonString json)
{
    JsonString ret;
    ret = RemoveSpace(json);//清空空格
    ret = FormatColonJson(ret);
    ret = FormatColonJson(ret);
    ret = FormatCommaJson(ret);
    ret = FormatCommaJson(ret);
    ret = FormatMiddleBracketsJson(ret);
    ret = FormatMiddleBracketsJson(ret);
    return ret;
}
//将自定义的json字串转换为可发送和易阅读的json字符串
JsonString FormatJsonSend(JsonString json)
{
    JsonString ret;
    ret = RemoveSpace(json);
    return ret;
}

