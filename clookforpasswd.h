#ifndef CLOOKFORPASSWD_H
#define CLOOKFORPASSWD_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class CLookForPassWd;
}

class CLookForPassWd : public QDialog
{
    Q_OBJECT

public:
    explicit CLookForPassWd(QWidget *parent = nullptr);
    ~CLookForPassWd();
    QTcpSocket *lookForPassWdTcpSocket;
    void setTcpSocker(QTcpSocket *socket);
private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void SlotReadMessageLookFor(QString tempQQPassWd);   // 处理接收服务器方发送的消息
    void SlotSendMsgBtn();    // 点击OK按钮后，后发送消息
    void on_lookForBtn_clicked();

private:
    Ui::CLookForPassWd *ui;
    QString lookForQQNumber;
    QString QQPassWd;
};

#endif // CLOOKFORPASSWD_H
