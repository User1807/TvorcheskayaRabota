#ifndef PAYMENT_H
#define PAYMENT_H

#include <QTableWidgetItem>
#include <QDialog>
#include "history.h"
#include "clients.h"

namespace Ui {
class Payment;
}

class Payment : public QDialog
{
    Q_OBJECT

public:
    explicit Payment(QWidget *parent = nullptr);
    ~Payment();
    void setFinalCost(double cost);
    bool addToDB(QDateTime dt, QString method, double sum);
    void changeInDB(int points, QString name, QString phone);
    double getTotal(){return total;};
    double getNal(){return nal;};
    double getCard(){return card;};
    int getSells(){return sells;};

private slots:
    void on_nalButton_clicked();

    void on_nalTB_textChanged();

    void on_cardButton_clicked();

    bool on_clientsButton_clicked();

    void on_usePts_clicked();

private:
    Ui::Payment *ui;
    double finalCost;
    double sum;
    int elementsInDB;
    QSqlQuery *query;
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlRecord *record;
    QString nameToChange;
    QString phoneToChange;
    int ptsToDB;
    double total=0;
    double nal=0;
    double card=0;
    int sells=0;
};

#endif // PAYMENT_H
