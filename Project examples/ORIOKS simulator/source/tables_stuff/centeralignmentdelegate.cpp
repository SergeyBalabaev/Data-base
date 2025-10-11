#include "centeralignmentdelegate.h"
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>
#include <QStyle>

void CenterAlignmentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem centeredOption = option;
    centeredOption.displayAlignment = Qt::AlignCenter;

    QStyledItemDelegate::paint(painter, centeredOption, index);
}
