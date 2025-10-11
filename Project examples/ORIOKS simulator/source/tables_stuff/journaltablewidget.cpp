#include <QToolTip>
#include "journaltablewidget.h"
#include "qevent.h"

JournalTableWidget::JournalTableWidget(QWidget *parent) : QTableWidget(parent) {
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(500); // 2000 milliseconds = 2 seconds

    connect(timer, &QTimer::timeout, [this](){
        QTableWidgetItem *item = itemAt(lastPosition);
        if(item) {
            int row = item->row();
            // замените map на ваш std::map
            int studentId = journal_[row];
            QToolTip::showText(QCursor::pos(), QString::number(studentId));
        }
    });
}

JournalTableWidget::~JournalTableWidget() {
    delete timer;
}

void JournalTableWidget::setJournalMap(std::map<int, int> journal)
{
    journal_ = journal;
}

void JournalTableWidget::mouseMoveEvent(QMouseEvent *event) {
    timer->start();
    lastPosition = event->pos();
    QTableWidget::mouseMoveEvent(event);
}

void JournalTableWidget::leaveEvent(QEvent *event) {
    timer->stop();
    QToolTip::hideText();
    QTableWidget::leaveEvent(event);
}

bool JournalTableWidget::viewportEvent(QEvent *event) {
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);

        QPoint pos = helpEvent->pos();
        QTableWidgetItem *item = itemAt(pos);

        if (item) {
            int row = item->row();
            // замените map на ваш std::map
            int studentId = journal_[row];
            QToolTip::showText(helpEvent->globalPos(), QString::number(studentId));
        } else {
            QToolTip::hideText();
            event->ignore();
        }

        return true;
    }
    return QTableWidget::viewportEvent(event);
}
