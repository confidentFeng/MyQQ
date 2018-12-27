#include "cregister.h"
#include "ui_cregister.h"
#include "cfriendslist.h"
#include <QHostAddress>

#define UserRegister 3
Cregister::Cregister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cregister)
{
    ui->setupUi(this);
    setWindowTitle(tr("注册用户"));
    setWindowFlags(Qt::FramelessWindowHint);

    registerTcpSocket = new QTcpSocket(this);//这里需要分配内存

    connect(registerTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(displayErr(QAbstractSocket::SocketError)));
}

void Cregister::on_submitPushButton_clicked()//这里可以设置一些数据库输入限制，以及账号查重
{
    //发送注册信息
    SlotSendMsgBtn();
    //等待服务器返回申请的QQ号码 进程会阻塞
    while(!registerTcpSocket->waitForReadyRead(5000));//注册窗口的Socket接收不到数据，因为数据会传给登陆窗口的接收函数，所以只能通过信号槽把QQ号码从登陆窗口传递过来

    if(QString(tempQQNumber).length()==10)//收到QQ账号为10位数，而不是空字符串，则说明注册成功
    {
        QMessageBox::information(this,"提示栏",QString("恭喜您注册成功,QQ号为：%1").arg(tempQQNumber));
    }
    else//注册失败
    {
        QMessageBox::information(this,"提示栏","注册失败!");
    }
    this->accept();//返回登陆界面
}

void Cregister::SlotRecvQQAccountRegister(QString QQNumber)
{
    tempQQNumber = QQNumber;
}

void Cregister::on_cancelPushButton_clicked()//取消按钮处理
{
    this->accept();//还需后续处理
}

//得到图片的url地址
void Cregister::SlotGetqqImageUrl(QString imageUrl)
{
    this->imageUrl = imageUrl;//传给本地的图片地址变量，然后在数据库提交的按钮中使用
    //通过样式表给按钮添加图片
    ui->qqImagePushButton->setStyleSheet( QString("border-image: url(%1);").arg(imageUrl));
}

void Cregister::SlotSendMsgBtn()
{
    //由于QQ账号是申请的，所以没有添加"Q账号"一栏，由服务器自动生成再返回给客户端
    QByteArray dataSend;
    QDataStream out(&dataSend,QIODevice::WriteOnly);

    out << UserRegister
        << ui->neckNameLineEdit->text()
        << ui->passWordLineEdit->text()
        << imageUrl
        << ui->idCardLineEdit->text()
        << ui->nameLineEdit->text()
        << ui->sexComboBox->currentText()
        << ui->signatureLineEdit->text()
        << ui->ageLineEdit->text().toInt(); //构建了数据帧: 类型 注册用户信息

    qDebug() <<"注册发送消息:"<< dataSend;
    registerTcpSocket->write(dataSend);//发送最终处理过的数据 先不用转化
}

void Cregister::setTcpSocker(QTcpSocket *TcpSocket)
{
    registerTcpSocket = TcpSocket;
}

void Cregister::on_qqImagePushButton_clicked()
{
    CImageChoose imageChoose;
    //把点击图片发出的图片url的信号给提交按钮发过去，获得图片的url地址
    connect(&imageChoose,SIGNAL(SignalImageUrl(QString)),this,SLOT(SlotGetqqImageUrl(QString)));

    imageChoose.exec();
}

void Cregister::displayErr(QAbstractSocket::SocketError sockErr)
{
    switch(sockErr)
    {
        case QAbstractSocket::RemoteHostClosedError : break;
        default : qDebug() << "this ?"<<registerTcpSocket->errorString();
    }
}

Cregister::~Cregister()
{
    delete ui;
}
