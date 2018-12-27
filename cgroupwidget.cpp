#include "cgroupwidget.h"

#include <QLabel>

//自定义“组窗口部件”类，来显示多个好友分组项(cgroupitem)的，放在部件tab_1里面 (tab_1为QTabWidget，可以放置多个Widget，这里是放置cgroupitem)
CgroupWidget::CgroupWidget(QWidget *parent) : QWidget(parent), m_verticalLayout(new QVBoxLayout)
{
    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    QWidget *m_contentsWidget = new QWidget; //“组窗口部件”选择QWidget
    m_verticalLayout->setContentsMargins(0,0,0,0); //设置左侧、顶部、右侧和底部边距，以便在布局周围使用
    m_verticalLayout->setSpacing(0); //布局内的部件间隔设置为0
    m_contentsWidget->setLayout(m_verticalLayout); //“组窗口部件”设置为垂直布局
    m_contentsWidget->setStyleSheet("QWidget{border: 0;}"); //边框设置为0像素，即不显示边框

    QScrollArea *m_friendsScrollArea = new QScrollArea(this);//设置滚动条的一些操作，先不管他
    m_friendsScrollArea->setWidgetResizable(true);
    m_friendsScrollArea->setAlignment(Qt::AlignLeft);
    m_friendsScrollArea->setWidget(m_contentsWidget); //在QScrollArea滚动窗口中添加“窗口部件 m_contentsWidget”
    mainLayout->addWidget(m_friendsScrollArea);
    setLayout(mainLayout);
}

//用来添加一个组，item指的是CgroupItem定义的一个控件，也就是一个组
void CgroupWidget::addItem(QWidget *item)
{
    // Remove last spacer item if present.
    int count = m_verticalLayout->count();
    if (count > 1)
    {
        m_verticalLayout->removeItem(m_verticalLayout->itemAt(count - 1));
    }

    // Add item and make sure it stretches the remaining space.
    m_verticalLayout->addWidget(item);
    m_verticalLayout->setSpacing(10);//设置组与组之间间距
    m_verticalLayout->addStretch();
}
