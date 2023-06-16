# Видео: https://www.youtube.com/watch?v=LDE51ldkoZc


## Постановка задачи

1\. Придумать функциональный набор профессиональных навыков для конкретного АРМа, внешних параметров обеспечения работы и инструментов для реализации навыков.

2\. Графический интерфейс пользователя должен быть выполнен при помощи фреймворка Qt и управляться событиями.

3\. АРМ должен поддерживать ввод данных оператором, а также их преобразование, согласно заданному алгоритму, и вывод результатов преобразования в графический интерфейс с визуализацией (диаграммы, графики, таблицы, карты).

4\. Предусмотреть режим тестовой генерации событий при помощи генератора случайных чисел и/или общедоступных внешних данных.


<a name="ole_link1"></a><a name="ole_link2"></a>Скриншоты работы программы:

![](Aspose.Words.70a020c0-2b7d-4e80-9cca-03c9a3d0f4eb.001.png)

![](Aspose.Words.70a020c0-2b7d-4e80-9cca-03c9a3d0f4eb.002.png)

![](Aspose.Words.70a020c0-2b7d-4e80-9cca-03c9a3d0f4eb.003.png)

![](Aspose.Words.70a020c0-2b7d-4e80-9cca-03c9a3d0f4eb.004.png)

![](Aspose.Words.70a020c0-2b7d-4e80-9cca-03c9a3d0f4eb.005.png)

![](Aspose.Words.70a020c0-2b7d-4e80-9cca-03c9a3d0f4eb.006.png)


## Исходный код:

### Clients.h

#ifndef CLIENTS\_H

#define CLIENTS\_H

#include <QDialog>

#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSqlTableModel>

#include "newclient.h"

#include "QTableWidgetItem"

*namespace* **Ui** {

*class* **Clients**;

}

*class* **Clients** : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* **Clients**(QWidget \*parent = *nullptr*);

`    `~***Clients***();

`    `QList<QString> **searchTable**(*const* QString& searchTerm);

`    `QString **getPoints**() {*return* points;};

`    `QString **getName**() {*return* name;};

`    `QString **getPhone**() {*return* phone;};

*private* slots:

`    `void **on\_search\_2\_textChanged**();

`    `bool **on\_addItem\_clicked**();

`    `void **on\_acceptBtn\_clicked**();

*private*:

`    `Ui::Clients \*ui;

`    `QSqlDatabase clients;

`    `QSqlQuery \*query;

`    `QSqlTableModel \*model;

`    `QString name;

`    `QString phone;

`    `QString card;

`    `QString points;

};

#endif *//* *CLIENTS\_H*

### Endshift.h

#ifndef ENDSHIFT\_H

#define ENDSHIFT\_H

#include <QDialog>

#include <QDateTime>

*namespace* Ui {

*class* EndShift;

}

*class* EndShift : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* EndShift(QWidget \*parent = *nullptr*);

`    `~EndShift();

`    `void setTotal(double value) {total = QString::number(value);};

`    `void setNal(double value) {nal = QString::number(value);};

`    `void setCard(double value) {card = QString::number(value);};

`    `void setSells(int value) {sells = QString::number(value);};

`    `void setStart(QDateTime dt) {startTime = dt;};

`    `void setEnd(QDateTime dt) {endTime = dt;};

*private* *slots*:

`    `void on\_endShift\_clicked();

`    `void on\_closeBtn\_clicked();

*private*:

`    `Ui::EndShift \*ui;

`    `QString total;

`    `QString nal;

`    `QString card;

`    `QString sells;

`    `QDateTime startTime;

`    `QDateTime endTime;

};

#endif *//* *ENDSHIFT\_H*


### History.h

#ifndef HISTORY\_H

#define HISTORY\_H

#include <QTableWidgetItem>

#include <QSqlDatabase>

#include <QDialog>

#include <QSqlQuery>

#include <QSqlTableModel>

*namespace* Ui {

*class* History;

}

*class* History : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* History(QWidget \*parent = *nullptr*);

`    `~History();

*private*:

`    `Ui::History \*ui;

`    `QSqlDatabase db;

`    `QSqlQuery \*query;

`    `QSqlTableModel \*model;

};

#endif *//* *HISTORY\_H*

### Mainwindow.h

#ifndef MAINWINDOW\_H

#define MAINWINDOW\_H

#include <QMainWindow>

#include "history.h"

#include "clients.h"

#include "newitem.h"

#include "shift.h"

#include "endshift.h"

#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSqlTableModel>

#include <QDateTime>

QT\_BEGIN\_NAMESPACE

*namespace* Ui { *class* MainWindow; }

QT\_END\_NAMESPACE

*class* MainWindow : *public* QMainWindow

{

`    `Q\_OBJECT

*public*:

`    `MainWindow(QWidget \*parent = *nullptr*);

`    `~MainWindow();

`    `double getFinalCost();

`    `QList<QString> searchTable(*const* QString& searchTerm);

*private* *slots*:

`    `*//void* *on\_tableWidget\_clicked(const* *QModelIndex* *&index);*

`    `void on\_payButton\_clicked();

`    `void on\_check\_clicked(*const* QModelIndex &index);

`    `void on\_history\_triggered();

`    `void on\_clientsButton\_clicked();

`    `void on\_search\_textChanged();

`    `bool on\_addItem\_clicked();

`    `void on\_tableView\_clicked(*const* QModelIndex &index);

`    `void on\_shift\_triggered();

*private*:

`    `Ui::MainWindow \*ui;

`    `int elementsCount = 0;

`    `double finalCost = 0;

`    `int countInCheck = 0;

`    `double costInCheck = 0;

`    `bool isNew = 0;

`    `QString name;

`    `QSqlDatabase db;

`    `QSqlQuery \*query;

`    `QSqlTableModel \*model;

`    `double total;

`    `double nal;

`    `double card;

`    `int sells;

`    `QDateTime startTime;

`    `QDateTime endTime;

`    `bool started;

};

#endif *//* *MAINWINDOW\_H*

### Newclient.h

#ifndef NEWCLIENT\_H

#define NEWCLIENT\_H

#include <QDialog>

*namespace* Ui {

*class* newClient;

}

*class* newClient : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* newClient(QWidget \*parent = *nullptr*);

`    `~newClient();

`    `QString getName() {*return* name;};

`    `QString getPhone() {*return* phone;};

`    `QString getCard() {*return* card;};

*private* *slots*:

`    `void on\_addBtn\_clicked();

*private*:

`    `Ui::newClient \*ui;

`    `QString name;

`    `QString phone;

`    `QString card;

};

#endif *//* *NEWCLIENT\_H*

### Newitem.h

#ifndef NEWITEM\_H

#define NEWITEM\_H

#include <QDialog>

#include <mainwindow.h>

*namespace* Ui {

*class* newItem;

}

*class* newItem : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* newItem(QWidget \*parent = *nullptr*);

`    `~newItem();

`    `QString getName() {*return* name;};

`    `double getCost() {*return* cost;};

`    `int getAmount() {*return* amount;};

*private* *slots*:

`    `void on\_addBtn\_clicked();

*private*:

`    `Ui::newItem \*ui;

`    `QString name;

`    `double cost;

`    `int amount;

};

#endif *//* *NEWITEM\_H*

### Payment.h

#ifndef PAYMENT\_H

#define PAYMENT\_H

#include <QTableWidgetItem>

#include <QDialog>

#include "history.h"

#include "clients.h"

*namespace* Ui {

*class* Payment;

}

*class* Payment : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* Payment(QWidget \*parent = *nullptr*);

`    `~Payment();

`    `void setFinalCost(double cost);

`    `bool addToDB(QDateTime dt, QString method, double sum);

`    `void changeInDB(int points, QString name, QString phone);

`    `double getTotal(){*return* total;};

`    `double getNal(){*return* nal;};

`    `double getCard(){*return* card;};

`    `int getSells(){*return* sells;};

*private* *slots*:

`    `void on\_nalButton\_clicked();

`    `void on\_nalTB\_textChanged();

`    `void on\_cardButton\_clicked();

`    `bool on\_clientsButton\_clicked();

`    `void on\_usePts\_clicked();

*private*:

`    `Ui::Payment \*ui;

`    `double finalCost;

`    `double sum;

`    `int elementsInDB;

`    `QSqlQuery \*query;

`    `QSqlDatabase db;

`    `QSqlTableModel \*model;

`    `QSqlRecord \*record;

`    `QString nameToChange;

`    `QString phoneToChange;

`    `int ptsToDB;

`    `double total=0;

`    `double nal=0;

`    `double card=0;

`    `int sells=0;

};

#endif *//* *PAYMENT\_H*

### Paymentdone.h

#ifndef PAYMENTDONE\_H

#define PAYMENTDONE\_H

#include <QDialog>

#include <QSqlDatabase>

#include <QSqlQuery>

#include <QSqlTableModel>

*namespace* Ui {

*class* PaymentDone;

}

*class* PaymentDone : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* PaymentDone(QWidget \*parent = *nullptr*);

`    `~PaymentDone();

`    `void setFinalCost(double cost);

*private* *slots*:

`    `void on\_newSell\_clicked();

*private*:

`    `Ui::PaymentDone \*ui;

`    `double finalCost;

`    `QSqlDatabase db;

`    `QSqlQuery \*query;

`    `QSqlTableModel \*model;

};

#endif *//* *PAYMENTDONE\_H*

### Shift.h

#ifndef SHIFT\_H

#define SHIFT\_H

#include <QDialog>

*namespace* Ui {

*class* Shift;

}

*class* Shift : *public* QDialog

{

`    `Q\_OBJECT

*public*:

`    `*explicit* Shift(QWidget \*parent = *nullptr*);

`    `~Shift();

*private* *slots*:

`    `void on\_startShift\_clicked();

*private*:

`    `Ui::Shift \*ui;

};

#endif *//* *SHIFT\_H*

### Clients.cpp

#include "clients.h"

#include "ui\_clients.h"

#include <QtSql>

Clients::**Clients**(QWidget \*parent) :

`    `QDialog(*parent*),

`    `ui(*new* Ui::Clients)

{

`    `ui->setupUi(*this*);

`    `setWindowTitle("Покупатели");

`    `clients = QSqlDatabase::addDatabase("QSQLITE");

`    `clients.setDatabaseName("./clientsDB.db");

`    `clients.open();

`    `query = *new* QSqlQuery(clients);

`    `query->exec("CREATE TABLE ClientsTable(ФИО TEXT, Телефон TEXT, Карта TEXT, Баллы INT);");

`    `model = *new* QSqlTableModel(*this*, clients);

`    `model->*setTable*("ClientsTable");

`    `model->*select*();

`    `QTableView \*view = ui->ClientsTable;

`    `view->*setModel*(*model*);

`    `view->setColumnWidth(0, view->width()/4);

`    `view->setColumnWidth(1, view->width()/4);

`    `view->setColumnWidth(2, view->width()/4);

`    `view->setColumnWidth(3, view->width()/4);

`    `view->setEditTriggers(QAbstractItemView::*NoEditTriggers*);

`    `view->show();

}

Clients::~***Clients***()

{

`    `*delete* ui;

}

bool Clients::**on\_addItem\_clicked**()

{

`    `newClient \*dialog = *new* newClient;

`    `*if* (dialog->*exec*() == QDialog::*Accepted*) {

`        `name = dialog->getName();

`        `phone = dialog->getPhone();

`        `card = dialog->getCard();

`        `QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

`        `db.setDatabaseName("clientsDB.db");

`        `*if* (!db.open()) {

`            `qDebug() << "Не удалось открыть базу данных";

`            `*return* *false*;

`        `}

`        `query = *new* QSqlQuery(db);

`        `query->exec("CREATE TABLE ClientsTable(ФИО TEXT, Телефон TEXT, Карта TEXT, Баллы INT);");


`        `model = *new* QSqlTableModel(*this*, db);

`        `model->*setTable*("ClientsTable");

`        `QSqlQuery query;

`        `query.prepare("INSERT INTO ClientsTable (ФИО, Телефон, Карта, Баллы) VALUES (:name, :phone, :card, :points)");

`        `query.bindValue(":name", name);

`        `query.bindValue(":phone", phone);

`        `query.bindValue(":card", card);

`        `query.bindValue(":points", 0);

`        `*if* (!query.exec()) {

`            `qDebug() << "Не удалось выполнить запрос:" << query.lastError().text();

`            `*return* *false*;

`        `}

`        `model->*select*();

`        `ui->ClientsTable->*setModel*(*model*);

`        `connect(model, &QSqlTableModel::dataChanged, ui->ClientsTable, &QTableView::reset);

`        `db.close();

`    `}

`    `*delete* dialog;

`    `*return* *true*;

}

void Clients::**on\_search\_2\_textChanged**()

{

`    `QSortFilterProxyModel\* proxyModel = *new* QSortFilterProxyModel(*ui->ClientsTable*);

`    `proxyModel->*setSourceModel*(*model*);

`    `proxyModel->setFilterCaseSensitivity(Qt::*CaseInsensitive*);

`    `proxyModel->setFilterKeyColumn(-1);

`    `proxyModel->setFilterRegExp(ui->search\_2->toPlainText());

`    `ui->ClientsTable->*setModel*(*proxyModel*);

`    `ui->ClientsTable->show();

}

void Clients::**on\_acceptBtn\_clicked**()

{

`    `QModelIndexList selectedIndexes = ui->ClientsTable->selectionModel()->selectedIndexes();

`    `*if* (!selectedIndexes.isEmpty())

`    `{

`        `QModelIndex selectedIndex = selectedIndexes.first();

`        `QModelIndex ptsIndex = selectedIndex.sibling(selectedIndex.row(), 3);

`        `QModelIndex nameIndex = selectedIndex.sibling(selectedIndex.row(), 0);

`        `QModelIndex phoneIndex = selectedIndex.sibling(selectedIndex.row(), 1);

`        `points = ptsIndex.data().toString();

`        `phone = phoneIndex.data().toString();

`        `name = nameIndex.data().toString();

`        `QDialog::accept();

`        `close();

`    `}

}

### Endshift.cpp

#include "endshift.h"

#include "ui\_endshift.h"

EndShift::**EndShift**(QWidget \*parent) :

`    `QDialog(*parent*),

`    `ui(*new* Ui::EndShift)

{

`    `ui->setupUi(*this*);

`    `ui->endShift->*setVisible*(*true*);

`    `ui->label->*setVisible*(*false*);

`    `ui->label\_2->*setVisible*(*false*);

`    `ui->label\_3->*setVisible*(*false*);

`    `ui->label\_4->*setVisible*(*false*);

`    `ui->label\_5->*setVisible*(*false*);

`    `ui->label\_6->*setVisible*(*false*);

`    `ui->label\_7->*setVisible*(*false*);

`    `ui->closeBtn->*setVisible*(*false*);

}

EndShift::~***EndShift***()

{

`    `*delete* ui;

}


void EndShift::**on\_endShift\_clicked**()

{

`    `ui->endShift->*setVisible*(*false*);

`    `ui->label->*setVisible*(*true*);

`    `ui->label\_2->*setVisible*(*true*);

`    `ui->label\_3->*setVisible*(*true*);

`    `ui->label\_4->*setVisible*(*true*);

`    `ui->label\_5->*setVisible*(*true*);

`    `ui->label\_6->*setVisible*(*true*);

`    `ui->label\_7->*setVisible*(*true*);

`    `ui->closeBtn->*setVisible*(*true*);

`    `ui->label->setText("Общая выручка за смену: " + total);

`    `ui->label\_2->setText("Наличными:  " + nal);

`    `ui->label\_3->setText("Картой: " + card);

`    `ui->label\_4->setText("Всего продаж: " + sells);

`    `ui->label\_6->setText("Смена начата: " + startTime.date().toString().mid(0, 9) +

`                         `' ' + startTime.time().toString());

`    `ui->label\_7->setText("Смена закончена: " + endTime.date().toString().mid(0, 9) +

`                         `' ' + endTime.time().toString());

}

void EndShift::**on\_closeBtn\_clicked**()

{

`    `QDialog::accept();

}

### History.cpp

#include "history.h"

#include "ui\_history.h"

#include <QDateTime>

History::**History**(QWidget \*parent) :

`    `QDialog(*parent*),

`    `ui(*new* Ui::History)

{

`    `ui->setupUi(*this*);

`    `setWindowTitle("История продаж");

`    `db = QSqlDatabase::addDatabase("QSQLITE");

`    `db.setDatabaseName("./historyDB.db");

`    `db.open();

`    `query = *new* QSqlQuery(db);

`    `query->exec("CREATE TABLE HistoryTable(Время TEXT, № TEXT, Способ TEXT, Итог DOUBLE);");

`    `model = *new* QSqlTableModel(*this*, db);

`    `model->*setTable*("HistoryTable");

`    `model->*select*();

`    `QTableView \*view = ui->HistoryTable;

`    `view->*setModel*(*model*);

`    `view->setAlternatingRowColors(*true*);

`    `view->setColumnWidth(0, view->width()/4);

`    `view->setColumnWidth(1, view->width()/4);

`    `view->setColumnWidth(2, view->width()/4);

`    `view->setColumnWidth(3, view->width()/4);

`    `view->setEditTriggers(QAbstractItemView::*NoEditTriggers*);

`    `view->show();

}

History::~***History***()

{

`    `*delete* ui;

}

### Main.cpp

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char \*argv[])

{

`    `QApplication a(*argc*, *argv*);

`    `MainWindow w;

`    `w.show();

`    `*return* a.exec();

}

### Mainwindow.cpp

#include "mainwindow.h"

#include "ui\_mainwindow.h"

#include "payment.h"

#include <QtSql>

#include <QStandardItemModel>

MainWindow::**MainWindow**(QWidget \*parent)

`    `: QMainWindow(*parent*)

`    `, ui(*new* Ui::MainWindow)

{

`    `ui->setupUi(*this*);

`    `setWindowTitle("АРМ Кассира");

`    `db = QSqlDatabase::addDatabase("QSQLITE");

`    `db.setDatabaseName("./productsDB.db");

`    `db.open();

`    `query = *new* QSqlQuery(db);

`    `query->exec("CREATE TABLE HistoryTable(Название TEXT, Стоимость DOUBLE, Количество INT);");

`    `model = *new* QSqlTableModel(*this*, db);

`    `model->*setTable*("tableView");

`    `model->*select*();

`    `QTableView \*view = ui->tableView;

`    `view->*setModel*(*model*);

`    `view->setAlternatingRowColors(*true*);

`    `view->setColumnWidth(0, view->width()/3);

`    `view->setColumnWidth(1, view->width()/3);

`    `view->setColumnWidth(2, view->width()/3);

`    `view->setEditTriggers(QAbstractItemView::*NoEditTriggers*);

`    `ui->check->horizontalHeader()->setSectionResizeMode(QHeaderView::*Stretch*);

`    `view->horizontalHeader()->setSectionResizeMode(QHeaderView::*Stretch*);

`    `view->show();

}

MainWindow::~***MainWindow***()

{

`    `*delete* ui;

}

void MainWindow::**on\_tableView\_clicked**(*const* QModelIndex &index)

{

`    `finalCost = 0;

`    `isNew=1;

`    `countInCheck = 1;

`    `int countInTable = ui->tableView->model()->*index*(index.row(), 2).data(Qt::*DisplayRole*).toInt();

`    `countInTable--;

`    `QSqlRecord record = model->record(index.row());

`    `QVariant nameValue = record.value(0);

`    `QVariant costValue = record.value(1);

`    `QString name = nameValue.toString();

`    `double cost = costValue.toDouble();

`    `*for*(int i = 0; i < elementsCount; i++)

`    `{

`        `*if*(ui->check->item(i, 0)->text() == name)

`        `{

`            `isNew = 0;

`            `countInCheck = ui->check->item(i, 2)->text().toInt()+1;

`            `costInCheck = ui->check->item(i, 1)->text().toDouble()\*countInCheck;

`            `QTableWidgetItem \*count = *new* QTableWidgetItem(QString::number(countInCheck));

`            `QTableWidgetItem \*baseCost = *new* QTableWidgetItem(QString::number(cost));

`            `QTableWidgetItem \*cost = *new* QTableWidgetItem(QString::number(costInCheck));

`            `ui->check->setItem(i, 2, *count*);

`            `ui->check->setItem(i, 1, *baseCost*);

`            `ui->check->setItem(i, 3, *cost*);

`        `}

`    `}

`    `*if*(isNew == 1)

`    `{

`        `QTableWidgetItem \*count = *new* QTableWidgetItem(QString::number(countInCheck));

`        `elementsCount+=1;

`        `ui->check->setRowCount(ui->check->rowCount() + 1);

`        `*if*(elementsCount==1)

`        `{

`            `ui->check->setColumnCount(4);

`            `ui->check->setHorizontalHeaderLabels(QStringList()<<"Название"<<"Стоимость"<<"Количество"<<"Итог");

`        `}

`        `QTableWidgetItem \*nameI= *new* QTableWidgetItem(name);

`        `QTableWidgetItem \*costI = *new* QTableWidgetItem(QString::number(cost));

`        `QTableWidgetItem \*baseCostI = *new* QTableWidgetItem(QString::number(cost));

`        `ui->check->setItem(elementsCount-1, 0, *nameI*);

`        `ui->check->setItem(elementsCount-1, 1, *baseCostI*);

`        `ui->check->setItem(elementsCount-1, 2, *count*);

`        `ui->check->setItem(elementsCount-1, 3, *costI*);

`    `}

`    `QModelIndex countIndex = ui->tableView->model()->*index*(index.row(), 2);

`    `model->*setData*(countIndex, countInTable);

`    `ui->sumText->setText(QString::number(getFinalCost()));

}

double MainWindow::**getFinalCost**()

{

`    `finalCost = 0;

`    `*for*(int i = 0; i < elementsCount; i++)

`    `{

`        `finalCost+=ui->check->item(i, 3)->text().toDouble();

`    `}

`    `*return* finalCost;

}

void MainWindow::**on\_payButton\_clicked**()

{

`    `*if*(finalCost<=0)

`        `*return*;

`    `ui->check->clear();

`    `ui->check->clearContents();

`    `ui->check->setRowCount(0);

`    `ui->check->setColumnCount(0);

`    `elementsCount = 0;

`    `ui->sumText->clear();

`    `Payment \*wnd = *new* Payment(*this*);

`    `wnd->setFinalCost(finalCost);

`    `finalCost=0;

`    `wnd->show();

`    `*if*(wnd->*exec*()==QDialog::*Accepted*)

`    `{

`        `total += wnd->getTotal();

`        `nal += wnd->getNal();

`        `card+=wnd->getCard();

`        `sells++;

`    `}

}

void MainWindow::**on\_check\_clicked**(*const* QModelIndex &index)

{

`    `int countValue = ui->check->item(index.row(), 2)->text().toInt();

`    `QTableWidgetItem \*cost = *new* QTableWidgetItem(ui->check->item(index.row(), 1)->text());

`    `QTableWidgetItem \*count = *new* QTableWidgetItem(QString::number(countValue));

`    `name = ui->check->item(index.row(), 0)->text();

`    `*if*(count->text().toInt()>1)

`    `{

`        `countValue--;

`        `count = *new* QTableWidgetItem(QString::number(countValue));

`        `ui->check->setItem(index.row(), 2, *count*);

`        `ui->check->setItem(index.row(), 3, *cost*);

`        `costInCheck = ui->check->item(index.row(), 3)->text().toDouble()\*countValue;

`        `cost->*setData*(0, costInCheck);

`    `}

`    `*else*

`    `{

`        `ui->check->removeRow(index.row());

`        `elementsCount--;

`    `}

`    `*for* (int i = 0; i < model->*rowCount*(); i++)

`    `{

`        `QVariant value = model->*data*(model->*index*(i, 0)).toString();

`        `*if* (value == name)

`        `{

`            `QModelIndex countIndex = model->*index*(i, 2);

`            `QVariant countValue = countIndex.data();

`            `int count = countValue.toInt() + 1;

`            `model->submitAll();

`            `model->*setData*(countIndex, count);

`            `model->submitAll();

`            `*break*;

`        `}

`    `}

`    `ui->sumText->setText(QString::number(getFinalCost()));

}

void MainWindow::**on\_history\_triggered**()

{

`    `History \*wnd = *new* History(*this*);

`    `wnd->show();

}

void MainWindow::**on\_clientsButton\_clicked**()

{

`    `Clients \*wnd = *new* Clients(*this*);

`    `wnd->show();

}


void MainWindow::**on\_search\_textChanged**()

{

`    `QSortFilterProxyModel\* proxyModel = *new* QSortFilterProxyModel(*ui->tableView*);

`    `proxyModel->*setSourceModel*(*model*);

`    `proxyModel->setFilterCaseSensitivity(Qt::*CaseInsensitive*);

`    `proxyModel->setFilterKeyColumn(-1);

`    `proxyModel->setFilterRegExp(ui->search->toPlainText());

`    `ui->tableView->*setModel*(*proxyModel*);

`    `ui->tableView->show();

}

bool MainWindow::**on\_addItem\_clicked**()

{

`    `newItem\* dialog = *new* newItem(*this*);

`    `*if* (dialog->*exec*() == QDialog::*Accepted*) {

`        `QString name = dialog->getName();

`        `double cost = dialog->getCost();

`        `int amount = dialog->getAmount();

`        `QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

`        `db.setDatabaseName("productsDB.db");

`        `*if* (!db.open()) {

`            `qDebug() << "Не удалось открыть базу данных";

`            `*return* *false*;

`        `}

`        `query = *new* QSqlQuery(db);

`        `query->exec("CREATE TABLE tableView(Название TEXT, "

`                    `"Стоимость DOUBLE, Количество INT);");


`        `model = *new* QSqlTableModel(*this*, db);

`        `model->*setTable*("tableView");

`        `QSqlQuery query;

`        `query.prepare("INSERT INTO tableView (Название, Стоимость, Количество) "

`                      `"VALUES (:name, :cost, :amount)");

`        `query.bindValue(":name", name);

`        `query.bindValue(":cost", cost);

`        `query.bindValue(":amount", amount);;

`        `*if* (!query.exec()) {

`            `qDebug() << "Не удалось выполнить запрос:" << query.lastError().text();

`            `*return* *false*;

`        `}

`        `model->*select*();

`        `ui->tableView->*setModel*(*model*);

`        `connect(model, &QSqlTableModel::dataChanged, ui->tableView, &QTableView::reset);

`    `}

`    `*delete* dialog;

`    `*return* *true*;

}

void MainWindow::**on\_shift\_triggered**()

{

`    `*if*(!started)

`    `{

`        `Shift \*dialog = *new* Shift;

`        `*if* (dialog->*exec*() == QDialog::*Accepted*)

`        `{

`            `startTime = QDateTime::currentDateTime();

`            `started = *true*;

`            `ui->tableView->setEnabled(*true*);

`            `ui->shiftNeeded->setMaximumSize(0, 0);

`            `total = 0;

`            `nal = 0;

`            `card = 0;

`            `sells = 0;

`        `}

`        `*delete* dialog;

`    `}

`    `*else*

`    `{

`        `EndShift \*dialog = *new* EndShift;

`        `endTime = QDateTime::currentDateTime();

`        `dialog->setEnd(endTime);

`        `dialog->setTotal(total);

`        `dialog->setNal(nal);

`        `dialog->setCard(card);

`        `dialog->setSells(sells);

`        `dialog->setStart(startTime);

`        `dialog->*exec*();

`        `*if* (dialog->*Accepted*||dialog->*Rejected*)

`        `{          

`            `ui->tableView->setEnabled(*false*);

`            `ui->shiftNeeded->setMaximumSize(999999, 21);

`            `ui->shiftNeeded->*setVisible*(*true*);

`            `started = *false*;

`            `ui->tableView->setEnabled(*false*);

`            `ui->shiftNeeded->*setVisible*(*true*);

`            `total = 0;

`            `nal = 0;

`            `card = 0;

`            `sells = 0;

`        `}

`        `*delete* dialog;

`    `}

}

### Newclient.cpp

#include "newclient.h"

#include "ui\_newclient.h"

#include <QMessageBox>

newClient::**newClient**(QWidget \*parent) :

`    `QDialog(*parent*),

`    `ui(*new* Ui::newClient)

{

`    `ui->setupUi(*this*);

}

newClient::~***newClient***()

{

`    `*delete* ui;

}

void newClient::**on\_addBtn\_clicked**()

{

`    `*if*(ui->nameL->toPlainText()==""

`            `|| ui->phoneL->toPlainText()==""

`            `|| ui->cardL->toPlainText()=="")

`    `{

`        `QMessageBox::critical(*this*, "Ошибка", "Данные введены некорректно.");

`        `*return*;

`    `}

`    `name = ui->nameL->toPlainText();

`    `phone = ui->phoneL->toPlainText();

`    `card = ui->cardL->toPlainText();

`    `QDialog::accept();

`    `close();

}

### Newitem.cpp

#include "newitem.h"

#include "ui\_newitem.h"

#include <QMessageBox>

newItem::newItem(QWidget \*parent) :

`    `QDialog(parent),

`    `ui(*new* Ui::newItem)

{

`    `ui->setupUi(*this*);

}

newItem::~newItem()

{

`    `*delete* ui;

}

void newItem::on\_addBtn\_clicked()

{

`    `*if*(ui->nameL->toPlainText()=="" || ui->costL->toPlainText().toDouble()<=0 || ui->amountL->toPlainText().toInt()<=0)

`    `{

`        `QMessageBox::critical(*this*, "Ошибка", "Данные введены некорректно.");

`        `*return*;

`    `}

`    `name = ui->nameL->toPlainText();

`    `cost = ui->costL->toPlainText().toDouble();

`    `amount = ui->amountL->toPlainText().toInt();

`    `QDialog::accept();

`    `close();

}

### Payment.cpp

#include "payment.h"

#include "ui\_payment.h"

#include "paymentdone.h"

#include "mainwindow.h"

#include <QDateTime>

#include <QSqlRecord>

#include <QDebug>

#include <QSqlError>

#include <QMessageBox>

Payment::**Payment**(QWidget \*parent) :

`    `QDialog(*parent*),

`    `ui(*new* Ui::Payment)

{

`    `ui->setupUi(*this*);

`    `setWindowTitle("Оплата");

}

Payment::~***Payment***()

{

`    `*delete* ui;

}

void Payment::**setFinalCost**(double cost)

{

`    `ui->costLabel->setText("К оплате: " + QString::number(cost));

`    `finalCost = cost;

}

void Payment::**on\_nalButton\_clicked**()

{

`    `*if* (ui->usePts->isEnabled())

`        `ptsToDB = finalCost + ui->client->toPlainText().toInt();

`    `*if*(sum<finalCost)

`    `{

`        `QMessageBox::critical(*this*, "Ошибка", "Внесенная сумма меньше суммы к оплате.");

`        `*return*;

`    `}

`    `QDateTime dt = QDateTime::currentDateTime();

`    `PaymentDone \*wnd = *new* PaymentDone(*this*);

`    `wnd->setFinalCost(finalCost);

`    `wnd->show();

`    `addToDB(dt, "Наличными", finalCost);

`    `changeInDB(ptsToDB, nameToChange, phoneToChange);

`    `total=finalCost;

`    `nal=finalCost;

`    `QDialog::accept();

`    `close();

}


void Payment::**on\_nalTB\_textChanged**()

{

`    `sum = ui->nalTB->toPlainText().toDouble();

`    `*if*(sum>finalCost)

`    `{

`        `ui->back->setText("Сдача: " + QString::number(sum-finalCost));

`    `}

}


void Payment::**on\_cardButton\_clicked**()

{

`    `*if* (ui->usePts->isEnabled())

`        `ptsToDB = finalCost + ui->client->toPlainText().toInt();

`    `QDateTime dt = QDateTime::currentDateTime();

`    `PaymentDone \*wnd = *new* PaymentDone(*this*);

`    `wnd->setFinalCost(finalCost);

`    `wnd->show();

`    `addToDB(dt, "Картой", finalCost);

`    `changeInDB(ptsToDB, nameToChange, phoneToChange);

`    `total=finalCost;

`    `card=finalCost;

`    `QDialog::accept();

`    `close();

}

bool Payment::**addToDB**(QDateTime dt, QString method, double sum)

{

`    `db = QSqlDatabase::addDatabase("QSQLITE");

`    `db.setDatabaseName("historyDB.db");

`    `*if* (!db.open()) {

`        `qDebug() << "Не удалось открыть базу данных";

`        `*return* *false*;

`    `}

`    `query = *new* QSqlQuery(db);

`    `query->exec("CREATE TABLE HistoryTable(Время TEXT, № TEXT, Способ TEXT, Итог DOUBLE);");

`    `query->prepare("SELECT COUNT(\*) FROM HistoryTable");

`    `*if* (query->exec() && query->next())

`        `elementsInDB = query->value(0).toInt();

`    `query->prepare("INSERT INTO HistoryTable (Время, №, Способ, Итог) VALUES (:time, :number, :method, :sum)");

`    `query->bindValue(":time", dt.date().toString() + ' ' + dt.time().toString());

`    `query->bindValue(":number", elementsInDB+1);

`    `query->bindValue(":method", method);

`    `query->bindValue(":sum", sum);

`    `*if* (!query->exec()) {

`        `qDebug() << "Не удалось выполнить запрос:" << query->lastError().text();

`        `*return* *false*;

`    `}

`    `db.close();

`    `*return* *true*;

}

void Payment::**changeInDB**(int points, QString name, QString phone)

{

`    `db = QSqlDatabase::addDatabase("QSQLITE");

`    `db.setDatabaseName("clientsDB.db");

`    `*if* (!db.open())

`        `qDebug() << "Не удалось открыть базу данных";

`    `query = *new* QSqlQuery(db);

`    `query->prepare("UPDATE ClientsTable SET Баллы = :points WHERE ФИО = :name AND Телефон = :phone");

`    `query->bindValue(":points", points);

`    `query->bindValue(":name", name);

`    `query->bindValue(":phone", phone);

`    `*if* (!query->exec())

`        `qDebug() << "Не удалось выполнить запрос:" << query->lastError().text();

`    `db.close();

}

bool Payment::**on\_clientsButton\_clicked**()

{

`    `Clients \*dialog = *new* Clients;

`    `dialog->show();

`    `*if* (dialog->*exec*() == QDialog::*Accepted*)

`    `{

`        `QString points = dialog->getPoints();

`        `nameToChange = dialog->getName();

`        `phoneToChange = dialog->getPhone();

`        `ui->client->setText(points);

`        `setFinalCost(finalCost);

`    `}

`    `*delete* dialog;

`    `*return* *true*;

}


void Payment::**on\_usePts\_clicked**()

{

`    `double clientBonus = ui->client->toPlainText().toInt();

`    `*if*(clientBonus>=500)

`    `{

`        `ui->usePts->setEnabled(*false*);

`        `*if* (clientBonus/100>finalCost/4)

`        `{

`            `ui->discount->setText("Скидка: " + QString::number(finalCost/4) + " руб.");

`            `ptsToDB = clientBonus - finalCost\*25 + finalCost\*0.75;

`            `finalCost\*=0.75;

`            `ui->costLabel\_2->setText("Итог с учётом скидки: " + QString::number(finalCost) + " руб.");

`        `}

`        `*else*

`        `{

`            `ui->discount->setText("Скидка: " + QString::number(clientBonus/100) + " руб.");

`            `finalCost-=clientBonus/100;

`            `ptsToDB = finalCost;

`            `ui->costLabel\_2->setText("Итог с учётом скидки: " + QString::number(finalCost) + " руб.");

`        `}

`        `sum = ui->nalTB->toPlainText().toDouble();

`        `*if*(sum>finalCost)

`        `{

`            `ui->back->setText("Сдача: " + QString::number(sum-finalCost));

`        `}

`    `}

`    `*else*

`    `{

`        `ui->label\_4->setStyleSheet("color: rgb(255, 0, 0)");

`        `ui->label\_4->setText("Недостаточно баллов");

`    `}

}

### Paymentdone.cpp

#include "paymentdone.h"

#include "ui\_paymentdone.h"

PaymentDone::PaymentDone(QWidget \*parent) :

`    `QDialog(parent),

`    `ui(*new* Ui::PaymentDone)

{

`    `ui->setupUi(*this*);

`    `setWindowTitle("Оплата");

`    `setFinalCost(finalCost);

}

PaymentDone::~PaymentDone()

{

`    `*delete* ui;

}

void PaymentDone::setFinalCost(double cost)

{

`    `ui->paidLabel->setText("Оплачено: " + QString::number(cost));

`    `finalCost = cost;

}

void PaymentDone::on\_newSell\_clicked()

{

`    `close();

`    `setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);

`    `activateWindow();

`    `db = QSqlDatabase::addDatabase("QSQLITE");

`    `db.setDatabaseName("productsDB.db");

`    `db.open();

`    `query = *new* QSqlQuery(db);

`    `model = *new* QSqlTableModel(*this*, db);

`    `model->select();

}

### Shift.cpp

#include "shift.h"

#include "ui\_shift.h"

Shift::**Shift**(QWidget \*parent) :

`    `QDialog(*parent*),

`    `ui(*new* Ui::Shift)

{

`    `ui->setupUi(*this*);

}

Shift::~***Shift***()

{

`    `*delete* ui;

}

void Shift::**on\_startShift\_clicked**()

{

`    `ui->startShift->*setVisible*(*false*);

`    `QDialog::accept();

`    `close();

}
