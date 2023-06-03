#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "payment.h"
#include <QtSql>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("АРМ Кассира");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./productsDB.db");
    db.open();
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE HistoryTable(Название TEXT, Стоимость DOUBLE, Количество INT);");

    model = new QSqlTableModel(this, db);
    model->setTable("tableView");
    model->select();
    QTableView *view = ui->tableView;
    view->setModel(model);
    view->setAlternatingRowColors(true);
    view->setColumnWidth(0, view->width()/3);
    view->setColumnWidth(1, view->width()/3);
    view->setColumnWidth(2, view->width()/3);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->check->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    finalCost = 0;
    isNew=1;
    countInCheck = 1;
    int countInTable = ui->tableView->model()->index(index.row(), 2).data(Qt::DisplayRole).toInt();
    countInTable--;

    QSqlRecord record = model->record(index.row());
    QVariant nameValue = record.value(0);
    QVariant costValue = record.value(1);

    QString name = nameValue.toString();
    double cost = costValue.toDouble();
    for(int i = 0; i < elementsCount; i++)
    {
        if(ui->check->item(i, 0)->text() == name)
        {
            isNew = 0;
            countInCheck = ui->check->item(i, 2)->text().toInt()+1;
            costInCheck = ui->check->item(i, 1)->text().toDouble()*countInCheck;
            QTableWidgetItem *count = new QTableWidgetItem(QString::number(countInCheck));
            QTableWidgetItem *baseCost = new QTableWidgetItem(QString::number(cost));
            QTableWidgetItem *cost = new QTableWidgetItem(QString::number(costInCheck));

            ui->check->setItem(i, 2, count);
            ui->check->setItem(i, 1, baseCost);
            ui->check->setItem(i, 3, cost);
        }
    }
    if(isNew == 1)
    {
        QTableWidgetItem *count = new QTableWidgetItem(QString::number(countInCheck));
        elementsCount+=1;
        ui->check->setRowCount(ui->check->rowCount() + 1);
        if(elementsCount==1)
        {
            ui->check->setColumnCount(4);
            ui->check->setHorizontalHeaderLabels(QStringList()<<"Название"<<"Стоимость"<<"Количество"<<"Итог");
        }
        QTableWidgetItem *nameI= new QTableWidgetItem(name);
        QTableWidgetItem *costI = new QTableWidgetItem(QString::number(cost));
        QTableWidgetItem *baseCostI = new QTableWidgetItem(QString::number(cost));
        ui->check->setItem(elementsCount-1, 0, nameI);
        ui->check->setItem(elementsCount-1, 1, baseCostI);
        ui->check->setItem(elementsCount-1, 2, count);
        ui->check->setItem(elementsCount-1, 3, costI);
    }
    QModelIndex countIndex = ui->tableView->model()->index(index.row(), 2);
    model->setData(countIndex, countInTable);
    ui->sumText->setText(QString::number(getFinalCost()));
}

double MainWindow::getFinalCost()
{
    finalCost = 0;
    for(int i = 0; i < elementsCount; i++)
    {
        finalCost+=ui->check->item(i, 3)->text().toDouble();
    }
    return finalCost;
}

void MainWindow::on_payButton_clicked()
{
    if(finalCost<=0)
        return;
    ui->check->clear();
    ui->check->clearContents();
    ui->check->setRowCount(0);
    ui->check->setColumnCount(0);
    elementsCount = 0;
    ui->sumText->clear();
    Payment *wnd = new Payment(this);
    wnd->setFinalCost(finalCost);
    finalCost=0;
    wnd->show();
    if(wnd->exec()==QDialog::Accepted)
    {
        total += wnd->getTotal();
        nal += wnd->getNal();
        card+=wnd->getCard();
        sells++;
    }
}

void MainWindow::on_check_clicked(const QModelIndex &index)
{
    int countValue = ui->check->item(index.row(), 2)->text().toInt();
    QTableWidgetItem *cost = new QTableWidgetItem(ui->check->item(index.row(), 1)->text());
    QTableWidgetItem *count = new QTableWidgetItem(QString::number(countValue));
    name = ui->check->item(index.row(), 0)->text();
    if(count->text().toInt()>1)
    {
        countValue--;
        count = new QTableWidgetItem(QString::number(countValue));
        ui->check->setItem(index.row(), 2, count);
        ui->check->setItem(index.row(), 3, cost);
        costInCheck = ui->check->item(index.row(), 3)->text().toDouble()*countValue;
        cost->setData(0, costInCheck);
    }
    else
    {
        ui->check->removeRow(index.row());
        elementsCount--;
    }

    for (int i = 0; i < model->rowCount(); i++)
    {
        QVariant value = model->data(model->index(i, 0)).toString();
        if (value == name)
        {
            QModelIndex countIndex = model->index(i, 2);
            QVariant countValue = countIndex.data();
            int count = countValue.toInt() + 1;
            model->submitAll();
            model->setData(countIndex, count);
            model->submitAll();
            break;
        }
    }

    ui->sumText->setText(QString::number(getFinalCost()));
}

void MainWindow::on_history_triggered()
{
    History *wnd = new History(this);
    wnd->show();
}

void MainWindow::on_clientsButton_clicked()
{
    Clients *wnd = new Clients(this);
    wnd->show();
}


void MainWindow::on_search_textChanged()
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(ui->tableView);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    proxyModel->setFilterRegExp(ui->search->toPlainText());

    ui->tableView->setModel(proxyModel);
    ui->tableView->show();
}

bool MainWindow::on_addItem_clicked()
{
    newItem* dialog = new newItem(this);
    if (dialog->exec() == QDialog::Accepted) {
        QString name = dialog->getName();
        double cost = dialog->getCost();
        int amount = dialog->getAmount();

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("productsDB.db");
        if (!db.open()) {
            qDebug() << "Не удалось открыть базу данных";
            return false;
        }
        query = new QSqlQuery(db);
        query->exec("CREATE TABLE tableView(Название TEXT, "
                    "Стоимость DOUBLE, Количество INT);");


        model = new QSqlTableModel(this, db);
        model->setTable("tableView");

        QSqlQuery query;
        query.prepare("INSERT INTO tableView (Название, Стоимость, Количество) "
                      "VALUES (:name, :cost, :amount)");
        query.bindValue(":name", name);
        query.bindValue(":cost", cost);
        query.bindValue(":amount", amount);;

        if (!query.exec()) {
            qDebug() << "Не удалось выполнить запрос:" << query.lastError().text();
            return false;
        }

        model->select();
        ui->tableView->setModel(model);
        connect(model, &QSqlTableModel::dataChanged, ui->tableView, &QTableView::reset);
    }
    delete dialog;
    return true;
}

void MainWindow::on_shift_triggered()
{
    if(!started)
    {
        Shift *dialog = new Shift;
        if (dialog->exec() == QDialog::Accepted)
        {
            startTime = QDateTime::currentDateTime();
            started = true;
            ui->tableView->setEnabled(true);
            ui->shiftNeeded->setMaximumSize(0, 0);
            total = 0;
            nal = 0;
            card = 0;
            sells = 0;
        }
        delete dialog;
    }
    else
    {
        EndShift *dialog = new EndShift;
        endTime = QDateTime::currentDateTime();
        dialog->setEnd(endTime);
        dialog->setTotal(total);
        dialog->setNal(nal);
        dialog->setCard(card);
        dialog->setSells(sells);
        dialog->setStart(startTime);
        dialog->exec();
        if (dialog->Accepted||dialog->Rejected)
        {          
            ui->tableView->setEnabled(false);
            ui->shiftNeeded->setMaximumSize(999999, 21);
            ui->shiftNeeded->setVisible(true);
            started = false;
            ui->tableView->setEnabled(false);
            ui->shiftNeeded->setVisible(true);
            total = 0;
            nal = 0;
            card = 0;
            sells = 0;
        }
        delete dialog;
    }
}

