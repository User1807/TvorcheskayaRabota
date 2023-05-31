#include "newclient.h"
#include "ui_newclient.h"
#include <QMessageBox>

newClient::newClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newClient)
{
    ui->setupUi(this);
}

newClient::~newClient()
{
    delete ui;
}

void newClient::on_addBtn_clicked()
{
    if(ui->nameL->toPlainText()==""
            || ui->phoneL->toPlainText()==""
            || ui->cardL->toPlainText()=="")
    {
        QMessageBox::critical(this, "Ошибка", "Данные введены некорректно.");
        return;
    }
    name = ui->nameL->toPlainText();
    phone = ui->phoneL->toPlainText();
    card = ui->cardL->toPlainText();

    QDialog::accept();
    close();
}

