#include "shift.h"
#include "ui_shift.h"

Shift::Shift(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shift)
{
    ui->setupUi(this);
}

Shift::~Shift()
{
    delete ui;
}

void Shift::on_startShift_clicked()
{
    ui->startShift->setVisible(false);
    QDialog::accept();
    close();
}
