#include "newitem.h"
#include "ui_newitem.h"
#include <QMessageBox>

newItem::newItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newItem)
{
    ui->setupUi(this);
}

newItem::~newItem()
{
    delete ui;
}
void newItem::on_addBtn_clicked()
{
    if(ui->nameL->toPlainText()=="" || ui->costL->toPlainText().toDouble()<=0 || ui->amountL->toPlainText().toInt()<=0)
    {
        QMessageBox::critical(this, "Ошибка", "Данные введены некорректно.");
        return;
    }
    name = ui->nameL->toPlainText();
    cost = ui->costL->toPlainText().toDouble();
    amount = ui->amountL->toPlainText().toInt();

    QDialog::accept();
    close();
}

