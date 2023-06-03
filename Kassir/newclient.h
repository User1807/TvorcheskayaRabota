#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>

namespace Ui {
class newClient;
}

class newClient : public QDialog
{
    Q_OBJECT

public:
    explicit newClient(QWidget *parent = nullptr);
    ~newClient();
    QString getName() {return name;};
    QString getPhone() {return phone;};
    QString getCard() {return card;};

private slots:
    void on_addBtn_clicked();

private:
    Ui::newClient *ui;
    QString name;
    QString phone;
    QString card;
};

#endif // NEWCLIENT_H
