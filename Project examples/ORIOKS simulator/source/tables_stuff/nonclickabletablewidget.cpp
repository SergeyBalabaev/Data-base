#include "nonclickabletablewidget.h"
#include <QMouseEvent>
#include <QStyleOptionFocusRect>

NonClickableTableWidget::NonClickableTableWidget(QWidget* parent) : QTableWidget(parent) {}

void NonClickableTableWidget::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    clearSelection(); // Очищаем выделение ячейки
}

bool NonClickableTableWidget::event(QEvent* event)
{
    if (event->type() == QEvent::FocusIn || event->type() == QEvent::FocusOut) {
        // Если событие - получение или потеря фокуса, сразу же снимаем фокус с ячейки
        clearFocus();
        return true;
    }

    return QTableWidget::event(event);
}

