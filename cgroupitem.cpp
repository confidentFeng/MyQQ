#include "cgroupitem.h"

//设置组的标题，以及布局
CgroupItem::CgroupItem(const QString &title, QWidget *parent) : QWidget(parent),verticalLayout(new QVBoxLayout)
{
    verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    QString strTitle = "  " + title;//留空行，用来显示图片
    groupNameLabel = new QLabel(strTitle);//设置组的名字,比如我的好友、黑名单

    groupNameLabel->setStyleSheet("image: url(:/mainDialog/images/arrow_r_g.png);image-position:left center");//设置向右的箭头

    //设置样式表
    verticalLayout->addWidget(groupNameLabel);
    setLayout(verticalLayout);

    verticalLayout->setContentsMargins(0,0,0,0);
    verticalLayout->setSpacing(2);//设置好友之间间距
}

//添加列表成员
void CgroupItem::addItem(QWidget *item)
{
    m_itemList.append(item);  //这里就是组成员了，每来一个，就向组里加一个好友，item值得是一个personinfo类
    verticalLayout->addWidget(item);  //并把他加到这一组的名下
    item->setVisible(false); //设置控件不显示
}

//设置用户列表的“箭头”
void CgroupItem::mousePressEvent(QMouseEvent *event)
{
    if(m_itemList[0]->isVisible())//当前不可见，设置向右的箭头
    {
        groupNameLabel->setStyleSheet("image: url(:/mainDialog/images/arrow_r_g.png);image-position:left center");//设置向右的箭头
    }
    else//当前可见，设置向下的箭头
    {
        groupNameLabel->setStyleSheet("image: url(:/mainDialog/images/arrow_d.png);image-position:left center");//设置向下的箭头
    }

    if (event->button() == Qt::LeftButton)//每次鼠标点击，来显示隐藏或者显示好友
    {
        for (int i=0; i<m_itemList.size(); ++i)
        {
            m_itemList[i]->setVisible(!m_itemList[i]->isVisible());
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        //设置菜单 添加好友 删除好友，移动分组 改名等
    }
    QWidget::mousePressEvent(event);
}
