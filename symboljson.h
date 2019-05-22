
#ifndef _SYMBOL_H_
#define _SYMBOL_H_


typedef int Number;
//记录字符串中的各种符号个数
struct JsonSymbol{
    Number Colon;                //冒号
    Number QuotationMarks;       //引号
    Number LeftMiddleBrackets;   //左中括号
    Number RightMiddleBrackets;  //右中括号
    Number LeftCurlyBraces;      //左花括号
    Number RightCurlyBraces;     //右花括号
    Number Comma;                //逗号
};
typedef struct JsonSymbol *JsonSymbolGather;

//构造布尔类型
enum Bool{
  FALSE,TRUE
};
typedef enum Bool bool;

typedef char* Information;
typedef char* LeftColon;
typedef int Position;
typedef char* JsonString;
//构建符号类型枚举
enum SymbolType{
  LeftMiddleBracketsType = 1,  //左中括号
  RightMiddleBracketsType,     //右中括号
  CommaType,                   //逗号
  LeftCurlyBracesType,         //左花括号
  RightCurlyBracesType,        //右花括号
  Prepare                      //初始化
};
typedef enum SymbolType Type;

//构建符号信息结构体
struct SymbolInformation{
  Position position;         //符号在字符串中的位置
  Position pairposition;    //符号的另一半（如[.{的右括号],}）的位置
  Type symboltype;           //符号类型
};
typedef struct SymbolInformation *Symbol;

//构建符号链表
struct SymbolList{
  Symbol symbol;              //符号信息指针
  struct SymbolList *next;    //符号信息链表
};
typedef struct SymbolList *ListSymbol;

//构建针对json数据的符号链表
//传入一个字串，此处用于做字符串解析，方便存储，所以应该用适合存储的格式
//后面的所有函数都是如此
//函数返回一个包含该字符串符号信息的链表
extern ListSymbol CreatJsonSymbolList(JsonString json);

//完善符号链表中每个符号的另一半的位置
//第二个参数是已经完成填值的符号列表 
//本函数的参数必须是Creatjsonsymbollist函数的返回值
//经过本函数处理之后，list函数就是完整的包含json信息的链表
extern void SymbolPair(JsonString json,ListSymbol list);

//判断一个符号是否是键左边的那个引号
bool KeyLeftQuotationMarks(char* ch);

//得到指定键值冒号右边的第一个字符
char GetColonRightChar(LeftColon left);

//得到冒号中包含的信息
//参数必须是左冒号的地址
//返回值就是冒号中的信息，char*
extern Information GetJsonColonInformation(LeftColon left);

//得到括号中的内容
//参数1是传入的字符串
//参数2是左括号的位置
//参数3是右括号的位置
extern Information GetJsonBrackestsInformation(JsonString json,Position leftposition,Position rightposition);

//获取字符串中键值对的个数
extern int JsonObjectCount(JsonString json);

//针对最简单的对象如“name":"xiaoming"
//通过输入键左边的引号地址，可以获取值
//得到值的字符串
extern Information GetSimpleObjValue(LeftColon left);

//根据传入的位置寻找另一半的位置
extern Position FindPairPosition(ListSymbol list,Position position);
//打印出列表中的信息
extern void ShowList(ListSymbol list);

//其他过程函数，一般不用，如果要使用，就取消注释
//数出字符串中各个符号个数
//返回值用一个JsonSymbolGather类型的值，保存了各个符号的个数
//    extern JsonSymbolGather CountSymbol(JsonString str);

//初始化一个符号链表指针
//函数返回一个完成初始化的链表头
//   extern ListSymbol InitListSymbol();

//创建符号链表
//参数就是Initlistsymbol函数返回值和一个count
//返回一个链表，不算头长度为count
//    extern void CreatSymbolList(ListSymbol head,const int count);

//从数组中找出最大值
//    extern int FindMax(int Array[],int count);

//从数组中找出除0以外的最小值
//    extern int FindMin(int Array[],int count);

//从数组中找出比compare大的最小值
//    extern int FindPair(int compare,int Array[],int count);

//将数组中的最大值置0
//    extern void SetMax(int Array[],int count);

//将数组中值为pair的成员置0
//    extern void SetPair(int pair,int Array[]);

//判断数组中有几个大于0的数
//  extern int PositiveCount(int Array[],int count)
#endif

//本模块代码主要是为了存储做准备，所以需要Formatjsonstorage函数处理后的格式
//示例
/*
  JsonString str;
  ListSymbol  list;
  str = FormatJsonSend(jsonstr);
  printf("%s\n",str);
  list = CreatJsonSymbolList(str);
  ShowList(list);
  SymbolPair(str, list);
  ShowList(list);
Information s;
s = GetJsonBrackestsInformation(str,105,274);
*/

