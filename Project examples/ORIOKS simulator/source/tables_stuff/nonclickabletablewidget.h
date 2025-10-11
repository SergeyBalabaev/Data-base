#ifndef NONCLICKABLETABLEWIDGET_H
#define NONCLICKABLETABLEWIDGET_H

#include <QTableWidget>

class NonClickableTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit NonClickableTableWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    bool event(QEvent* event) override;
};

#endif // NONCLICKABLETABLEWIDGET_H
