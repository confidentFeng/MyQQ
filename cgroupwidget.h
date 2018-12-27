/************************************************************
Copyright (C), 2018-2081, feng
FileName:cgroupwidget.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: 被引用的类
//自定义“组窗口部件”类，来显示每个好友分组的，放在部件tab_1里面 (tab_1为QTabWidget，可以放置多个Widget，这里是放置CgroupWidget)
Function List:
     void addItem(QWidget *item);//用来添加一个组，item指的是CgroupItem定义的一个控件，也就是一个分组
History: 无
***********************************************************/
#ifndef CGROUPWIDGET_H
#define CGROUPWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

//自定义“组窗口部件”类，来显示每个好友分组的，放在部件tab_1里面 (tab_1为QTabWidget，可以放置多个Widget，这里是放置CgroupWidget)
class CgroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CgroupWidget(QWidget *parent = nullptr);
    void addItem(QWidget *item);//用来添加一个组，item指的是CgroupItem定义的一个控件，也就是一个组

private:
    QVBoxLayout *m_verticalLayout;

signals:

public slots:
};


#endif // CGROUPWIDGET_H
