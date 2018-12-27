/************************************************************
Copyright (C), 2018-2081, feng
FileName:qqlogin.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: QQ登陆的主界面
Function List:
    void on_LoginPushButton_clicked();//登录按钮处理
    void on_registerPushButton_clicked();//注册按钮处理函数
    void LoadStyle(QString fileName);//加载样式表
    bool connectiondatabes();  //连接mysql数据库
    bool queryDB(const QString &sql);//mysql数据库操作的集成函数
    void mouseMoveEvent(QMouseEvent *);//鼠标移动事件
    void mousePressEvent(QMouseEvent *);//鼠标按压事件
    void OpenSqlServerDatabase();//SQL server服务器连接
History: 无
***********************************************************/
#ifndef QQLOGIN_H
#define QQLOGIN_H

#include <QDialog>
#include <QMouseEvent>
#include <QFile>
#include <QMenu>
#include <QMovie>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QDateTime>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include "rigistertest.h"
#include "cregister.h"

namespace Ui {
class qqLogin;
}

enum enum_MesType{_UserEnter=1, UserRegister=3, LookForPassWd, UpDateFriendList=5};

class qqLogin : public QDialog
{
    Q_OBJECT

public:
    explicit qqLogin(QDialog *parent = nullptr);
    ~qqLogin();

private slots:
    void SlotBlueSheetStyle(); //装载"蓝色动图"样式
    void SlotRedSheetStyle(); //装载"红色动图"样式
    void SlotPurpleSheetStyle(); //装载"粉色动图"样式
    void SlotReadMessage(); //处理接收服务器方发送的消息
    //----
    void SendMessageLogin(enum_MesType type, QStringList strlistMes); //发送消息给服务器
    //----
    void on_miniPushButton_clicked(); //最小化登陆窗口
    void on_closePushButton_clicked(); //关闭窗口
    //----
    void on_LoginPushButton_clicked(); //登录按钮处理
    void on_registerPushButton_clicked(); //注册按钮处理
    void on_lookForPasswordPushButton_clicked(); //找回密码

private:
    Ui::qqLogin *ui;

    QTcpSocket *m_TcpSocket;
    QPoint mouseDragPosition;//鼠标移动位置保存，用于拖动"登陆窗口"
    QMenu *sheetStyleMenu;//设置皮肤菜单
    QString userInfoArr[4]; //自身昵称、自身QQ账号、头像文件路径、个性签名
    bool isTrue = false;//验证用户QQ账号密码，为true，则QQ账号密码正确，登陆成功
    //----
    void LoadStyle(QString fileName);//加载样式表
    void InitialUi();//初始化登陆窗口UI
    void CreatTcpConnenct();//创建TCP连接
    //----
    void mousePressEvent(QMouseEvent *);//鼠标按压事件，为了可以拖动"登陆窗口"
    void mouseMoveEvent(QMouseEvent *);//鼠标移动事件处理，为了可以拖动"登陆窗口"

signals:
    void SignalTransQQAccount(QString qqNum);//传递QQ账号给"注册窗口"的信号
    void SignalTransQQPassWd(QString qqPassWd);//传递QQQQ密码给"查找密码窗口"
    void SignalShowMainDialog(QTcpSocket *TcpSocket,QStringList strlistUser);//显示主窗口的信号,并把socket和用户信息发给主窗口
};

#endif // QQLOGIN_H
