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

    tableWidget =new QTableWidget(this);

    tableWidget->setColumnCount(11);
    tableWidget->setRowCount(11);
    /* 设置 tableWidget */
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Id" << "Name" << "Unit" << "Value" << "Min");
    tableWidget->verticalHeader()->setVisible(false); // 隐藏水平header
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);   // 单个选中
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个


    tableWidget->setItem(0,1,new QTableWidgetItem("Jan"));
    tableWidget->setItem(1,1,new QTableWidgetItem("Feb"));


    QDateTimeEdit *dateTimeEdit= new QDateTimeEdit();  //创建一个QDateTimeEdit
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());//设置为当前时间
    dateTimeEdit->setDisplayFormat("dd/M/yyyy");//设置显示格式
    dateTimeEdit->setCalendarPopup(true);//设置可以打开日历
    tableWidget->setCellWidget (1,2,dateTimeEdit);//加到第二行第三列中

    for (int var = 0; var < 10; ++var) {
        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        tableWidget->setItem(var,0,check);
    }


    buttonChoose=new QPushButton(this);
    buttonUnChoose=new QPushButton(this);
    buttonSend=new QPushButton(this);
    buttonChoose->setText("全选");
    buttonUnChoose->setText("反选");
    buttonSend->setText("发送");
    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addWidget(buttonChoose);
    hLayout->addWidget(buttonUnChoose);
    hLayout->addWidget(buttonSend);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *pLayout = new QGridLayout();
    pLayout->addWidget(tableWidget);
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(pLayout);
    setLayout(mainLayout);
    connect(buttonChoose,SIGNAL(clicked()),this, SLOT(pushButtonChoose_clicked()));
    connect(buttonUnChoose,SIGNAL(clicked()),this, SLOT(pushButtonUnchoose_clicked()));
    connect(buttonSend,SIGNAL(clicked()),this, SLOT(pushButtone_send()));
}
void Widget::pushButtonChoose_clicked(){
    qDebug()<<"全选";
    int rowCount=tableWidget->rowCount();
    qDebug()<<rowCount;
    for (int i=0;i<10;i++)
    {
     tableWidget->item(i,0)->setCheckState(Qt::Checked);

    }
}
void Widget::pushButtonUnchoose_clicked(){
    qDebug()<<"反选";
    int rowCount=tableWidget->rowCount();
    qDebug()<<rowCount;
    for (int i=0;i<10;i++)
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

Widget::~Widget()
{
    delete ui;
}
