#ifndef COLORCOLUMNDELEGATE_H
#define COLORCOLUMNDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class ColorColumnDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ColorColumnDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COLORCOLUMNDELEGATE_H
