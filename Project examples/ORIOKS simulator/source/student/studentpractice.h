#ifndef STUDENTPRACTICE_H
#define STUDENTPRACTICE_H

#include <QWidget>

namespace Ui {
class StudentPractice;
}

class StudentPractice : public QWidget
{
    Q_OBJECT

public:
    explicit StudentPractice(QWidget *parent = nullptr);
    ~StudentPractice();

private:
    Ui::StudentPractice *ui;
};

#endif // STUDENTPRACTICE_H
