/************************************************************
Copyright (C), 2018-2081, feng
FileName:cregister.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: QQ注册的主窗口
Function List:
     void on_submitPushButton_clicked();//提交按钮的处理，
     void on_cancelPushButton_clicked();//取消按钮的处理
    void on_qqImagePushButton_clicked();//图片处理按钮，
    void SlotGetqqImageUrl(QString);//为了得到图片的url地址，专门写了个槽函数，接收SignalImageUrl(QString)
History: 无
***********************************************************/

#ifndef CREGISTER_H
#define CREGISTER_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "cimagechoose.h"
#include <QMessageBox>
#include <QTime>
#include <QTcpSocket>

namespace Ui {
class Cregister;
}

class Cregister : public QDialog
{
    Q_OBJECT

public:
    explicit Cregister(QWidget *parent = nullptr);
    ~Cregister();

private slots:
    void on_submitPushButton_clicked();//提交按钮的处理，

    void on_cancelPushButton_clicked();//取消按钮的处理

    void on_qqImagePushButton_clicked();//图片处理按钮，
    void SlotGetqqImageUrl(QString);//为了得到图片的url地址，专门写了个槽函数

    void SlotRecvQQAccountRegister(QString tempQQNumber);   // 处理接收服务器方发送的消息
    void SlotSendMsgBtn();    // 点击发送按钮后，后发送消息
    void displayErr(QAbstractSocket::SocketError sockErr);//错误处理函数
public:
    void setTcpSocker( QTcpSocket *TcpSocket);//设置套接字
    QTcpSocket *registerTcpSocket;
private:
    Ui::Cregister *ui;
    QString imageUrl;//保存图片的地址，并存到数据库中

    QString tempQQNumber;
};

#endif // CREGISTER_H
