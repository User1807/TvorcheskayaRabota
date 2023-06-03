#ifndef ENDSHIFT_H
#define ENDSHIFT_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class EndShift;
}

class EndShift : public QDialog
{
    Q_OBJECT

public:
    explicit EndShift(QWidget *parent = nullptr);
    ~EndShift();
    void setTotal(double value) {total = QString::number(value);};
    void setNal(double value) {nal = QString::number(value);};
    void setCard(double value) {card = QString::number(value);};
    void setSells(int value) {sells = QString::number(value);};
    void setStart(QDateTime dt) {startTime = dt;};
    void setEnd(QDateTime dt) {endTime = dt;};

private slots:
    void on_endShift_clicked();

    void on_closeBtn_clicked();

private:
    Ui::EndShift *ui;
    QString total;
    QString nal;
    QString card;
    QString sells;
    QDateTime startTime;
    QDateTime endTime;
};

#endif // ENDSHIFT_H
