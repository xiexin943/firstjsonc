#ifndef _DICTLIST_H_
#define _DICTLIST_H_

//类似python的dict数据结构
//输入值为数值的时候需要加上引号”““
typedef int Position;

extern char* True;
extern char* False;
extern char* None;

typedef char* DictKey;
typedef char* DictValue;

//创建键值对结构体
struct KeyValue{
    DictKey key;
    DictValue value;
};
typedef struct KeyValue *DictKeyValue;
//创建键链表结构体
struct KeyNode{
    DictKey key;
    struct KeyNode *Prev;
    struct KeyNode *Next;
};
typedef struct KeyNode *KeyNodePtr;
//创建值链表结构体
struct ValueNode{
    DictValue value;
    struct ValueNode *Prev;
    struct ValueNode *Next;
};
typedef struct ValueNode *ValueNodePtr; 

//创建键值对列表
struct KeyValueList{
    int len;
    KeyNodePtr      keyhead;
    ValueNodePtr    valuehead;
};
typedef struct KeyValueList *KeyValueListPtr;

/************
 * 创建一个键值对列表
 * 参数是选择长度
 * 返回值必须用KeyValueListPtr类型接收
 * ********/ 
extern KeyValueListPtr CreatKeyValueList(const int count);

/***********
 * 给键值对添加值
 * 第一个参数是键值对指针
 * 第二个参数是键 
 * 第三个参数是键对应的值
 * 第四个参数是添加的位置
 * ************/
extern void SetKeyValueList(KeyValueListPtr kylist,DictKey key,DictValue value,Position position);
/*************
 * 根据位置获取节点的值或键
 * 第一个参数是键值对指针
 * 第二个参数是需要获取的位置
 * 返回包含键值对的变量
 * *********/ 
extern DictKeyValue GetKeyValueList(KeyValueListPtr kylist,Position position);

//打印出链表的值
extern void ShowKeyVlaueList(KeyValueListPtr kylist);
//其他过程函数，一般不用，如果要使用，就取消注释


//返回一个完成初始化的KeyValueList类型的变量
//    extern KeyValueListPtr InitKeyValueList();

//创建或更新键值对链表和键值对关系链表的关联
//第一个参数是键值对链表信息结构体变量
//第二个参数是键链表变量
//第三个参数是值链表变量
//  extern void Relation(KeyValueListPtr kvlist,KeyNodePtr keyhead,ValueNodePtr valuehead);

#endif

/*************
 * 使用示例
 * *********/
/*
 
int main()
{
    KeyValueListPtr list;
    list = CreatKeyValueList(6);
    SetKeyValueList(list,"name","xiaoming",1);
    SetKeyValueList(list,"sex","mam",2);
    SetKeyValueList(list,"school","dongruan",3);
    SetKeyValueList(list,"age","20",4);
    SetKeyValueList(list,"appearance","headsome",5);
    SetKeyValueList(list,True,False,6);
    DictKeyValue s;
    s = GetKeyValueList(list,1);
    printf("key = %s,value = %s\n",s->key,s->value);
    s = GetKeyValueList(list,2);
    printf("key = %s,value = %s\n",s->key,s->value);
    s = GetKeyValueList(list,3);
    printf("key = %s,value = %s\n",s->key,s->value);
    s = GetKeyValueList(list,4);
    printf("key = %s,value = %s\n",s->key,s->value);
    s = GetKeyValueList(list,5);
    printf("key = %s,value = %s\n",s->key,s->value);
    s = GetKeyValueList(list,6);
    printf("key = %s,value = %s\n",s->key,s->value);
    return 0;
}
*/

