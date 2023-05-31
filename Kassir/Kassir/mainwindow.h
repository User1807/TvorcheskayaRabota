#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double getFinalCost();
    QList<QString> searchTable(const QString& searchTerm);

private slots:
    //void on_tableWidget_clicked(const QModelIndex &index);

    void on_payButton_clicked();

    void on_check_clicked(const QModelIndex &index);

    void on_history_triggered();

    void on_clientsButton_clicked();

    void on_search_textChanged();

    bool on_addItem_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_shift_triggered();

private:
    Ui::MainWindow *ui;
    int elementsCount = 0;
    double finalCost = 0;
    int countInCheck = 0;
    double costInCheck = 0;
    bool isNew = 0;
    QString name;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    double total;
    double nal;
    double card;
    int sells;
    QDateTime startTime;
    QDateTime endTime;
    bool started;
};
#endif // MAINWINDOW_H
