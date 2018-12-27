/************************************************************
Copyright (C), 2018-2081, feng
FileName:cpeople.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: 显示每一个好友的信息，可以在上面增加各种好友信息 我这里有头像 昵称 以及在线状态、后期可以加上签名
Function List:

History: 无
***********************************************************/
#ifndef CPEOPLE_H
#define CPEOPLE_H
#include <QPushButton>
#include <QLabel>

class CPeople : public QPushButton
{
public:
    CPeople(QString qqNum, QString headPath, QString neckName, bool onlineState);

public:
    QString qqumlocal;
    QString headPathlocal;
    QString nickNamelocal;
    bool onlineStatelocal;

    QLabel *onlieStateLabel;
    QLabel *headIconLabel;
    QLabel *nickNameLabel;

    void setonlineState(bool onlineState);//设置在线状态
};

#endif // CPEOPLE_H
