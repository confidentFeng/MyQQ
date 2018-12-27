/************************************************************
Copyright (C), 2018-2081, feng
FileName:menubutton.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: 对话的主窗口
Function List:
    void SlotReadMessage();   // 处理接收服务器方发送的消息
    void SlotSendMsgBtn();    // 点击发送按钮后，后发送消息
History: 无
***********************************************************/
#ifndef CTALKWITHDIALOG_H
#define CTALKWITHDIALOG_H
//#include "server.h"
#include <QDialog>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>

enum MsgType {Msg , UserEnter , UserLeft, NULLMes };//定义消息类型

struct MsgInfo//定义一个消息结构体，后期看有没有必要转化为类
{
    QString From;
    QString To;
    MsgType msgType;
    QString msgContent;
};

namespace Ui {
class CTalkWithDialog;
}

class CTalkWithDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CTalkWithDialog(QWidget *parent = nullptr);
    ~CTalkWithDialog();

private:
    Ui::CTalkWithDialog *ui;
    QPoint mouseDragPosition;//鼠标移动位置保存
    QTcpSocket* m_TcpSocket;      // 客户端套接字
    QString qqIconPath;
    QString qqnecklNameLocal;
    QString qqNumToLocal;//到哪里去
    QString qqNumFromLocal;//从哪里发来
    QString currentTime;
    QString sendLineText;//真实的有用消息
    QString structMsg;//构造消息
    QColor color;

public:
    QAction *b1,*b2,*b3,*b4,*b; //背景图片切换
    void mouseMoveEvent(QMouseEvent *); //鼠标移动事件
    void mousePressEvent(QMouseEvent *); //鼠标按压事件

    void sendMsg(MsgType type ,QString sendText = "");//发送的统一函数

    bool saveFile(const QString& filename);//保存文件记录

public slots:
    void SlotShowTalkWithDialog(QString qqNumFrom, QString necklName, QString qqNumTo, QString qqIcon, QTcpSocket *mainSocket);
    void SlotReveiveMainDialogMessage(QString structMessage , QString realMessage);//显示从主窗口传来的信息
    void SlotReadMessageTalk();   // 处理接收服务器方发送的消息
    void SlotSendMsgBtn();    // 点击发送按钮后，后发送消息

private slots:
    void on_minButton_clicked(); //最小化
    void on_maxButton_clicked(); //最大化
    void on_closeButton_clicked(); //关闭
    void on_exitButton_clicked(); //退出
    void on_saveToolButton_clicked(); //保存聊天消息
    void on_clearToolButton_clicked(); //清楚聊天消息
    void on_fontComboBox_currentFontChanged(const QFont &f); //选择字体
    void on_sizeComboBox_currentIndexChanged(const QString &arg1); //选择字号
    void on_boldToolButton_clicked(bool checked); //字体加粗
    void on_italicToolButton_clicked(bool checked); //斜体
    void on_underlineToolButton_clicked(bool checked); //下划线
    void on_colorToolButton_clicked(); //选择文字
    void on_menuButton_clicked();
    //设置聊天窗口的背景图，通过设置样式表的方式
    void bg();
    void bg1();
    void bg2();
    void bg3();
    void bg4();

};

#endif // CTALKWITHDIALOG_H
