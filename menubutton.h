/************************************************************
Copyright (C), 2018-2081, feng
FileName:menubutton.h
Author: feng
Version : V1.0
Date:2018-12-10
Description: 继承自按钮的菜单
Function List:

History: 无
***********************************************************/

#ifndef MENUBUTTON
#define MENUBUTTON
#include <QPushButton>

class QMenu;
class MenuButton : public QPushButton //继承QPushButton类
{
    Q_OBJECT

public:
    explicit MenuButton(QWidget *parent = nullptr);
    QMenu *getmenu();

private slots:
    void PushMenu();

private:
    QMenu *menu;
};
#endif // MENUBUTTON

