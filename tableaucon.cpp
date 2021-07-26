#include "tableaucon.h"
#include "ui_tableaucon.h"

void Move(QString &str,int j);
void Delete(QString &f);
//void clearFile(string fileName);

tableaucon::tableaucon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableaucon)
{
    ui->setupUi(this);
    flag=0;
    cont=0;
    confile.open("myfile.txt",ofstream::out|ofstream::app);
    qDebug()<<"con";
}

tableaucon::~tableaucon()
{
    delete ui;
}

//void clearFile(string fileName)
//{
//    fstream dmyfile(fileName,ios::out);
//    return;
//}

void Move(QString &str,int j)
{
    while(str[j]!='#')
    {
        str[j]=str[j+1];
        j++;
    }
    Delete(str);
}

void Delete(QString &f)
{
    while(f.back()=='#')
    {
        f=f.left(f.length() - 1);
    }
    f.append("#");
}

void tableaucon::setFormula(QString str)
{
    f=str;
    string temp;

    temp=f.toStdString();
    confile<<temp<<"\n";
    cont=1;
}

void tableaucon::ConTab()
{
    qDebug()<<f<<"进来了";
    Alpha();
//    Beta();
    Painter();
}

void tableaucon::Alpha()//α规则的逻辑，并非是一种提前读取的逻辑，而是说读到谁算谁
{
    int i=0;
    int j=0;
    while(f.at(i)!='#')//r1规则
    {
        if(f.at(i)=='!')
        {
            if(f.at(i+1)=='!')
            {
                j=i+1;
                Move(f,j);
                j=i;
                Move(f,j);
                j=i-1;
                Move(f,j);
                flag=1;
            }
        }
        i++;
    }
    Print();

    i=0;
    while(f.at(i)!='#')
    {
        if(f.at(i)=='&')
        {
            if(f.at(i+1)=='&') //r2规则
            {
                f[i]=',';
                j=i+1;
                Move(f,j);
                flag=1;
            }
        }
        i++;
    }
    Print();

    i=0;
    while(f.at(i)!='#')
    {
        if(f.at(i)=='G')//r3规则，与r9规则相区分
        {
            if(f.at(i-1)!='!')
            {
                j=i;
                Move(f,j);
                Move(f,j);
                flag=1;
                int k=i;
                QString str=" , og ";
                while(f.at(k)!=' '&&(f.at(k)!='#'))
                {
                    str+=f.at(k);
                    k++;
                }
                Delete(f);
                f=f.left(f.length() - 1);
                f.append(str);
                f.append("#");
            }
        }
        i++;
    }
    Print();

    i=0;
    while(f.at(i)!='#')
    {
        if(f.at(i)=='!')
        {
            if(f.at(i+1)=='F')//r4规则
            {
                j=i+1;
                Move(f,j);
                flag=1;
                int k=i+2;
                QString str=" , !of ";
                while((f.at(k)!=' ')&&(f.at(k)!='#'))
                {
                    str+=f.at(k);
                    k++;
                }
                Delete(f);
                f=f.left(f.length() - 1);
                f.append(str);
                f.append("#");
            }
        }
        i++;
    }
    Print();
}

void tableaucon::Print()//将公式写入文件
{
    if(flag==1)
    {
        Delete(f);
    }
    flag=0;
    string temp;
    QString str;
    temp=f.toStdString();
    str=QString::fromStdString(temp);
    confile<<temp<<"\n";
    cont++;
}

void tableaucon::Painter()//将写入文件的公式放在视图里
{
    readfile.open("myfile.txt");
    string temp;
    QString t;
    char c='A';
    string c1="a";
    QString c2;
    int i=0;//i行
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(cont);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);//自适应
    while(getline(readfile,temp))//表方式
    {
        c1[0]=c;
        c2=t=QString::fromStdString(c1);
        t=QString::fromStdString(temp);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(c2));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(t));
        c++;
        i++;
        qDebug()<<t;
    }
}

void tableaucon::on_pushButton_clicked()
{
    this->close();
    te.show();
    te.Eliminate();
    te.Painter();
}
