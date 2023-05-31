#include "history.h"
#include "ui_history.h"
#include <QDateTime>

History::History(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    setWindowTitle("История продаж");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./historyDB.db");
    db.open();
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE HistoryTable(Время TEXT, № TEXT, Способ TEXT, Итог DOUBLE);");

    model = new QSqlTableModel(this, db);
    model->setTable("HistoryTable");
    model->select();
    QTableView *view = ui->HistoryTable;
    view->setModel(model);
    view->setAlternatingRowColors(true);
    view->setColumnWidth(0, view->width()/4);
    view->setColumnWidth(1, view->width()/4);
    view->setColumnWidth(2, view->width()/4);
    view->setColumnWidth(3, view->width()/4);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->show();
}

History::~History()
{
    delete ui;
}
