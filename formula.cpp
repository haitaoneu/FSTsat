#include "formula.h"
#include "ui_formula.h"


Formula::Formula(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formula)
{
    ui->setupUi(this);
}

Formula::~Formula()
{
    delete ui;
}


void Formula::GenerateCase(int i)
{
    srand((unsigned int)(time(NULL)));
    while(i!=0)
    {
        GenerateFormula(str);
        i--;
    }
    str=str.left(str.length() - 1);
    str=str.left(str.length() - 1);
    str=str.left(str.length() - 1);
    str=str.left(str.length() - 1);
    str+="#";
    tc.setFormula(str);//传递公式
    Transform(str);
    ui->textBrowser->setText(str);
}

void Formula::Transform(QString &str)
{
    int i=0;
    while(i!=str.length())
    {
//        if(str.at(i)=='!')
//        {
//            str[i]='¬';
//        }
//        if(str.at(i)=='F')
//        {
//            str[i]='◊';
//        }
        if(str.at(i)=='[')
        {
            str[i]='<';
        }
        if(str.at(i)==']')
        {
            str[i]='>';
        }
        i++;
    }
}

void Formula::GenerateSign(QString &str)
{
    QString t1="!! ";
    QString t2="G ";
    QString t3="!F ";
    QString temp;
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

void Formula::Generatef(QString &str)
{
    char t='A'+rand()%(('Z'+1)-'A');//随机生成大写字母
    QString temp="[";
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

void Formula::GenerateFormula(QString &str)
{
    Generatef(str);
    str+=" && ";
    GenerateSign(str);
    Generatef(str);
    str+=" && ";
}

void Formula::on_pushButton_clicked()
{
    this->close();
    tc.ConTab();
    tc.show();

}
