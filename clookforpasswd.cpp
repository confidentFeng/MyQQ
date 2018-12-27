#include "clookforpasswd.h"
#include "ui_clookforpasswd.h"

#define LookForPassWd 4

CLookForPassWd::CLookForPassWd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLookForPassWd)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    lookForPassWdTcpSocket = new QTcpSocket(this);//一定要给他分配内存啊，一会不分配试一下
}

void CLookForPassWd::on_lookForBtn_clicked()//查询按钮
{
    SlotSendMsgBtn();

    while(!lookForPassWdTcpSocket->waitForReadyRead(-1));//为啥会接收不到数据呢？因为数据会传给登陆的接收函数，所以我又很麻烦的用了槽函数

    if(QQPassWd == "NoQQAccount")//没有该账户
    {
        ui->resultLabel->setText("不存在该账户！请重新输入。");
    }
    else//存在该账户
    {
        ui->resultLabel->setText(QQPassWd);
    }
}

void CLookForPassWd::on_pushButton_clicked()//OK按钮
{
    this->accept();
}

void CLookForPassWd::SlotReadMessageLookFor(QString tempQQPassWd)
{
    QQPassWd = tempQQPassWd;
}

void CLookForPassWd::SlotSendMsgBtn()
{
    QByteArray dataSend;
    QDataStream out(&dataSend,QIODevice::WriteOnly);
    lookForQQNumber = ui->lineEdit->text();
    out << LookForPassWd << lookForQQNumber;//构建了报头 类型 注册信息
    qDebug() << dataSend;
    lookForPassWdTcpSocket->write(dataSend);//发送最终处理过的数据 先不用转化
}


void CLookForPassWd::on_pushButton_2_clicked()//取消按钮
{
    this->accept();//还需后续处理
}

CLookForPassWd::~CLookForPassWd()
{
    delete ui;
}

void CLookForPassWd::setTcpSocker(QTcpSocket *socket)//赋值给找密码的套接字
{
    lookForPassWdTcpSocket = socket;
}

