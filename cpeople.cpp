#include "cpeople.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

CPeople::CPeople(QString qqNum,QString headPath,QString neckName,bool onlineState):qqumlocal(qqNum),headPathlocal(headPath),nickNamelocal(neckName),onlineStatelocal(onlineState)
{
    /*QLabel **/headIconLabel = new QLabel;
    headIconLabel->setFixedSize(35,35);
    headIconLabel->setStyleSheet(QString("border-image: url(%1)").arg(headPath));//设置头像
    /*QLabel **/nickNameLabel = new QLabel;
    nickNameLabel->setText(neckName);//设置网名
    /*QLabel **/onlieStateLabel = new QLabel;
    if(onlineState)//如果在线
    {
        //设置字体显示样式，显示绿色
        onlieStateLabel->setStyleSheet("color: rgb(112, 237, 58)");//颜色显示绿色
        onlieStateLabel->setText("[在线]");
    }
    else//不在线，显示灰色
    {
        onlieStateLabel->setStyleSheet("color: rgb(173, 198, 180)");//颜色显示灰色
        onlieStateLabel->setText("[离线]");
    }

    QVBoxLayout *verticalLayout = new QVBoxLayout;//neckNameLabel onlieStateLabel垂直布局
    verticalLayout->addSpacing(1);
    verticalLayout->addWidget(nickNameLabel);
    verticalLayout->addWidget(onlieStateLabel);
    verticalLayout->addStretch();


    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);//headIconLabel verticalLayout水平布局
    horizontalLayout->addWidget(headIconLabel);
    horizontalLayout->addLayout(verticalLayout);

    horizontalLayout->setContentsMargins(4,0,0,0);
    setMinimumSize(100,45);//设置按钮的大小吧

    setStyleSheet("QPushButton{border: 0;}");

}

void CPeople::setonlineState(bool onlineState)
{
    if(onlineState)//如果在线
    {
        //设置字体显示样式，显示绿色
        onlieStateLabel->setStyleSheet("color: rgb(112, 237, 58)");//颜色显示绿色
        onlieStateLabel->setText("[在线]");
    }
    else//不在线，显示灰色
    {
        onlieStateLabel->setStyleSheet("color: rgb(173, 198, 180)");//颜色显示灰色
        onlieStateLabel->setText("[离线]");
    }
}
