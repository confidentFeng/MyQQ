#include "qq.h"
#include "ui_qq.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>

QQ::QQ(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QQ)
{
    ui->setupUi(this);
    setWindowTitle(tr("MyQQ"));
    setWindowFlags(Qt::FramelessWindowHint);

    //设置点击一个用户头像，弹出一个“聊天窗口”
    m_talkWithDialog = new CTalkWithDialog();
    connect(this,SIGNAL(SignalShowTalkWithDialog(QString,QString,QString,QString,QTcpSocket *)),m_talkWithDialog,SLOT(SlotShowTalkWithDialog(QString,QString,QString,QString,QTcpSocket *)));
}

//连接信号SignalShownMainDialog() ，用来显示主窗口并接受登陆窗口传递来的“与服务器连接socket”、“昵称”、“QQ账号”、“头像图片路径”
void QQ::SlotAcceptLogin(QTcpSocket * loginSocket,QStringList strlistUser)
{
    necklName1 = strlistUser[0];
    qqNumId = strlistUser[1]; //保存登陆窗口传过来的QQ账号
    qqIcon1 = strlistUser[2]; //保存登陆窗口传过来的头像图片路径
    strSignature = strlistUser[3];
    qDebug() <<"主窗口接收_注册窗口的" <<necklName1 <<qqNumId <<qqIcon1 <<strSignature;
    //设置头像和昵称
    ui->iconLabel->setStyleSheet(QString("border-image: url(%1);").arg(qqIcon1));
    ui->neckNameLabel->setText(necklName1);
    ui->mottoLineEdit->setText(strSignature); //设置个性签名

    m_mainSocket = loginSocket; //接受一个从登陆窗口传来的套接字
    connect(m_mainSocket,SIGNAL(readyRead()),this,SLOT(SlotMainDialogReadMessage())); //告诉mainSocket, SlotMainDialogReadMessage()去处理接收的消息.

    //建立自己的好友列表和更新别的好友列表 *********
    UpdateFriendsList();

    this->show();//显示主窗口
}

//接收消息
void QQ::SlotMainDialogReadMessage()
{
    QDataStream in(m_mainSocket);

    int msgType;//类型
    in >> msgType;
    qDebug()<<"主窗口接收消息类型:"<<msgType;
    switch (msgType)
    {
        case 5: //UpDateFriendList
        {
            //更新用户的好友在线状态，避免先登陆的用户的好友列表里：后登陆用户状态为“离线”
            QString strnicklName;
            in >> strnicklName;
            qDebug()<<"上线用户昵称："<<strnicklName;
            for(int i = 0 ; i<m_peopleList.size(); i++)
            {
                qDebug()<<m_peopleList.at(i)->nickNameLabel->text();
                if(m_peopleList.at(i)->nickNameLabel->text() == strnicklName)
                {
                    m_peopleList.at(i)->onlineStatelocal = true;
                    m_peopleList.at(i)->setonlineState(true);//设置在线
                    break;
                }
            }
        }
        break;

        default:
        break;
    }

}

//发送消息
void QQ::SendMessage(MsgType type, QStringList strlistMes)
{
    QByteArray dataSend;
    QDataStream out(&dataSend,QIODevice::WriteOnly);

    qDebug() <<"主窗口发送消息:";
    out <<type;
    for(int i=0;i<strlistMes.size();i++)
    {
        out <<strlistMes.at(i);
        qDebug() <<strlistMes.at(i);
    }

    //发送消息到服务器
    m_mainSocket->write(dataSend);
}

//更新好友列表
void QQ::UpdateFriendsList()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mydata");
    db.setUserName("root");
    db.setPassword("root");
    if (!db.open())
    {
         QMessageBox::critical(nullptr, QObject::tr("无法打开数据库"),
             "无法创建数据库连接！", QMessageBox::Cancel);
    }
    QSqlQuery createQuery;
    //创建好友信息表(friendsTable): QQ账号、好友分组、好友QQ
    createQuery.exec("create table friendsTable(id varchar(10) primary key, QQ账号 varchar(10),\
                         好友分组 varchar(20), 好友QQ varchar(10))character set = utf8");

    //建立好友列表 建立一个大的控件，把每组都弄好之后，再插入到tabWidget的一页上。
    CgroupWidget *groupWidget = new CgroupWidget(ui->tab_1);//建立了一个大的控件，并把它插入到tabWidget的一页上
    groupWidget->resize(QSize(400,1000));//设置组空间的大小

    //建立组以及组内的成员了，最后 groupWidget->addItem("每个组就好了") ;
    QSqlQuery query;
    QString sql = QString("select Distinct 好友分组 from friendsTable where QQ账号 = %1 order by 好友分组 DESC").arg(qqNumId);//根据QQ账号查找分组，在friendsTable表中
    query.exec(sql);
    while (query.next())
    {
        qDebug() << "进入数据库内部！";

        //这几句就是建立每一个分组，并把它存到m_groupList中
        QString groupName = query.value(0).toString();
        qDebug()<<"groupName: " <<groupName;
        CgroupItem *item = new CgroupItem(groupName);//建立了一个分组,名称设置为groupName

        //根据本地QQ账号获取有多少个“分组”，再建立“分组列表”
        sql = QString("select Distinct 好友QQ from friendsTable where 好友分组 = '%1'and QQ账号 = '%2'").arg(groupName).arg(qqNumId);
        QSqlQuery queryFriendQQ;//2.得到组里好友的QQ
        queryFriendQQ.exec(sql);//得到QQ好友的结果列表
        while(queryFriendQQ.next())
        {
            QString friendQQ = queryFriendQQ.value(0).toString();
            qDebug()<<"friendQQ: " << friendQQ;
            //根据好友的QQ获取好友的具体信息
            sql = QString("select  headIcon, nickname, onlineStatus from userTable where account = '%1'").arg(friendQQ);
            QSqlQuery queryFriendInfo;
            queryFriendInfo.exec(sql);
            //每个“分组”内有多个联系人，将这些联系人都加入到分组内 （类似于一个双重for循环）
            while (queryFriendInfo.next())
            {
                QString qqIcon = queryFriendInfo.value(0).toString();
                QString nicklName = queryFriendInfo.value(1).toString();
                QVariant varOnlineStatue = queryFriendInfo.value(2); //直接使用.tobool()转换，无论是0或1，得到的都是false
                bool onlineStatue = false;
                if(varOnlineStatue==QString("\u0001"))
                    onlineStatue = true;
                qDebug()<<qqIcon<<"\t"<<nicklName<<"\t"<<onlineStatue;

                CPeople *personWidget = new CPeople(friendQQ,qqIcon,nicklName,onlineStatue);
                item->addItem(personWidget);//在组里插入一个具体人的信息
                m_peopleList.append(personWidget);//存储每个人的信息。
                //设置点击personWidget，则打开一个“聊天窗口”
                connect(personWidget,SIGNAL(clicked(bool)),this,SLOT(SlotSendTalkWithDialogSignal()));//这里肯定要发送一些用户信息给对话框，例如昵称、QQ账号等
            }
        }
        m_groupList.append(item);//组的链表，后期可以用来转移分组
        groupWidget->addItem(item);//插入一组
    }
}

//关闭按钮
void QQ::on_closePushButton_clicked()
{
    QByteArray dataSend;
    QDataStream out(&dataSend,QIODevice::WriteOnly);

    //发送"用户离开"消息，将该用户的"在线状态"设置为"离线"
    QStringList strlistMes;
    strlistMes.append(qqNumId);
    qDebug() << "用户离开消息:" << qqNumId;
    SendMessage(UserLeft,strlistMes);

    m_talkWithDialog->close();//主窗口一销毁，对话窗口也销毁
    close();
}

void QQ::SlotSendTalkWithDialogSignal()
{
    for(int i = 0;i < m_groupList.size();i++)
    {
        CgroupItem * itemTemp = static_cast<CgroupItem *>(m_groupList.at(i));//获得好友列表的每一项

        for(int j = 0 ;j<itemTemp->m_itemList.size();j++ )
        {
            CPeople *personTempBtn = static_cast<CPeople *>(itemTemp->m_itemList.at(j));//要强制类型转换的

             /*需要注意的是，子窗口获取geometry，是相对于父窗口的相对位置，QCursor::pos()获取的是鼠标绝对位置，要不将父窗口的相对位置进行换算，
                要不将鼠标的绝对位置进行换算，这里本文采用将鼠标绝对位置换算到控件上，我这里是itemTemp 不是 personTempBtn 因为我是要在组里遍历的。
                并且点击的“联系人”在线状态必须是在线，才能打开与其的聊天窗口*/
            if (personTempBtn->geometry().contains(itemTemp->mapFromGlobal(QCursor::pos())) && personTempBtn->onlineStatelocal==true)//QPoint(mouse_x,mouse_y)
            {
                //取消主窗口的socket接收消息功能
                disconnect(m_mainSocket,SIGNAL(readyRead()),this,SLOT(SlotMainDialogReadMessage()));
                //把鼠标得到的控件信息发送给聊天窗口，去改变它的头像和昵称和套接字mainSocket
                qDebug()<<"鼠标得到的控件信息:"<<qqNumId <<personTempBtn->qqumlocal <<personTempBtn->headPathlocal <<personTempBtn->nickNamelocal <<m_mainSocket;
                qDebug()<<"聊天窗口——在线状态:"<<personTempBtn->onlineStatelocal;
                emit SignalShowTalkWithDialog(qqNumId,personTempBtn->nickNamelocal,personTempBtn->qqumlocal,personTempBtn->headPathlocal,m_mainSocket);
            }
        }
    }
}

void QQ::mouseMoveEvent(QMouseEvent *event) //鼠标移动事件，用来进行拖动窗口
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-mouseDragPosition); //减去原先的误差
        event->accept();//传给下面部件
    }
}
void QQ::mousePressEvent(QMouseEvent *event) //鼠标按压事件，用来进行拖动窗口
{
    if(event->button() == Qt::LeftButton)
    {
        mouseDragPosition = event->globalPos()-frameGeometry().topLeft();
        event->accept();//要加上这一句话
    }
}

//最小化
void QQ::on_miniPushButton_clicked()
{
    this->showMinimized();
}

QQ::~QQ()
{
    delete ui;
}


