#ifndef RIGISTER_H
#define RIGISTER_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
namespace Ui {
class rigister;
}

class rigister : public QDialog
{
    Q_OBJECT

public:
    explicit rigister(QWidget *parent = 0);
    ~rigister();

private slots:
    void on_pushButton_clicked();//测试按钮

private:
    Ui::rigister *ui;
};

#endif // RIGISTER_H
