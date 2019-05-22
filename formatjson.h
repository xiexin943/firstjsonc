#ifndef _FORMATJSON_H_
#define _FORMATJSON_H_

/*表示字串中某个字符的位置*/
typedef int Position;

/*表示计数数值*/
typedef int Frequency;
/*表示自定义,或者接收,或者易存储的json字串*/
typedef char* JsonString;

/*******************/
//将接收到的json字串或者自定义的json字串转换为易存取的格式
/*********************/
extern JsonString FormatJsonStorage(JsonString json);
/**************/
//将自定义的json字串转换为可发送的json字符串
//得到的也是方便展开阅读的格式
//不能将FormatJsonStorage转化过的对象作为参数
//从其他端接收的json字串就是这种格式
extern JsonString FormatJsonSend(JsonString json);

//定义缩进的全局变量
typedef int Indent;
extern Indent indent;

/*******************/
//参数为接收到的字符串或者通过Formatjsonsend函数转换后的字符串
//反正不能是自定义的字符串，自定义的字符串由于空格问题导致不能正常打开
//函数将会以Javascripts的格式展开打印出字符串
//这里打印出来，用于读取，所以特别的，参数要是易读的json
extern void ShowJsonString(JsonString json);


/*其他过程函数，一般不用，如果有需要，可以去掉注释*/

//向字符串中插入一个字符
//第一个参数是传入的字符串指针
//第二个参数是插入的位置，第几个，从1开始
//第三个参数是要插入的字符
//返回值是插入后的字符串
//    extern char * InsertChar(char* str,Position position,char ch)；

//算出冒号后面的值需要添加引号的次数，如,34,35,这样的34就需要两个引号
//返回值是需要插入的个数
//    extern Frequency InsertColonFrequency(JsonString json);

//给Json字符串中冒号后面需要添加引号的地方添加上引号
//返回值是插入后的字符串
//    extern JsonString FormatColonJson(JsonString json);

//算出逗号后面的值需要添加引号的次数
//返回值是需要插入的个数
//    extern Frequency InsertCommaFrequency(JsonString json);

//给Json字符串中逗号后面需要添加引号的地方添加上引号
//返回值是插入后的字符串
//本函数由于遍历算法设计问题，对于如[1,2,3,4]这样连续的,后没有冒号的成员，只能每两个
//添加一个，执行一次结果为["1",2,"3",4,"5"],所以本函数应该执行两次，由于这个是过程函数
//所以在它的调用函数中做了优化，而并未优化本函数
//    extern JsonString FormatCommaJson(JsonString json);

//算出左括号后面的值需要添加引号的次数
//返回值是需要插入的个数
//    extern Frequency InsertMiddleBracketsFrequency(JsonString json);

//给Json字符串中中括号后面需要添加引号的地方添加上引号
//返回值是插入后的字符串
//    extern JsonString FormatMiddleBracketsJson(JsonString json);

//清理掉字符串中的空格字符
//返回值是除掉空格的字符串
//    extern JsonString RemoveSpace(JsonString str);

//换行并且多打印两个个空格
//    extern void NextLineIncrease();
//换行并且少打印两个个空格
//    extern void NextLineReduce();
//换行并且保留原缩进
//    extern void NextLine();



#endif

/****************************************/
//自定义的格式也应该遵循json格式定义
//但是为了满足c语言语法
//需要在换行的时候加上换行符号\
//使用引号的时候必须加上\转义

//下面是一个例子
//可以看到除了加上\表示转义和换行之外，和JavaScripts中的json无任何差别

/*******************
 


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

**********/


