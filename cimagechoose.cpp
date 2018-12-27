#include "cimagechoose.h"
#include "ui_cimagechoose.h"

CImageChoose::CImageChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CImageChoose)
{
    ui->setupUi(this);
    setWindowTitle("选择头像");
    setWindowFlags(Qt::SplashScreen);
}

CImageChoose::~CImageChoose()
{
    delete ui;
}

//头像选择按钮
void CImageChoose::on_pushButton_1_clicked()
{
    QString imageUrl = ":/mainDialog/images/1.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_2_clicked()
{
    QString imageUrl = ":/mainDialog/images/2.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_3_clicked()
{
    QString imageUrl = ":/mainDialog/images/3.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_4_clicked()
{
    QString imageUrl = ":/mainDialog/images/4.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_5_clicked()
{
    QString imageUrl = ":/mainDialog/images/5.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_6_clicked()
{
    QString imageUrl = ":/mainDialog/images/6.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_7_clicked()
{
    QString imageUrl = ":/mainDialog/images/7.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_9_clicked()
{
    QString imageUrl = ":/mainDialog/images/9.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_8_clicked()
{
    QString imageUrl = ":/mainDialog/images/8.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}

void CImageChoose::on_pushButton_10_clicked()
{
    QString imageUrl = ":/mainDialog/images/10.jpg";
    emit SignalImageUrl(imageUrl);
    close();
}
