#ifndef CENTERALIGNMENTDELEGATE_H
#define CENTERALIGNMENTDELEGATE_H

#include <QStyledItemDelegate>

class CenterAlignmentDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CENTERALIGNMENTDELEGATE_H
