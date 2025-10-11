#include "colorcolumndelegate.h"

#include "colorcolumndelegate.h"

ColorColumnDelegate::ColorColumnDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ColorColumnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    int targetColumn = 1;
    if (index.column() == targetColumn) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0xebf4f9));
        painter->drawRect(option.rect);

        QStyleOptionViewItem centeredOption = option;
        centeredOption.displayAlignment = Qt::AlignCenter;

        QStyledItemDelegate::paint(painter, centeredOption, index);
        painter->restore();
    }
}
