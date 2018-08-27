#include "widget.h"
#include "ui_widget.h"

#include <QTableWidgetItem>
#include<QDateTimeEdit>
#include<QLayout>
#include<QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);
    tableWidget =new QTableWidget(this);
    tableWidget->horizontalScrollBar()->hide();
    tableWidget->setColumnCount(5);
  //  tableWidget->setRowCount(11);
    /* 设置 tableWidget */
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Id" << "Name" << "Unit" << "Value" << "Min");
    tableWidget->verticalHeader()->setVisible(false); // 隐藏水平header
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);   // 单个选中
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个
    num=0;
    flag=true;
    buttonChoose=new QPushButton(this);
    buttonUnChoose=new QPushButton(this);
    buttonSend=new QPushButton(this);
    buttonStart=new QPushButton(this);
    buttonEnd=new QPushButton(this);
    buttonStart->setText("开始");
    buttonEnd->setText("结束");
    buttonChoose->setText("全选");
    buttonUnChoose->setText("反选");
    buttonSend->setText("发送");
    verticalScrollBar=tableWidget->verticalScrollBar();
    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(buttonChoose);
    hLayout->addWidget(buttonUnChoose);
    hLayout->addWidget(buttonSend);
    hLayout->addWidget(buttonStart);
    hLayout->addWidget(buttonEnd);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *pLayout = new QGridLayout();
    pLayout->addWidget(tableWidget);
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(pLayout);
    setLayout(mainLayout);
    connect(buttonChoose,SIGNAL(clicked()),this, SLOT(pushButtonChoose_clicked()));
    connect(buttonUnChoose,SIGNAL(clicked()),this, SLOT(pushButtonUnchoose_clicked()));
    connect(buttonSend,SIGNAL(clicked()),this, SLOT(pushButtone_send()));
    connect(buttonStart,SIGNAL(clicked()),this,SLOT(pushButtonstart_clicked()));
    connect(buttonEnd,SIGNAL(clicked()),this,SLOT(pushButtonend_clicked()));
    connect(verticalScrollBar, SIGNAL(valueChanged(int)),this,SLOT(onScrollBarValueChanged(int)));
    //只要定时器启动，自动触发timeout()
    connect(myTimer, &QTimer::timeout, this, &Widget::dealTimeout);//connect(sender, signal, receiver, slot);;
}
void Widget::pushButtonChoose_clicked(){
    qDebug()<<"全选";
    int rowCount=tableWidget->rowCount();
    qDebug()<<rowCount;
    for (int i=0;i<rowCount;i++)
    {
     tableWidget->item(i,0)->setCheckState(Qt::Checked);

    }
}
void Widget::pushButtonUnchoose_clicked(){
    qDebug()<<"反选";
    int rowCount=tableWidget->rowCount();
    qDebug()<<rowCount;
    for (int i=0;i<rowCount;i++)
    {
     tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
    }
}

void Widget::pushButtone_send(){
    qDebug()<<"发送";
    int rowCount=tableWidget->rowCount();
    qDebug()<<rowCount;

    for (int i=0;i<10;i++)
    {   if (tableWidget->item(i,0)->checkState()==Qt::Checked) {
            QString str=tableWidget->item(i,1)->text();
            qDebug()<<str;
        }
    }
}
void Widget::pushButtonstart_clicked(){
    qDebug()<<"开始";

    if (myTimer->isActive()==false) {
         myTimer->start(500);
    }
}
void Widget::pushButtonend_clicked(){
   qDebug()<<"结束";
   myTimer->stop();
}

void Widget::dealTimeout(){
    qDebug()<<"product data ";
    //数据不断的产生
    if (!flag) {
        num=num+1;
        qDebug()<<"return ";
        return;
    }
    int RowCont;
    RowCont=tableWidget->rowCount();
    if (RowCont>=100) {
        tableWidget->removeRow(0);
        RowCont--;
    }

    tableWidget->insertRow(RowCont);//增加一行
    QTableWidgetItem *check = new QTableWidgetItem();
    check->setCheckState(Qt::Unchecked);
    tableWidget->setItem(RowCont,0,check);
    tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::number(num, 10)));
    tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::number(num, 10)));
    tableWidget->setItem(RowCont,3,new QTableWidgetItem(QString::number(num, 10)));
    num=num+1;
    tableWidget->scrollToBottom();

}
void Widget::onScrollBarValueChanged(int value){
    qDebug()<<"滑动条移动";
    if(value == verticalScrollBar->maximum()){
        flag=true;
        qDebug()<<value;
    }else{
         flag=false;
    }
}

Widget::~Widget()
{
    delete ui;
}
