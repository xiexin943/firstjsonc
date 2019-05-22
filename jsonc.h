#ifndef _JSON_H_
#define _JSON_H_

#include "dictlist.h"
#include "formatjson.h"
#include "symboljson.h"

struct JSON{
  JsonString String;
  KeyValueListPtr KeyValueList;
  void (*Show)(JsonString jsonstr);
  DictValue (*GetValue)(struct JSON *jsonobj,DictKey key);
  JsonString (*Ready)(JsonString jsonstr);
};
typedef struct JSON *Json;

//查看字符串函数，输入可以是自定义的也可以是易读的
extern void JsonShow(JsonString jsonstr);

//将json字串转换成易读取的格式
//也就是容易发送的格式
//注意输入不能是易存储的格式
//将自定义格式的字串经过本函数就可以发送了
extern JsonString JsonReady(JsonString jsonstr);

//将json字串转换成易读取的格式
//也就是容易发送的格式
//注意输入不能是易存储的格式
//将自定义格式的字串经过本函数就可以发送了
extern JsonString JsonReady(JsonString jsonstr);

//根据键寻找链表中的值
extern DictValue JsonGetValue(struct JSON *jsonobj,DictKey key);

//过程函数，一般不用，需要使用就取消注释
//将易存储类型的json字符串按照键值对,将键先存储在list中
//第一个参数是完成初始化的双双向链表
//第二个参数是易存储的json字串
//extern void StorageKey(KeyValueListPtr head,JsonString json);

//将易存储类型的json字符串按照键值对,将键先存储在list中
//第一个参数是完成填值的符号链表
//extern void StorageValue(ListSymbol sblist,KeyValueListPtr head,JsonString json);

#endif

//解析库说明：
/*
 * 自定义json的字符串，如果出现同名Key,则会解析出错
 * 自定义json字符串，按照JavaScripts的规则定义即可，但是要在所有冒号和换行的时候加上反斜杠/
 *
 * 必须定义json对象指针，数据类型为Json,注意这是一个指针，调用方法函数必须使用箭头,myjson->Show（）
 * 其余接收键值或者准备发送的变量都可以定义为char*
 */
