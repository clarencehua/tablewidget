#ifndef WIDGET_H
#define WIDGET_H
#include <QTimer> //定时器头文件
#include <QWidget>
#include<QVector>
#include<QPushButton>
#include<QString>
#include <QTableWidget>
#include<QScrollBar>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void pushButtonChoose_clicked();
    void pushButtonstart_clicked();
    void pushButtonend_clicked();
    void pushButtonUnchoose_clicked();
    void pushButtone_send();
    void dealTimeout(); //定时器槽函数
    void onScrollBarValueChanged(int);
private:
    QPushButton *buttonChoose;
    QPushButton *buttonUnChoose;
    QPushButton *buttonSend;
    QPushButton *buttonStart;
    QPushButton *buttonEnd;
    QTableWidget *tableWidget;
    int num;
    QVector<QString> vector;
    QTimer *myTimer; //声明变量
    Ui::Widget *ui;
    QScrollBar *verticalScrollBar;
    bool flag;
};

#endif // WIDGET_H
