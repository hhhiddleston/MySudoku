#include "mainwindow.h"
#include <QCoreApplication>
#include <solver.h>
//#include <time.h>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            square[i][j] = new QPushButton("",this);
            connect(square[i][j],SIGNAL(released()),this,SLOT(squareClicked()));
        }

    for (int i=0;i<9;++i)
    {
        number[i]=new QPushButton(QString::number(i+1),this);
        connect(number[i],SIGNAL(released()),this,SLOT(numberClicked()));
    }

    emtyButton = new QPushButton("Empty",this);
    emtyButton->setGeometry(QRect(QPoint(25,460),QSize(150,40)));
    connect(emtyButton,SIGNAL(released()),this,SLOT(emtyClicked()));

    solveButton = new QPushButton("Solve",this);
    solveButton->setGeometry(QRect(QPoint(200,340),QSize(115,67)));
    connect(solveButton,SIGNAL(released()),this,SLOT(solveClicked()));

    clearButton = new QPushButton("Clear",this);
    clearButton->setGeometry(QRect(QPoint(200,433),QSize(115,67)));
    connect(clearButton,SIGNAL(released()),this,SLOT(clearClicked()));

    TrymyselfButton = new QPushButton("Try for myself",this);
    TrymyselfButton->setGeometry(QRect(QPoint(25,510),QSize(230,40)));

    easyButton = new QPushButton("Easy",this);
    easyButton->setGeometry(QRect(QPoint(25,560),QSize(100,40)));
    connect(easyButton,SIGNAL(released()),this,SLOT(easyClicked()));

    middleButton = new QPushButton("Middle",this);
    middleButton->setGeometry(QRect(QPoint(125,560),QSize(100,40)));
    connect(middleButton,SIGNAL(released()),this,SLOT(middleClicked()));

    hardButton = new QPushButton("Hard",this);
    hardButton->setGeometry(QRect(QPoint(225,560),QSize(100,40)));
    connect(hardButton,SIGNAL(released()),this,SLOT(hardClicked()));

    helpButton = new QPushButton("Help",this);
    helpButton->setGeometry(QRect(QPoint(250,510),QSize(80,40)));
    connect(helpButton,SIGNAL(released()),this,SLOT(helpClicked()));

    redText = new QPalette();
    redText->setColor(QPalette::ButtonText,Qt::red);

    whiteText = new QPalette();
    whiteText->setColor(QPalette::ButtonText,Qt::white);

    blackText = new QPalette();
    blackText->setColor(QPalette::ButtonText,Qt::black);

    setSquareGeo();
    setNumberGeo();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setSquareGeo()//设置数独在界面上的位置
{
    int x,y;
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            int a=0,b=0;
            if(i>2&&i<6)
                a=10;
            if(i>5)
                a=20;
            if(j>2&&j<6)
                b=10;
            if(j>5)
                b=20;
            x=a+25+i*30;
            y=b+25+j*30;
            square[i][j]->setGeometry(QRect(QPoint(x,y),QSize(30,30)));
                square[i][j]->setStyleSheet("background-color: gray");
        }
}

void MainWindow::setNumberGeo()//设置数字在界面上的位置
{
    for (int i=0;i<3;++i)
        number[i]->setGeometry(QRect(QPoint(25+i*50,420),QSize(50,40)));
    for (int i=3;i<6;++i)
        number[i]->setGeometry(QRect(QPoint(25+(i-3)*50,380),QSize(50,40)));
    for (int i=6;i<9;++i)
        number[i]->setGeometry(QRect(QPoint(25+(i-6)*50,340),QSize(50,40)));
}

void MainWindow::numberClicked()
{
    QPushButton *virButton =(QPushButton *)sender();
    value=virButton->text();
}

void MainWindow::emtyClicked()
{
    value="";
}

void MainWindow::squareClicked()
{
    int count=0;
    QPushButton *virSquare =(QPushButton *)sender();
    virSquare->setText(value);
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            if(square[i][j]->text()=="")//将界面上的数字放到二维数组里面去
                grid[i][j]='0';
            else
            {
            int x = QString(square[i][j]->text())[0].unicode();
            grid[i][j]=(char)x;
            }
        }
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            if(square[i][j]->isEnabled())
            {
                 //qDebug("able");

            if(identical_row(grid, i, j) + identical_collumn(grid, i, j) + identical_block(grid, i, j) == 0)
            {
                square[i][j]->setPalette(*blackText);
                //qDebug("yeah");
            }
            if(identical_row(grid, i, j) + identical_collumn(grid, i, j) + identical_block(grid, i, j) != 0)
            {
                square[i][j]->setPalette(*redText);
                qDebug("ooops");
                count++;
            }
            }
}
    //square[i][j]->setPalette((*blackText));
    //if(identical_row(grid, flagr, flagc) + identical_collumn(grid, flagr, flagc) + identical_block(grid, flagr, flagc) != 0)
        //square[flagr][flagc]->setPalette(*redText);//若出现重复数字则变红表示警示
    if(count>2){
    QMessageBox::information(this, QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("冲突处较多，请仔细检查后修改当前数字！"));
}
}


void MainWindow::clearClicked()
{
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            square[i][j]->setEnabled(true);
            value="";
            square[i][j]->setText(value);
            square[i][j]->setPalette(*blackText);
            grid[i][j]='\0';
        }
     solveButton->setEnabled(true);
}


void MainWindow::solveClicked()
{
    int l;
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            if(square[i][j]->text()=="")//将界面上的数字放到二维数组里面去求解
                grid[i][j]='0';
            else
            {
            int x = QString(square[i][j]->text())[0].unicode();
            grid[i][j]=(char)x;
            }
        }

    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            square[i][j]->setEnabled(false);
            square[i][j]->setPalette(*blackText);
        }
    solveButton->setEnabled(false);
    char workingArr[9][9];
    copyGrid(workingArr);

    //clock_t a=clock();
    l = solve2(0,workingArr, workingArr);
    //clock_t b=clock();
    //double totalTime = (b-a)/CLOCKS_PER_SEC;//***********************记录解数独所用时间*/
    setGrid(workingArr);
    display();
    if(l==0)
    {
        qDebug("no answer");
        QMessageBox::information(this, QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("数独无解！请输入符合要求的数独！"));
    }
    if(l==2)
    {qDebug("many");
        QMessageBox::information(this, QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("数独不是唯一解！"));}
    if(l==1)
        qDebug("one");
}

char answer[9][9];
void MainWindow::easyClicked()
{
    char workingArrr[9][9];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            workingArrr[i][j]='0';
            answer[i][j]='0';
        }
    easy(workingArrr,answer);
    for(int i=0;i<9;i++) //将空缺数独显示到屏幕上
        for(int j=0;j<9;j++){
            if(workingArrr[i][j]=='0')
            {
                square[i][j]->setEnabled(true);
                square[i][j]->setText("");
                qDebug("settrue!");
            }
            else
            {
                square[i][j]->setEnabled(false);
                square[i][j]->setPalette(*whiteText);
                //qDebug("dis"); //no problem
                square[i][j]->setText(QString(workingArrr[i][j]));
            }
        }
    solveButton->setEnabled(false);

}

void MainWindow::helpClicked()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(square[i][j]->isEnabled())
            {
                square[i][j]->setPalette(*blackText);
                square[i][j]->setText(QString(answer[i][j]));
            }
        }
}

void MainWindow::middleClicked()
{
    //char answer[9][9];
    char workingArrr[9][9];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            workingArrr[i][j]='0';
            answer[i][j]='0';
        }
    middle(workingArrr,answer);
    //setGrid(answer);
    for(int i=0;i<9;i++) //将空缺数独显示到屏幕上
        for(int j=0;j<9;j++){
            if(workingArrr[i][j]=='0')
                square[i][j]->setText("");
            else
            {
                square[i][j]->setText(QString(workingArrr[i][j]));
                square[i][j]->setEnabled(false);
                square[i][j]->setPalette(*whiteText);
            }
        }
    solveButton->setEnabled(false);
}

void MainWindow::hardClicked()
{
    //char answer[9][9];
    char workingArrr[9][9];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            workingArrr[i][j]='0';
            answer[i][j]='0';
        }
    hard(workingArrr,answer);
    //setGrid(answer);
    for(int i=0;i<9;i++) //将空缺数独显示到屏幕上
        for(int j=0;j<9;j++){
            if(workingArrr[i][j]=='0')
                square[i][j]->setText("");
            else
            {
                square[i][j]->setText(QString(workingArrr[i][j]));
                square[i][j]->setEnabled(false);
                square[i][j]->setPalette(*whiteText);
            }
        }
    solveButton->setEnabled(false);
}

void MainWindow::display()
{
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            if(square[i][j]->text() == "")
            {
            square[i][j]->setText(QString(grid[i][j]));
            square[i][j]->setPalette(*whiteText);//设置填入数字的颜色
            }

        }
}

void MainWindow::setGrid(char arr[9][9])
{
   memcpy(grid, arr, sizeof(char) * 9 * 9);
}

void MainWindow::copyGrid(char arr[9][9])
{
   memcpy(arr, grid, sizeof(char) * 9 * 9);
}
