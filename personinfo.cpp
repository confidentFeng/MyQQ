#include "personinfo.h"
#include "ui_personinfo.h"

//把头像，昵称，和在线状态传过来，除此之外，后期也可以添加个性签名
personinfo::personinfo(QString headPath,QString neckName,bool onlineState,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::personinfo)
{
    ui->setupUi(this);

    ui->iconLabel->setStyleSheet(QString("border-image: url(%1)").arg(headPath));//设置头像
    ui->neckNameLabel->setText(neckName);//设置网名

    if(onlineState)//如果在线
    {
        //设置字体显示样式，显示绿色
        ui->onlineStateLabel->setStyleSheet("color: rgb(55, 255, 52)");//颜色显示绿色
        ui->onlineStateLabel->setText("[在线]");
    }
    else//不在线，显示灰色
    {
        ui->onlineStateLabel->setStyleSheet("color: rgb(195, 195, 195)");//颜色显示灰色
        ui->onlineStateLabel->setText("[离线]");
    }

}

personinfo::~personinfo()
{
    delete ui;
}
