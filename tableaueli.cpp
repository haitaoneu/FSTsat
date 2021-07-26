#include "tableaueli.h"
#include "ui_tableaueli.h"

bool Judgerule1(string str);
double Transform(string num);
bool Judgerule2(string str);
bool fuzzyconjudge(int sign1,int sign2,int eql1,int eql2,double n,double m);
void clearFile(string fileName);

tableaueli::tableaueli(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableaueli)
{
    ui->setupUi(this);
    cont=0;
    truthfile.open("truthfile.txt",ofstream::out|ofstream::app);//写入真值文件
}

tableaueli::~tableaueli()
{
    clearFile("myfile.txt");
    clearFile("truthfile.txt");
    delete ui;
}

void tableaueli::Eliminate()
//可以从这个函数开始，对公式进行分割，然后分别进行判断
{
    string str;
    ifstream ifile("myfile.txt");//读文件
    ifstream tfile("truthfile.txt");
    int i,k;
    string temp;
//    bool d;
    while(getline(ifile,str))//按行读取已经建立的tableau,对节点进行标记
    {
        k=0;
        cont++;
//        while(k<str.length())
//        {
//            while(str.at(k)!='#')
//            {
//                temp+=str.at(k);
//                k++;
//            }
//            temp+='#';//截取出来一个公式
//            cout<<temp<<endl;
            if(!Judgerule1(str)||!Judgerule2(str))
            {
                truthfile<<"F";
//                d=false;
            }
            else//如果是可满足节点
            {
                truthfile<<"T";
//                d=true;
            }
//            if(truth.root==NULL)
//            {
//                truth.root->data=d;
//                truth.root->lchild=NULL;
//                truth.root->rchild=NULL;
//                truth.Pointer=truth.root;//Pointer指向root
//            }
//            else//但是这种结构实际上只是一种替代结构，没办法来搞分支
//            {
//                truth.Pointer->lchild->data=d;
//                truth.Pointer->rchild=NULL;
//                truth.Pointer=truth.Pointer->lchild;//指向左节点
//            }
//            k++;
//        }
        truthfile<<endl;//换一行
    }
    i=cont;
    string truth[cont];
    while(i--)
    {
        tfile>>str;
        truth[i]=str;
    }
    for(i=1;i<cont;i++)//通过子节点判断父节点是否应该被消除
    {
        if(truth[i-1]=="F")
        {
            truth[i]="F";
        }
    }
    clearFile("truthfile.txt");//清空文件内容
    for(i=0;i<cont;i++)//按规则重新安排节点
    {
        truthfile<<truth[i]<<endl;
    }
}

bool Judgerule1(string str)//不可满足节点规则1，模糊度必须介于[0,1]之间
//认真看下这个判断函数，其实可以发现，这个判断函数，只能用来判断一条公式的可满足性
{
    int i=0;
    string num;
    double d;//存储模糊度
    while(str.at(i)!='#')
    {
        if(((str.at(i)>='0')&&(str.at(i)<='9'))||(str.at(i)=='.'))
        {
            num+=str.at(i);
        }
        if((str.at(i)==' ')||(i==str.length()-2))
        {
            if(!num.empty())
            {
                d=Transform(num);
                if(d>1)
                {
                    return false;
                }
            }
            num.clear();
        }
        i++;
    }
    return true;
}

double Transform(string num)
{
    double d=0;
    int i=0;
    int len=num.length();
    int cnt=0;
    while(i!=len)
    {
        if(num.at(i)=='.')
        {
            cnt--;
        }
        if((num.at(i)>='0')&&(num.at(i)<='9'))
        {
            d+=(num.at(i)-'0')*pow(10,cnt);
        }
        i++;
    }
    return d;
}

bool Judgerule2(string str)//判断模糊共轭对,模糊共轭对判定的的时候有一点非常关键，就是模糊共轭对是公式断言，他不包括任何其他的符号
{
    int i=0;
    int j;
    int k;
    string temp;//临时存储公式
    string num;//临时存储模糊度
    int eql1=0;//标记公式中是否有等号，有等号标记为1
    int eql2=0;
    int sign1=0;//标记大于号，还是小于号，大于号为0，小于号为1
    int sign2=0;
    double n=0;//模糊度
    double m=0;
    while(str.at(i)!='#')
    {
        if(((str.at(i)=='[')&&((i==0)))||((str.at(i)=='[')&&(str.at(i-2)==',')))//模糊共轭对断言判别，两种可能，一种是[位于公式第一个字符,要么前第二个字符一定是,
        {

            j=i+1;
            while((str.at(j)!='>')&&(str.at(j)!='<'))//截取公式
            {
                temp+=str.at(j);
                j++;
            }
            if(str.at(j)=='<')
            {
                sign1=1;
            }
            if(str.at(j+1)=='=')
            {
                eql1=1;
            }
            while(str.at(j)!=']')//截取模糊度
            {
                if(((str.at(j)>='0')&&(str.at(j)<='9'))||(str.at(j)=='.'))
                {
                    num+=str.at(j);
                }
                j++;
            }
            n=Transform(num);//转换为浮点数
            num.clear();
            i=j-1;//标记j目前的位置
            for(;j<=str.length()-temp.length();j++)//开始匹配后面的公式
            {
                for(k=0;k<temp.length();k++)
                {
                    if(str.at(j+k)!=temp.at(k))
                    {
                        break;
                    }
                }
                if((k==temp.length())&&(str.at(j-3)==','))//匹配到后面公式，且必须是公式断言
                //if(k==temp.length())
                {
//                    cout<<str.at(j-3)<<endl;
                    if(str.at(j+k)=='<')
                    {
                        sign2=1;
                    }
                    if(str.at(j+k+1)=='=')
                    {
                        eql2=1;
                    }
                    while(str.at(j)!=']')//截取模糊度
                    {
                        if(((str.at(j)>='0')&&(str.at(j)<='9'))||(str.at(j)=='.'))
                        {
                            num+=str.at(j);
                        }
                        j++;
                    }
                    m=Transform(num);
                    if(!fuzzyconjudge(sign1,sign2,eql1,eql2,n,m))
                    {
                        return false;
                    }
                }
            }
            temp.clear();
            num.clear();
            eql1=0;
            eql2=0;
            sign1=0;
            sign2=0;
            n=0;
            m=0;//刷新d值
        }
        i++;
//        cout<<str.at(i)<<endl;
    }
    return true;
}

bool fuzzyconjudge(int sign1,int sign2,int eql1,int eql2,double n,double m)
{
    if(sign1==0)//说明第一个是大于
    {
        if(eql1==1)//大于等于
        {
            if(eql2==1)//小于等于
            {
                if(n>m)
                {
                    return true;
                }
            }
            else//小于
            {
                if(n>m||n==m)
                {
                    return true;
                }
            }
        }
        else //大于
        {
               if(n>m||n==m)
               {
                   return true;
               }
        }
    }
    else//说明第一个是小于
    {
        if(eql1==1)//小于等于
        {
            if(eql2==1)//大于等于
            {
                if(n<m)
                    {
                        return true;
                    }
            }
            else//大于
            {
                if(n<m||n==m)
                {
                    return true;
                }
            }
        }
        else//小于
        {
            if(n<m||n==m)
            {
                return true;
            }
         }
     }
}

void clearFile(string fileName)
{
    fstream dmyfile(fileName,ios::out);
    return;
}

void tableaueli::on_pushButton_clicked()
{
    this->close();
    this->~tableaueli();
}

void tableaueli::Painter()//描绘最终图形，并且判断公式可满足性
{
    ifstream tfile("truthfile.txt");
    ifstream ifile("myfile.txt");
    string temp;//读入公式
    string str;//读入节点可满足性;
    QString str1;
    int endjudge=0;//判断根节点可满足性
    getline(tfile,str);
    if(str=="T")//判断根节点可满足性
    {
        endjudge=1;
        ui->lineEdit->setText("The formula is satisfiable.");
    }
    else
    {
        ui->lineEdit->setText("The formula is unsatisfiable.");
    }
    QString t;
    char c='A';
    string c1="a";
    QString c2;
    int i=0;//i行
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(cont);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);//第一列自适应
    while(getline(ifile,temp))//表方式
    {
        c1[0]=c;
        c2=t=QString::fromStdString(c1);
        t=QString::fromStdString(temp);
        str1=QString::fromStdString(str);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(c2));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(t));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(str1));
        getline(tfile,str);
        c++;
        i++;
        qDebug()<<t<<str1;
    }
}
