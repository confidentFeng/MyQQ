/************************************************************
Copyright (C), 2018-2081, feng
FileName:cimagechoose.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: 注册时用来选择用户头像
Function List:
     void on_pushButton_1_clicked();//响应点击每一个图片之后的处理函数
     void SignalImageUrl(QString);//发送图片的Url给注册窗口
History: 无
***********************************************************/
#ifndef CIMAGECHOOSE_H
#define CIMAGECHOOSE_H

#include <QDialog>

namespace Ui {
class CImageChoose;
}

class CImageChoose : public QDialog
{
    Q_OBJECT

public:
    explicit CImageChoose(QWidget *parent = nullptr);
    ~CImageChoose();

public:
    Ui::CImageChoose *ui;

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

signals:
    void SignalImageUrl(QString);
};

#endif // CIMAGECHOOSE_H
