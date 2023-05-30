#ifndef SHIFT_H
#define SHIFT_H

#include <QDialog>

namespace Ui {
class Shift;
}

class Shift : public QDialog
{
    Q_OBJECT

public:
    explicit Shift(QWidget *parent = nullptr);
    ~Shift();

private slots:
    void on_startShift_clicked();

private:
    Ui::Shift *ui;
};

#endif // SHIFT_H
