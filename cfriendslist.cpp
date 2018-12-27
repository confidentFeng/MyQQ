#include "cfriendslist.h"
#include"personinfo.h"
#include <QLabel>
CFriendsList::CFriendsList()
{
      QStringList strList;
        strList<< "Item1"<<"Item2"<< "Item3"<<"Item4";

        this->addItems(strList);

//        QListWidgetItem *pItem = new QListWidgetItem(this);
//        pItem->setText("Item5");
//        this->addItem(pItem);
}

void CFriendsList::slotAddGroup()
{
    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/mainDialog/images/arrow_r_g.png"),"未命名");    //创建一个Item
    newItem->setSizeHint(QSize(this->width(),25));//设置宽度、高度
    this->addItem(newItem);         //加到QListWidget中
    groupMap.insert(newItem,newItem);//加到容器groupMap里，key和value都为组
    isHideMap.insert(newItem,true);  //设置该组隐藏状态
    groupNameEdit->raise();
    groupNameEdit->setText(tr("未命名")); //设置默认内容
    groupNameEdit->selectAll();        //设置全选
    groupNameEdit->setGeometry(this->visualItemRect(newItem).left()+15,this->visualItemRect(newItem).top()+1,this->visualItemRect(newItem).width(),this->visualItemRect(newItem).height()-2);//出现的位置
    groupNameEdit->show();              //显示
    groupNameEdit->setFocus();          //获取焦点
    currentItem = newItem;     // 因为要给group命名，所以当前的currentItem设为该group
}

void CFriendsList::slotAddFriend()
{
    personinfo *friends =new personinfo(":/mainDialog/images/1.jpg","嚣张的小烧包",1);   //创建一个自己定义的信息类
//    buddy->headPath=":/head";                          //设置头像路径
//    buddy->name->setText("逍遥圣帝");                  //设置用户名
//    buddy->sign->setText("用通俗的语言，讲深刻的技术。");   //设置个性签名
    QList<QListWidgetItem*> tem = groupMap.keys(currentItem);//当前组对应的项（包括组本身和好友）复制给tem
    //关键代码
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    this->insertItem(row(currentItem)+tem.count(),newItem); //将该newItem插入到后面
    this->setItemWidget(newItem, friends); //将buddy赋给该newItem
    groupMap.insert(newItem,currentItem);   //加进容器，key为好友，value为组
    if(isHideMap.value(currentItem))          //如果该组是隐藏，则加进去的好友设置为隐藏
        newItem->setHidden(true);
    else                                      //否则，该好友设置为显示
        newItem->setHidden(false);
}


