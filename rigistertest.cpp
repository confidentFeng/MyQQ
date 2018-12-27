#include "rigistertest.h"
#include "ui_rigister.h"

rigister::rigister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rigister)
{
    ui->setupUi(this);
}

rigister::~rigister()
{
    delete ui;
}

void rigister::on_pushButton_clicked()
{
//    QSqlQueryModel *model = new QSqlQueryModel;
//    model->setQuery("select * from city");//这里直接设置SQL语句，忽略最后一个参数
////    model->setHeaderData(0, Qt::Horizontal, tr("1"));//这只每一列的标识
////    model->setHeaderData(1, Qt::Horizontal, tr("2"));
////    model->setHeaderData(2, Qt::Horizontal, tr("3"));
//    ui->tableView->setModel(model);

////    //以下是视觉方面的效果，不加也没影响

//    //隔行变色
//    ui->tableView->setAlternatingRowColors(true);

//    //设置行高
//    int row_count = model->rowCount();
//    for(int i =0; i < row_count; i++)
//    {
//        ui->tableView->setRowHeight(i, 50);
//    }

        QSqlQuery query;
        query.exec("select * from city");
        qDebug() << "exec next() :";
        //开始就先执行一次next()函数，那么query指向结果集的第一条记录
        if(query.next())
        {
           //获取query所指向的记录在结果集中的编号
           int rowNum = query.at();
           //获取每条记录中属性（即列）的个数
           int columnNum = query.record().count();
           //获取"city"属性所在列的编号，列从左向右编号，最左边的编号为0
           int fieldNo = query.record().indexOf("city");
           //获取id属性的值，并转换为int型,我这个数据库没有Id这个属性
           //int id = query.value(0).toInt();
           //获取name属性的值
           QString city = query.value(fieldNo).toString();
           //将结果输出
           qDebug() << "rowNum is : " << rowNum
                    << " columnNum is : " << columnNum
           << " fieldNo is : " << fieldNo
                  //   << " id is : " << id
                     << " city is : " << city;

        }
}

