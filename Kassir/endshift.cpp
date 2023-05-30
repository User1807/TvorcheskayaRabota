#include "endshift.h"
#include "ui_endshift.h"

EndShift::EndShift(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndShift)
{
    ui->setupUi(this);
    ui->endShift->setVisible(true);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->closeBtn->setVisible(false);
}

EndShift::~EndShift()
{
    delete ui;
}


void EndShift::on_endShift_clicked()
{
    ui->endShift->setVisible(false);
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->closeBtn->setVisible(true);
    ui->label->setText("Общая выручка за смену: " + total);
    ui->label_2->setText("Наличными:  " + nal);
    ui->label_3->setText("Картой: " + card);
    ui->label_4->setText("Всего продаж: " + sells);
    ui->label_6->setText("Смена начата: " + startTime.date().toString().mid(0, 9) +
                         ' ' + startTime.time().toString());
    ui->label_7->setText("Смена закончена: " + endTime.date().toString().mid(0, 9) +
                         ' ' + endTime.time().toString());
}

void EndShift::on_closeBtn_clicked()
{
    QDialog::accept();
}

