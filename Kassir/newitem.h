#ifndef NEWITEM_H
#define NEWITEM_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class newItem;
}

class newItem : public QDialog
{
    Q_OBJECT

public:
    explicit newItem(QWidget *parent = nullptr);
    ~newItem();
    QString getName() {return name;};
    double getCost() {return cost;};
    int getAmount() {return amount;};

private slots:

    void on_addBtn_clicked();

private:
    Ui::newItem *ui;
    QString name;
    double cost;
    int amount;
};

#endif // NEWITEM_H
