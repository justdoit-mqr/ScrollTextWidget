#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scrollTextWidget = new ScrollTextWidget(this);
    QFont font;
    font.setPointSize(20);
    scrollTextWidget->setScrollProperty(5,100,100);
    scrollTextWidget->setTextProperty(QColor(Qt::white),font);
    scrollTextWidget->setScrollText(ui->lineEdit->text());
    ui->horizontalLayout->addWidget(scrollTextWidget);
}

Widget::~Widget()
{
    delete ui;
}

//重置按钮槽
void Widget::on_pushButton_clicked()
{
    scrollTextWidget->setScrollText(ui->lineEdit->text());
}

//隐藏/显示按钮槽
void Widget::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text() == "隐藏")
    {
        scrollTextWidget->hide();
        ui->pushButton_2->setText("显示");
    }
    else
    {
        scrollTextWidget->show();
        ui->pushButton_2->setText("隐藏");
    }
}

