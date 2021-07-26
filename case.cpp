#include <iostream>
#include <string>
#include <cstdlib>
//#include <ctime>
//#include <fstream>
using namespace std;
//公式形如 [C(a)>=0.7] && !! [C(b)<=0.6] && G [R(a,b)>=0.8] && !F [DC(a,b)>=0.8] && [R(a,b)<=0.7]#
//由公式断言构成


void GenerateSign(string &str)
{
    string t1="!! ";
    string t2="G ";
    string t3="!F ";
    string temp;
    int i=rand()%3;
    if(i==0)
    {
        temp="!! ";
    }
    else if(i==1)
    {
        temp="G ";
    }
    else if(i==2)
    {
        temp="!F ";
    }
    else
    {
        temp=" ";
    }
    str+=temp;
}

void Generatef(string &str)
{
    char t='A'+rand()%(('Z'+1)-'A');//随机生成大写字母
    string temp="[";
    temp=temp+t+"(";
    t='a'+rand()%(('z'+1)-'a');
    temp=temp+t+")";
    int i=rand()%3;
    if(i==0)
    {
        temp+=">=";
    }
    else if(i==1)
    {
        temp+="<=";
    }
    else if(i==2)
    {
        temp+=">";
    }
    else
    {
        temp+="<";
    }
    i=rand()%1;
    if(i==0)
    {
        temp+="0";
    }
    else
    {
        temp+="1";
    }
    temp+=".";
    i=rand()%9;
    char c=i+'0';
    temp+=c;
    temp+="]";
    str+=temp;
}

void GenerateFormula(string &str)
{
    Generatef(str);
    str+=" && ";
    GenerateSign(str);
    Generatef(str);
    str+=" && ";
}

//int main()
//{
//    string str;
//    srand((unsigned int)(time(NULL)));
//    int i=1000;
//    while(i!=0)
//    {
//        GenerateFormula(str);
//        i--;
//    }
//    str.pop_back();
//    str.pop_back();
//    str.pop_back();
//    str.pop_back();
//    str+="#";
//    ofstream casefile;
//    casefile.open("case.txt",ofstream::out|ofstream::app);
//    casefile<<str<<endl;
//    cout<<str<<endl;
//}
