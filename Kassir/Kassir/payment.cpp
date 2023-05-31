#include "payment.h"
#include "ui_payment.h"
#include "paymentdone.h"
#include "mainwindow.h"
#include <QDateTime>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

Payment::Payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    setWindowTitle("Оплата");
}

Payment::~Payment()
{
    delete ui;
}

void Payment::setFinalCost(double cost)
{
    ui->costLabel->setText("К оплате: " + QString::number(cost));
    finalCost = cost;
}

void Payment::on_nalButton_clicked()
{
    if (ui->usePts->isEnabled())
        ptsToDB = finalCost + ui->client->toPlainText().toInt();
    if(sum<finalCost)
    {
        QMessageBox::critical(this, "Ошибка", "Внесенная сумма меньше суммы к оплате.");
        return;
    }
    QDateTime dt = QDateTime::currentDateTime();
    PaymentDone *wnd = new PaymentDone(this);
    wnd->setFinalCost(finalCost);
    wnd->show();
    addToDB(dt, "Наличными", finalCost);
    changeInDB(ptsToDB, nameToChange, phoneToChange);
    total=finalCost;
    nal=finalCost;
    QDialog::accept();
    close();
}


void Payment::on_nalTB_textChanged()
{
    sum = ui->nalTB->toPlainText().toDouble();
    if(sum>finalCost)
    {
        ui->back->setText("Сдача: " + QString::number(sum-finalCost));
    }
}


void Payment::on_cardButton_clicked()
{
    if (ui->usePts->isEnabled())
        ptsToDB = finalCost + ui->client->toPlainText().toInt();
    QDateTime dt = QDateTime::currentDateTime();
    PaymentDone *wnd = new PaymentDone(this);
    wnd->setFinalCost(finalCost);
    wnd->show();
    addToDB(dt, "Картой", finalCost);
    changeInDB(ptsToDB, nameToChange, phoneToChange);
    total=finalCost;
    card=finalCost;
    QDialog::accept();
    close();
}

bool Payment::addToDB(QDateTime dt, QString method, double sum)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("historyDB.db");
    if (!db.open()) {
        qDebug() << "Не удалось открыть базу данных";
        return false;
    }
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE HistoryTable(Время TEXT, № TEXT, Способ TEXT, Итог DOUBLE);");

    query->prepare("SELECT COUNT(*) FROM HistoryTable");
    if (query->exec() && query->next())
        elementsInDB = query->value(0).toInt();
    query->prepare("INSERT INTO HistoryTable (Время, №, Способ, Итог) VALUES (:time, :number, :method, :sum)");
    query->bindValue(":time", dt.date().toString() + ' ' + dt.time().toString());
    query->bindValue(":number", elementsInDB+1);
    query->bindValue(":method", method);
    query->bindValue(":sum", sum);

    if (!query->exec()) {
        qDebug() << "Не удалось выполнить запрос:" << query->lastError().text();
        return false;
    }

    db.close();

    return true;
}

void Payment::changeInDB(int points, QString name, QString phone)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("clientsDB.db");
    if (!db.open())
        qDebug() << "Не удалось открыть базу данных";
    query = new QSqlQuery(db);
    query->prepare("UPDATE ClientsTable SET Баллы = :points WHERE ФИО = :name AND Телефон = :phone");
    query->bindValue(":points", points);
    query->bindValue(":name", name);
    query->bindValue(":phone", phone);

    if (!query->exec())
        qDebug() << "Не удалось выполнить запрос:" << query->lastError().text();

    db.close();
}

bool Payment::on_clientsButton_clicked()
{
    Clients *dialog = new Clients;
    dialog->show();
    if (dialog->exec() == QDialog::Accepted)
    {
        QString points = dialog->getPoints();
        nameToChange = dialog->getName();
        phoneToChange = dialog->getPhone();
        ui->client->setText(points);
        setFinalCost(finalCost);
    }
    delete dialog;
    return true;
}


void Payment::on_usePts_clicked()
{
    double clientBonus = ui->client->toPlainText().toInt();
    if(clientBonus>=500)
    {
        ui->usePts->setEnabled(false);
        if (clientBonus/100>finalCost/4)
        {
            ui->discount->setText("Скидка: " + QString::number(finalCost/4) + " руб.");
            ptsToDB = clientBonus - finalCost*25 + finalCost*0.75;
            finalCost*=0.75;
            ui->costLabel_2->setText("Итог с учётом скидки: " + QString::number(finalCost) + " руб.");
        }
        else
        {
            ui->discount->setText("Скидка: " + QString::number(clientBonus/100) + " руб.");
            finalCost-=clientBonus/100;
            ptsToDB = finalCost;
            ui->costLabel_2->setText("Итог с учётом скидки: " + QString::number(finalCost) + " руб.");
        }
        sum = ui->nalTB->toPlainText().toDouble();
        if(sum>finalCost)
        {
            ui->back->setText("Сдача: " + QString::number(sum-finalCost));
        }
    }
    else
    {
        ui->label_4->setStyleSheet("color: rgb(255, 0, 0)");
        ui->label_4->setText("Недостаточно баллов");
    }
}

