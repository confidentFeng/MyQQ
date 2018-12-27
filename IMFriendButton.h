#ifndef IMFRIENDBUTTON_H
#define IMFRIENDBUTTON_H

#include <QPushButton>

class IMFriendButton : public QPushButton
{
    Q_OBJECT
public:
    IMFriendButton(QWidget *parent = 0);
    ~IMFriendButton();


protected:
    void mousePressEvent(QMouseEvent *e);
    
signals:
    
public slots:

private:

};

#endif // IMFRIENDBUTTON_H
