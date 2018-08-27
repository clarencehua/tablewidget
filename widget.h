#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include <QTableWidget>
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
    void pushButtonUnchoose_clicked();
    void pushButtone_send();
private:
    QPushButton *buttonChoose;
    QPushButton *buttonUnChoose;
    QPushButton *buttonSend;
    QTableWidget *tableWidget;
    Ui::Widget *ui;
};

#endif // WIDGET_H
