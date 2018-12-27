#include "qq.h"
#include <QApplication>
#include "qqlogin.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //国际化
    QTranslator translator;
    if(QLocale::system().name() == "zh_CN")//如果是中文系统，变成中文的，不是的话，显示英文
    {
        translator.load(":/qss/login_zh_CN.qm");
        a.installTranslator(&translator);
    }

    //构建对话框
    qqLogin loginDialog;
    QQ mainDialog;
    loginDialog.show();
    //连接登陆界面和主界面
    QObject::connect(&loginDialog,SIGNAL(SignalShowMainDialog(QTcpSocket *,QStringList)),&mainDialog,SLOT(SlotAcceptLogin(QTcpSocket *,QStringList)));

    return a.exec();
}
