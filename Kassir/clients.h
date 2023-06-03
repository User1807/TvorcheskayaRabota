#ifndef CLIENTS_H
#define CLIENTS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "newclient.h"
#include "QTableWidgetItem"

namespace Ui {
class Clients;
}

class Clients : public QDialog
{
    Q_OBJECT

public:
    explicit Clients(QWidget *parent = nullptr);
    ~Clients();
    QList<QString> searchTable(const QString& searchTerm);
    QString getPoints() {return points;};
    QString getName() {return name;};
    QString getPhone() {return phone;};

private slots:
    void on_search_2_textChanged();

    bool on_addItem_clicked();

    void on_acceptBtn_clicked();

private:
    Ui::Clients *ui;
    QSqlDatabase clients;
    QSqlQuery *query;
    QSqlTableModel *model;
    QString name;
    QString phone;
    QString card;
    QString points;
};

#endif // CLIENTS_H
