#ifndef HISTORY_H
#define HISTORY_H

#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class History;
}

class History : public QDialog
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = nullptr);
    ~History();

private:
    Ui::History *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
};

#endif // HISTORY_H
