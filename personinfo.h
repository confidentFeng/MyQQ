#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QWidget>
#include <QString>
namespace Ui {
class personinfo;
}

class personinfo : public QWidget
{
    Q_OBJECT

public:
    explicit personinfo(QString headPath,QString neckName,bool onlineState,QWidget *parent = 0);//把头像，昵称，和在线状态传过来
    ~personinfo();

private:
    Ui::personinfo *ui;
};

#endif // PERSONINFO_H
