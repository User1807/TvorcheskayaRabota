#ifndef PAYMENTDONE_H
#define PAYMENTDONE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class PaymentDone;
}

class PaymentDone : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentDone(QWidget *parent = nullptr);
    ~PaymentDone();
    void setFinalCost(double cost);

private slots:
    void on_newSell_clicked();

private:
    Ui::PaymentDone *ui;
    double finalCost;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
};

#endif // PAYMENTDONE_H
