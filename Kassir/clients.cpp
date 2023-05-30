#include "clients.h"
#include "ui_clients.h"
#include <QtSql>

Clients::Clients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clients)
{
    ui->setupUi(this);
    setWindowTitle("Покупатели");
    clients = QSqlDatabase::addDatabase("QSQLITE");
    clients.setDatabaseName("./clientsDB.db");
    clients.open();
    query = new QSqlQuery(clients);
    query->exec("CREATE TABLE ClientsTable(ФИО TEXT, Телефон TEXT, Карта TEXT, Баллы INT);");

    model = new QSqlTableModel(this, clients);
    model->setTable("ClientsTable");
    model->select();
    QTableView *view = ui->ClientsTable;
    view->setModel(model);
    view->setColumnWidth(0, view->width()/4);
    view->setColumnWidth(1, view->width()/4);
    view->setColumnWidth(2, view->width()/4);
    view->setColumnWidth(3, view->width()/4);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->show();
}

Clients::~Clients()
{
    delete ui;
}

bool Clients::on_addItem_clicked()
{
    newClient *dialog = new newClient;
    if (dialog->exec() == QDialog::Accepted) {
        name = dialog->getName();
        phone = dialog->getPhone();
        card = dialog->getCard();
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("clientsDB.db");
        if (!db.open()) {
            qDebug() << "Не удалось открыть базу данных";
            return false;
        }
        query = new QSqlQuery(db);
        query->exec("CREATE TABLE ClientsTable(ФИО TEXT, Телефон TEXT, Карта TEXT, Баллы INT);");


        model = new QSqlTableModel(this, db);
        model->setTable("ClientsTable");

        QSqlQuery query;
        query.prepare("INSERT INTO ClientsTable (ФИО, Телефон, Карта, Баллы) VALUES (:name, :phone, :card, :points)");
        query.bindValue(":name", name);
        query.bindValue(":phone", phone);
        query.bindValue(":card", card);
        query.bindValue(":points", 0);

        if (!query.exec()) {
            qDebug() << "Не удалось выполнить запрос:" << query.lastError().text();
            return false;
        }

        model->select();
        ui->ClientsTable->setModel(model);
        connect(model, &QSqlTableModel::dataChanged, ui->ClientsTable, &QTableView::reset);
        db.close();
    }
    delete dialog;
    return true;
}

void Clients::on_search_2_textChanged()
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(ui->ClientsTable);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    proxyModel->setFilterRegExp(ui->search_2->toPlainText());

    ui->ClientsTable->setModel(proxyModel);
    ui->ClientsTable->show();
}

void Clients::on_acceptBtn_clicked()
{
    QModelIndexList selectedIndexes = ui->ClientsTable->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty())
    {
        QModelIndex selectedIndex = selectedIndexes.first();
        QModelIndex ptsIndex = selectedIndex.sibling(selectedIndex.row(), 3);
        QModelIndex nameIndex = selectedIndex.sibling(selectedIndex.row(), 0);
        QModelIndex phoneIndex = selectedIndex.sibling(selectedIndex.row(), 1);

        points = ptsIndex.data().toString();
        phone = phoneIndex.data().toString();
        name = nameIndex.data().toString();
        QDialog::accept();
        close();
    }
}
