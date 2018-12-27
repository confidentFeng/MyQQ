#include "ctalkwithdialog.h"
#include "ui_ctalkwithdialog.h"
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QMenu>
#include <QAction>

CTalkWithDialog::CTalkWithDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CTalkWithDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

void CTalkWithDialog::SlotShowTalkWithDialog(QString qqNumFrom,QString nicklName,QString qqNum,QString qqIcon,QTcpSocket *mainSocket)
{
    //设置头像和昵称
    qqNumFromLocal = qqNumFrom; //获取传进来的本地用户QQ号
    qqNumToLocal = qqNum; //获取传进来的正在聊天的用户QQ号（在用户列表选择的用户对应QQ账号）
    qqnecklNameLocal = nicklName; //获取传过来的用户名
    qDebug() <<"聊天界面接收"<<qqNumFromLocal<<nicklName<<qqNumToLocal<<qqIcon;
    ui->iconToolButton->setStyleSheet(QString("border-image: url(%1);").arg(qqIcon));
    ui->neckNameLabel->setText(nicklName);

    m_TcpSocket = mainSocket; //从主窗口传来的套接字
    //Qt::UniqueConnection - 防止重复连接，如果当前信号和槽已经连接过了，将不再连接。
    connect(m_TcpSocket,SIGNAL(readyRead()),this,SLOT(SlotReadMessageTalk()),Qt::UniqueConnection);
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(SlotSendMsgBtn()));//绑定“发送消息”按钮

    ui->messageBrowser->clear();//每打开一个聊天界面，清空“聊天对话栏”文字

    /* 显示菜单 */
    QMenu * menu = ui->menuButton->getmenu();
    b1 = new QAction(QIcon(":/images/menu.png"), tr("&星球皮肤"), this);
    b2 = new QAction(QIcon(":/images/menu.png"), tr("&绿草皮肤"), this);
    b3 = new QAction(QIcon(":/images/menu.png"), tr("&动漫皮肤"), this);
    b4 = new QAction(QIcon(":/images/menu.png"), tr("&炫酷皮肤"), this);
    b = new QAction(QIcon(":/images/menu.png"), tr("&原始皮肤"), this);
    menu->addAction(b1);
    menu->addAction(b2);
    menu->addAction(b3);
    menu->addAction(b4);
    menu->addAction(b);
    connect(b1,SIGNAL(triggered(bool)),this,SLOT(bg1()));
    connect(b2,SIGNAL(triggered(bool)),this,SLOT(bg2()));
    connect(b3,SIGNAL(triggered(bool)),this,SLOT(bg3()));
    connect(b4,SIGNAL(triggered(bool)),this,SLOT(bg4()));
    connect(b,SIGNAL(triggered(bool)),this,SLOT(bg()));

    this->show();
}

void CTalkWithDialog::SlotSendMsgBtn()//点击发送按钮
{
    //构造发送信息
    currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    structMsg = "<font size='+1'>["+qqnecklNameLocal +"]</font>" + currentTime;

    sendLineText = ui->messageTextEdit->toHtml();//要用这个函数，便于设置字体格式
    //sendLineText = ui->messageTextEdit->toPlainText();

    if(ui->messageTextEdit->toPlainText() != "")
    {
        sendMsg(Msg,sendLineText); //给指定用户发消息
        //本地显示消息
        ui->messageBrowser->append(structMsg);
        ui->messageBrowser->append(sendLineText);
    }
    ui->messageTextEdit->clear();//清空发送区
}

void CTalkWithDialog::sendMsg(MsgType type,QString sendText)
{
    QByteArray dataSend;
    QDataStream out(&dataSend,QIODevice::WriteOnly);

    out<< type << qqNumFromLocal << qqNumToLocal  ;//构建了报头: 类型 发送发，接收方，，后面要加上内容

    switch (type) //根据类型进行相应的处理
    {
        case Msg:
        {
            out << structMsg << sendText;//用户时间信息加上发送内容
        }
        break;

        default:
        break;
    }
    m_TcpSocket->write(dataSend);//发送最终处理过的数据 先不用转化
}

void CTalkWithDialog::SlotReadMessageTalk()
{
    QDataStream in(m_TcpSocket);
    QString type;
    QString structMsg;
    QString message;

    in>>type >>structMsg >>message;
    qDebug()<<"聊天窗口接收："<<type <<" " <<structMsg <<" " <<message;
    ui->messageBrowser->append(structMsg);
    ui->messageBrowser->append(message);
}

void CTalkWithDialog::SlotReveiveMainDialogMessage(QString structMessage , QString realMessage)
{
    ui->messageBrowser->append(structMessage);//显示信息
    ui->messageBrowser->append(realMessage);//显示信息
}

void CTalkWithDialog::on_minButton_clicked()
{
    this->showMinimized();
}
void CTalkWithDialog::on_maxButton_clicked()
{
    this->showMaximized();
}
void CTalkWithDialog::on_closeButton_clicked()
{
    this->close();
}
void CTalkWithDialog::on_exitButton_clicked()
{
    this->close();
}
void CTalkWithDialog::on_menuButton_clicked()
{

}

void CTalkWithDialog::bg1()
{
    //有异常，后续解决
    //ui->widget->setStyleSheet("QWidget {background-image: url(:/talkDialog/images/talkwith/background1.jpg);}");
}
void CTalkWithDialog::bg2()
{
    //ui->widget->setStyleSheet("QWidget {background-image: url(:/talkDialog/images/talkwith/background1.jpg);}");
}
void CTalkWithDialog::bg3()
{
    //ui->widget->setStyleSheet("QWidget {background-image: url(:/talkDialog/images/talkwith/background1.jpg);}");
}
void CTalkWithDialog::bg4()
{
    //ui->widget->setStyleSheet("QWidget {background-image: url(:/talkDialog/images/talkwith/background1.jpg);}");
}

void CTalkWithDialog::bg()
{
    //ui->widget->setStyleSheet("QWidget {background-image: url(:/talkDialog/images/talkwith/background.jpg);}");
}

//保存文件记录
void CTalkWithDialog::on_saveToolButton_clicked()
{
    if (ui->messageBrowser->document()->isEmpty()) {
        QMessageBox::warning(nullptr, tr("警告"), tr("聊天记录为空，无法保存！"), QMessageBox::Ok);
    } else {
        QString fname = QFileDialog::getSaveFileName(this,tr("保存聊天记录"), /*"/" 代表目录*/tr("聊天记录"), tr("文本(*.txt);;所有文件(*.*)"));
        if(!fname.isEmpty())
            saveFile(fname);
    }
}

//保存文件
bool CTalkWithDialog::saveFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("保存文件"),tr("无法保存文件 %1:\n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->messageBrowser->toPlainText();

    return true;
}

//清除聊天记录
void CTalkWithDialog::on_clearToolButton_clicked()
{
    ui->messageBrowser->clear();
}

//改变字体
void CTalkWithDialog::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->messageTextEdit->setCurrentFont(f);
    //ui->messageBrowser->setCurrentFont(f);
    ui->messageTextEdit->setFocus();
}
//改变字号
void CTalkWithDialog::on_sizeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->messageTextEdit->setFontPointSize(arg1.toDouble());
    //ui->messageBrowser->setFontPointSize(arg1.toDouble());
    ui->messageTextEdit->setFocus();
}

void CTalkWithDialog::on_boldToolButton_clicked(bool checked)
{
    if(checked)
    {
        ui->messageTextEdit->setFontWeight(QFont::Bold);
        //ui->messageBrowser->setFontWeight(QFont::Bold);
    }
    else
    {

        ui->messageTextEdit->setFontWeight(QFont::Normal);
        //ui->messageBrowser->setFontWeight(QFont::Normal);
    }
    ui->messageTextEdit->setFocus();
}


void CTalkWithDialog::on_italicToolButton_clicked(bool checked)
{
    ui->messageTextEdit->setFontItalic(checked);
    //ui->messageBrowser->setFontItalic(checked);
    ui->messageTextEdit->setFocus();
}

void CTalkWithDialog::on_underlineToolButton_clicked(bool checked)
{
    ui->messageTextEdit->setFontUnderline(checked);
    //ui->messageBrowser->setFontUnderline(checked);
    ui->messageTextEdit->setFocus();
}
//设置文本颜色
void CTalkWithDialog::on_colorToolButton_clicked()
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid()){
        ui->messageTextEdit->setTextColor(color);
        //ui->messageBrowser->setTextColor(color);
        ui->messageTextEdit->setFocus();
    }
}


CTalkWithDialog::~CTalkWithDialog()
{
    delete ui;
}

void CTalkWithDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-mouseDragPosition);//减去原先的误差
        event->accept();
    }
}

void CTalkWithDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseDragPosition = event->globalPos()-frameGeometry().topLeft();
        event->accept();//要加上这一句话
    }
}
