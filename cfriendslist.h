#ifndef CFRIENDSLIST_H
#define CFRIENDSLIST_H

#include <QObject>
#include <QListWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QLineEdit>
class CFriendsList : public QListWidget //继承QListWidget，可以使用它本身自带的函数，更方便
{
    Q_OBJECT
public:
    CFriendsList();







    QMap<QListWidgetItem*,QListWidgetItem*> groupMap;   // 组容器 - key:项 value:组
    QMap<QListWidgetItem*,bool> isHideMap;//用来判断该组是否隐藏了
    QLineEdit *groupNameEdit;//组的名字，重命名的时候需要用到
    QListWidgetItem *currentItem;//当前的项

public slots:
    void slotAddGroup();   //添加组
    //void slotDelGroup();   //删除组
    void slotAddFriend();   //添加好友
    //void slotDelBuddy();   //删除好友
    //void slotRename();     //重命名组
    //void slotRenameEditFshed();//命名完成
};

#endif // CFRIENDSLIST_H
