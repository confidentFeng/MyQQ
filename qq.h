/************************************************************
Copyright (C), 2018-2081, TianCheng Tech. Co., Ltd.
FileName:qq.h
Author: Mrs Wang
Version : V1.0
Date:2018-5-1
Description: QQ主界面
Function List:
1. void SlotAcceptLogin(QString qqNum) //接收登陆窗口发来的信号，显示主界面
2. void SlotSendTalkWithDialogSignal()// 显示对话框
History: 无
***********************************************************/

#ifndef QQ_H
#define QQ_H

#include <QDialog>
#include <QMouseEvent>
#include <QTcpSocket>
#include "ctalkwithdialog.h"
#include "personinfo.h"
#include "cgroupitem.h"
#include "cgroupwidget.h"
#include "personinfo.h"
#include "IMFriendButton.h"
#include "cpeople.h"

namespace Ui {
class QQ;
}

class QQ : public QDialog
{
    Q_OBJECT

public:
    explicit QQ(QWidget *parent = nullptr);
    ~QQ();
    QTcpSocket *m_mainSocket;

private:
    Ui::QQ *ui;
    QPoint mouseDragPosition; //鼠标移动位置保存， 用来进行拖动窗口
    CTalkWithDialog *m_talkWithDialog; //对话的界面
    //----
    QString qqNumId; //保存登陆窗口传过来的QQ号
    QString qqIcon1;
    QString necklName1;
    QString strSignature;
    QList<QWidget *> m_groupList; //用来存放组的item 比如这里的我的好友 陌生人 黑名单
    QList<CPeople *> m_peopleList; //用来存放每一个人，来更新上下线状态
    //----
    void mouseMoveEvent(QMouseEvent *); //鼠标移动事件，用来进行拖动窗口
    void mousePressEvent(QMouseEvent *); //鼠标按压事件，用来进行拖动窗口
    void UpdateFriendsList(); //更新好友列表

signals:
    void SignalShowTalkWithDialog(QString qqNumFrom,QString qqNumTo,QString m_qqIcon,QString m_nicklName,QTcpSocket *m_mainSocket);

public slots:
    void SlotAcceptLogin(QTcpSocket * loginSocket, QStringList strlistUser); //接收登陆窗口发来的套接字和用户信息
    void SlotSendTalkWithDialogSignal();
    void SlotMainDialogReadMessage(); //接收消息
    void SendMessage(MsgType type, QStringList strlistMes); //发送消息

private slots:
    void on_miniPushButton_clicked();//最小化
    void on_closePushButton_clicked();//关闭窗口
};

#endif
