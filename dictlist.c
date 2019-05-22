#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictlist.h"

char* True = "True";
char* False = "False";
char* None = "None";

//函数声明
KeyValueListPtr InitKeyValueList();
void Relation(KeyValueListPtr kvlist,KeyNodePtr keyhead,ValueNodePtr valuehead);
KeyValueListPtr CreatKeyValueList(const int count);
void SetKeyValueList(KeyValueListPtr kylist,DictKey key,DictValue value,Position position);
DictKeyValue GetKeyValueList(KeyValueListPtr kylist,Position position);
void ShowKeyVlaueList(KeyValueListPtr kylist);



//返回一个完成初始化的KeyValueList类型的变量
KeyValueListPtr InitKeyValueList()
{
    KeyValueListPtr kvlist;
    kvlist = (KeyValueListPtr)malloc(sizeof(struct KeyValueList));
    kvlist->len  = 0;
    kvlist->keyhead = NULL;
    kvlist->valuehead = NULL;
    return kvlist;
}
//创建或更新键值对链表和键值对关系链表的关联
//第一个参数是键值对链表信息结构体变量
//第二个参数是键链表变量
//第三个参数是值链表变量
void Relation(KeyValueListPtr kvlist,KeyNodePtr keyhead,ValueNodePtr valuehead)
{
    KeyNodePtr keyptr = keyhead->Next;
    int len;
    while(keyptr != keyhead)
    {
        keyptr = keyptr->Next;
        len++;
    }
    kvlist->keyhead = keyhead;
    kvlist->valuehead = valuehead;
    kvlist->len = len;
}
//创建键值对列表
//键链表和值链表都设计为环形
//参数是选择链表长度
//键链表和值链表都是一样长
KeyValueListPtr CreatKeyValueList(const int count)
{
    KeyValueListPtr ret;
    KeyNodePtr keytemp,keyptr;
    ValueNodePtr valuetemp,valueptr;
    int i;
    ret = InitKeyValueList();
    ret->keyhead = (KeyNodePtr)malloc(sizeof(struct KeyNode));
    ret->valuehead = (ValueNodePtr)malloc(sizeof(struct ValueNode));
    if(ret->keyhead == NULL||ret->valuehead == NULL)
    {
        printf("Memory malloc error!\n");
        exit(-1);
    }
    ret->keyhead->key = NULL;
    ret->keyhead->Prev = NULL;
    ret->keyhead->Next = NULL;
    ret->valuehead->value = NULL;
    ret->valuehead->Prev = NULL;
    ret->valuehead->Next = NULL;
    keytemp = ret->keyhead;
    valuetemp  = ret->valuehead;
    for(i = 0;i<count;i++)
    {
        keyptr = (KeyNodePtr)malloc(sizeof(struct KeyNode));
        valueptr = (ValueNodePtr)malloc(sizeof(struct ValueNode));
        if(keyptr == NULL||valueptr == NULL)
        {
            printf("Memory malloc error!\n");
            exit(-1);
        }
        keytemp->Next = keyptr;
        keyptr->Prev = keytemp;
        keyptr->Next = NULL;
        keyptr->key = NULL;
        keytemp = keyptr;

        valuetemp->Next = valueptr;
        valueptr->Prev = valuetemp;
        valueptr->Next = NULL;
        valueptr->value = NULL;
        valuetemp = valueptr;
    }
    ret->keyhead->Prev = keyptr;
    keyptr->Next = ret->keyhead;

    ret->valuehead->Prev = valueptr;
    valueptr->Next = ret->valuehead;
    Relation(ret,ret->keyhead,ret->valuehead);
    return ret;
}
//给键值对赋值
void SetKeyValueList(KeyValueListPtr kylist,DictKey key,DictValue value,Position position)
{
    KeyNodePtr keyptr = kylist->keyhead->Next;
    ValueNodePtr valueptr = kylist->valuehead->Next;
    int i;
    for(i = 0;i<position - 1;i++)
    {
        keyptr = keyptr->Next;
        valueptr = valueptr->Next;
    }

    keyptr->key = key;
    valueptr->value = value;
}
//按位置读取键值对的值
DictKeyValue GetKeyValueList(KeyValueListPtr kylist,Position position)
{
    KeyNodePtr keyptr = kylist->keyhead->Next;
    ValueNodePtr valueptr = kylist->valuehead->Next;
    DictKeyValue ret;
    ret = (DictKeyValue)malloc(sizeof(struct KeyValue));
    bzero(ret,sizeof(struct KeyValue));
    int i;
    for(i = 0;i<position - 1;i++)
    {
        keyptr = keyptr->Next;
        valueptr = valueptr->Next;
    }
    ret->key = keyptr->key;
    ret->value = valueptr->value;
    return ret;
}
//打印出链表的值
void ShowKeyVlaueList(KeyValueListPtr kylist)
{
  KeyNodePtr keyptr = kylist->keyhead->Next;
  ValueNodePtr valueptr = kylist->valuehead->Next;
  while(keyptr != kylist->keyhead)
  {
    printf("key = %s,",keyptr->key);
    printf("value = %s\n",valueptr->value);
    keyptr = keyptr->Next;
    valueptr = valueptr->Next;
  }
}


