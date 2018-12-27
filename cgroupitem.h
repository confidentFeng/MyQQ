/************************************************************
Copyright (C), 2018-2081, feng
FileName:cgroupitem.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: 被引用的类
用来建立一个组的成员列表，比如 我的好友 、陌生人 这一些列表
Function List:
     explicit CgroupItem(const QString &title,QWidget *parent = 0);//设置组的标题，以及布局
     void addItem(QWidget *item);//添加列表成员
     void mousePressEvent(QMouseEvent *event) ;//设置显示列表成员还是不显示
History: 无
***********************************************************/
#ifndef CGROUPITEM_H
#define CGROUPITEM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>

//用来建立一个组的成员列表，比如 我的好友、陌生人 这一些列表
class CgroupItem : public QWidget
{
    Q_OBJECT
public:
     explicit CgroupItem(const QString &title,QWidget *parent = nullptr); //设置组的标题，以及布局
     void addItem(QWidget *item); //添加列表成员
     void mousePressEvent(QMouseEvent *event) ; //设置显示列表成员还是不显示
     QLabel *groupNameLabel;
     QList<QWidget *> m_itemList; //用来存放好友的链表
signals:

public slots:

private:
    QVBoxLayout *verticalLayout; //垂直布局
};

#endif // CGROUPITEM_H
