#include "IMFriendButton.h"
#include <QLabel>
#include <QBoxLayout>


IMFriendButton::IMFriendButton(QWidget *parent) :
    QPushButton(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    QLabel *head = new QLabel;
    head->setFixedSize(35,35);
    QLabel *mes = new QLabel;
    layout->addSpacing(1);
    layout->addWidget(head);
    layout->addWidget(mes);
    layout->addStretch();
    setMinimumSize(100,45);

    QString str = QString(":/mainDialog/images/1.jpg");
    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(35, 35));
    head->setPixmap(pixmap);

    QString text = QString("<font color=green>2014061301(demo)<br>[online]</font>");
    mes->setText(text);

    layout->setContentsMargins(4,0,0,0);
    setLayout(layout);

    setStyleSheet("QPushButton{border: 0;}");
}

void IMFriendButton::mousePressEvent(QMouseEvent *e)
{
}

IMFriendButton::~IMFriendButton()
{

}
