#include "paymentdone.h"
#include "ui_paymentdone.h"

PaymentDone::PaymentDone(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentDone)
{
    ui->setupUi(this);
    setWindowTitle("Оплата");
    setFinalCost(finalCost);
}

PaymentDone::~PaymentDone()
{
    delete ui;
}

void PaymentDone::setFinalCost(double cost)
{
    ui->paidLabel->setText("Оплачено: " + QString::number(cost));
    finalCost = cost;
}

void PaymentDone::on_newSell_clicked()
{
    close();
    setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    activateWindow();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("productsDB.db");
    db.open();
    query = new QSqlQuery(db);
    model = new QSqlTableModel(this, db);
    model->select();
}

