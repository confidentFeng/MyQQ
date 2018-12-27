#include "qqlogin.h"
#include "ui_qqlogin.h"
#include "clookforpasswd.h"
#include <QIODevice>
#include <QRegExpValidator>

qqLogin::qqLogin(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::qqLogin)
{
    ui->setupUi(this);

    //初始化UI
    InitialUi();
    //建立TCP连接
    CreatTcpConnenct();
}

qqLogin::~qqLogin()
{
    delete ui;
}

//创建TCP连接
void qqLogin::CreatTcpConnenct()
{
    //初始化通信套接字
    m_TcpSocket = new QTcpSocket(this);

    // 如果想要实现局域网通信, 只需将第一个IP地址设置为“服务器”所在主机的IP地址即可
    m_TcpSocket->connectToHost(QHostAddress::LocalHost, 7777);//到这里就已经连接上服务器了

    connect(m_TcpSocket,SIGNAL(readyRead()),this,SLOT(SlotReadMessage()));   // 告诉socket, 要用SlotReadMessage()去处理接收的消息.
}

//处理接收服务器方发送的消息
void qqLogin::SlotReadMessage()
{
    QDataStream in(m_TcpSocket);

    int msgType;//类型
    in >> msgType;
    qDebug()<<"登陆窗口接收类型:"<<msgType;

    switch (msgType)
    {
        case _UserEnter://UserEnter
        {
            QString strLoginRecvMes;

            in >> strLoginRecvMes >>userInfoArr[0] >>userInfoArr[1] >>userInfoArr[2] >>userInfoArr[3];
            if(strLoginRecvMes=="Login Success!")
                isTrue = true;
        }
        break;

        case UserRegister://UserRegister
        {
            QString qqNumReceive;
            in >> qqNumReceive;
            emit SignalTransQQAccount(qqNumReceive);//发射显示注册窗口的界面,把QQ号发给注册窗口
        }
        break;

        case LookForPassWd://LookForPassWd
        {
            QString strLookForPassWd;
            in >> strLookForPassWd;
            emit SignalTransQQPassWd(strLookForPassWd);//发射显示主窗口的界面,把QQ号发给主窗口
        }
        break;

        case UpDateFriendList://UpDateFriendList
        {
            QString tempUpdateCommand;
            in >> tempUpdateCommand;
            qDebug()<<"tempUpdateCommand"<<tempUpdateCommand;
        }
        break;

        default:
        break;
    }
}

//发送消息给服务器
void qqLogin::SendMessageLogin(enum_MesType type, QStringList strlistMes)
{
    QByteArray dataSend;
    QDataStream out(&dataSend,QIODevice::WriteOnly);

    out <<type;
    for(int i=0;i<strlistMes.size();i++)
    {
        out <<strlistMes.at(i);
    }

    m_TcpSocket->write(dataSend);//发送最终处理过的数据 先不用转化
}

//登录按钮响应函数
void qqLogin::on_LoginPushButton_clicked()
{
    if(ui->userNameLineEdit->text().isEmpty())//如果用户名为空，弹出提示框
    {
        QMessageBox::information(this,"information","请输入用户");
        ui->userNameLineEdit->setFocus();
    }
    else
    {
        if(ui->passwdLineEdit->text().isEmpty())//如果密码为空，弹出提示框
        {
            QMessageBox::information(this,"information","请输入密码");
            ui->passwdLineEdit->setFocus();
        }
        else
        {
            qDebug()<<"套接字Login"<<m_TcpSocket->socketDescriptor();
            //等待按下登陆按钮，发送登陆请求
            QString strUserQQAccount; //用户QQ账号
            QString strUserQQPasswd; //用户QQ密码
            strUserQQAccount = ui->userNameLineEdit->text();
            strUserQQPasswd = ui->passwdLineEdit->text();
            QStringList strlistMes;
            strlistMes.append(strUserQQAccount);
            strlistMes.append(strUserQQPasswd);
            SendMessageLogin(_UserEnter,strlistMes);
            //直到接收到数据，才往下执行
            while(!m_TcpSocket->waitForReadyRead(-1));

            if(isTrue)
            {
                /*********用于和主窗口的切换****************************/             
                disconnect(m_TcpSocket,SIGNAL(readyRead()),this,SLOT(SlotReadMessage()));//取消登陆窗口的接收服务器发来数据功能
                this->close();//关闭"登陆窗口"

                QStringList strlistUser;
                strlistUser.append(userInfoArr[0]); //自身昵称
                strlistUser.append(userInfoArr[1]); //自身QQ账号
                strlistUser.append(userInfoArr[2]); //头像文件路径
                strlistUser.append(userInfoArr[3]); //个性签名
                emit SignalShowMainDialog(m_TcpSocket,strlistUser);//发射显示主窗口的信号,并把socket和QQ账号发给主窗口
                this->close();//关闭"登陆窗口"
            }
            else
            {
                QMessageBox::information(this,"information","账号或密码错误");
                ui->userNameLineEdit->clear();
                ui->passwdLineEdit->clear();
                ui->userNameLineEdit->setFocus();
            }
        }
    }
}

//注册账号
void qqLogin::on_registerPushButton_clicked()
{
    Cregister registerDialog;//注册窗口的实例化对象
    registerDialog.setTcpSocker(m_TcpSocket);//把现登陆窗口的套接字传给注册窗口
    //注册窗口socket发送注册信息给服务器，但接收不到服务器返回的QQ号码，因为"注册窗口"socket跟"登陆窗口"传递来的，两者相同
    //发现只有"登陆窗口"socket才能接收到服务器返回消息，所以QQ号码是通过信号槽从登陆窗口传递给"注册窗口"的，注册窗口才能提示申请到的"QQ账号"
    connect(this,SIGNAL(SignalTransQQAccount(QString)),&registerDialog,SLOT(SlotRecvQQAccountRegister(QString)));
    this->hide();//当前登陆窗口隐藏

    if(registerDialog.exec() == Cregister::Accepted)
        this->show();//再显示登陆界面
}

//找回密码
void qqLogin::on_lookForPasswordPushButton_clicked()
{
    CLookForPassWd lookPassWdDialog;//找回密码窗口的实例化对象
    lookPassWdDialog.setTcpSocker(m_TcpSocket);//把现窗口的套接字传给找回密码窗口
    connect(this,SIGNAL(SignalTransQQPassWd(QString)),&lookPassWdDialog,SLOT(SlotReadMessageLookFor(QString)));
    this->hide();//当前窗口隐藏
    if(lookPassWdDialog.exec() == Cregister::Accepted)
        this->show();//再显示登陆界面
}

//初始化登陆窗口UI
void qqLogin::InitialUi()
{
    //设置窗口无边框且在别的窗口上面
    setWindowFlags(Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint);

    //默认显示蓝色动图
    LoadStyle(":/qss/blue.qss");
    QMovie *movie = new QMovie(":/qqLogin/images/blue70-2.gif");
    movie->resized(ui->gifLabel->size());
    ui->gifLabel->setMovie(movie);
    movie->start();

    //创建一个菜单，并把菜单放置在setPushButton(“设置皮肤”)下面
    sheetStyleMenu = new QMenu;
    ui->setPushButton->setMenu(sheetStyleMenu);
    //为菜单添加动作，并命名
    QAction* blueAct = new QAction(sheetStyleMenu);
    QAction* redAct = new QAction(sheetStyleMenu);
    QAction* purpleAct = new QAction(sheetStyleMenu);
    blueAct->setText(tr("blue"));
    redAct->setText(tr("red"));
    purpleAct->setText(tr("purple"));
    sheetStyleMenu->addAction(blueAct);
    sheetStyleMenu->addAction(redAct);
    sheetStyleMenu->addAction(purpleAct);
    //按钮中不显示向下的箭头
    ui->setPushButton->setStyleSheet("QPushButton::menu-indicator{image:none}");
    //连接几个按钮菜单动作的槽
    connect(blueAct,SIGNAL(triggered(bool)),this,SLOT(SlotBlueSheetStyle()));
    connect(redAct,SIGNAL(triggered(bool)),this,SLOT(SlotRedSheetStyle()));
    connect(purpleAct,SIGNAL(triggered(bool)),this,SLOT(SlotPurpleSheetStyle()));

    //设置正则表达式
    QValidator *userNameValidator = new QRegExpValidator(QRegExp("[0-9]{10}")); //设置"用户账号输入栏"，只能输入数字0-9,不超过10位
    ui->userNameLineEdit->setValidator(userNameValidator);
    QValidator *passwordValidator = new QRegExpValidator(QRegExp("[0-9]{10}")); //设置"用户账号输入栏"，只能输入数字0-9,不超过10位
    ui->passwdLineEdit->setValidator(passwordValidator);
    //密码隐式显示
    ui->passwdLineEdit->setEchoMode(QLineEdit::Password);
}

//加载样式表函数
void qqLogin::LoadStyle(QString fileName)
{
    if(fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
        setStyleSheet(file.readAll());

    file.close();
}

//鼠标按压事件响应处理，为了可以拖动"登陆窗口"
void qqLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseDragPosition = event->globalPos()-frameGeometry().topLeft();
        event->accept();//要加上这一句话
    }
}
//鼠标移动事件处理，为了可以拖动"登陆窗口"
void qqLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-mouseDragPosition);//减去原先的误差
        event->accept();
    }
}

//登陆窗口最小化
void qqLogin::on_miniPushButton_clicked()
{
    this->showMinimized();
}
//关闭登陆窗口
void qqLogin::on_closePushButton_clicked()
{
    m_TcpSocket->disconnectFromHost();
    m_TcpSocket->close();//关闭套接字
    close();//关闭窗口
}

//装载"蓝色动图"样式
void qqLogin::SlotBlueSheetStyle()
{
    //显示动图
    LoadStyle(":/qss/blue.qss"); //默认装载blue样式表
    QMovie *movie = new QMovie(":/qqLogin/images/blue70-2.gif");
    ui->gifLabel->setMovie(movie);
    movie->start();
}
//装载"红色动图"样式
void qqLogin::SlotRedSheetStyle()
{
    //显示动图
    LoadStyle(":/qss/red.qss");
    QMovie *movie = new QMovie(":/qqLogin/images/red69-2.gif");
    ui->gifLabel->setMovie(movie);
    movie->start();
}
//装载"粉色动图"样式
void qqLogin::SlotPurpleSheetStyle()
{
    //显示动图
    LoadStyle(":/qss/purple.qss");
    QMovie *movie = new QMovie(":/qqLogin/images/purple0.4.gif");
    ui->gifLabel->setMovie(movie);
    movie->start();
}
