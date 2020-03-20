#include "activex.h"
#include "ui_activex.h"

ActiveX::ActiveX(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveX)
{
    ui->setupUi(this);


}

ActiveX::~ActiveX()
{
    delete ui;
}

QString ActiveX::Version()
{
    return QString("ActiveX 1.0.0");
}

void ActiveX::on_pushButton_clicked()
{
    w = new GLYuvWidget(this);
    w->setGeometry(0,0,200,200);
    w->show();
    w->ready();
}

void ActiveX::on_pushButton_2_clicked()
{
    w->startPull();
}
