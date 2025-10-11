#include "tabledelegate.h"
#include <QPainter>
#include <QBrush>

TableDelegate::TableDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);

    QVariant data = index.data(Qt::DisplayRole);
    if (data.isValid()) {
        int grade = data.toInt();
        QColor bgColor;
        switch (grade) {
            case 2:
                bgColor = QColor(Qt::red);
                break;
            case 3:
                bgColor = QColor(0xf1c40f);
                break;
            case 4:
                bgColor = QColor(0x99cc33);
                break;
            case 5:
                bgColor = QColor(0x29cf00);
                break;
            default:
                bgColor = QColor(Qt::white);
        }
        painter->fillRect(option.rect, QBrush(bgColor));

        // Цвет текста всегда в черный
        painter->setPen(QColor(Qt::black));

        // Текст в центре ячейки
        QRect textRect = option.rect;
        painter->drawText(textRect, Qt::AlignCenter, data.toString());
    }


}

