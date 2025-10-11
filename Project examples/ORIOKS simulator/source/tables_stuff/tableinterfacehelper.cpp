#include "tableinterfacehelper.h"

QPushButton *createOpenJournalButton()
{
    QPushButton* open_journal_btn = new QPushButton("Журнал");
    QString style = ("QPushButton {"
                     "text-align: center;"
                     "color: white;"
                     "background: none repeat scroll 0 0 #3db066;"
                     "border: 0 none;"
                     "border-radius: 20px;"
                     "};");
    open_journal_btn->setStyleSheet(style);
    open_journal_btn->setFixedWidth(100);
    open_journal_btn->setFixedHeight(30);
    // open_journal_btn->setAlignment(Qt::AlignCenter); // Выравниваем текст по центру
    return open_journal_btn;
}

QLabel *createMarkBorder(int grade)
{
    QLabel* mark_label = new QLabel;
    QString fill_color;
    QString style = ("QLabel {"
                         "text-align: center;"
                         "padding: 2px;"
                         "color: #fff;"
                         "border-radius: 3px;"
                         "width: 40px;"
                         "background: %1;"
                     "}");
    switch (grade) {
        case 2:
            fill_color = "red";
            break;
        case 3:
            fill_color = "#f1c40f";
            break;
        case 4:
            fill_color = "#99cc33 !important";
            break;
        case 5:
            fill_color = "#29cf00";
            break;
        default:
            fill_color = "red";

    }
    mark_label->setStyleSheet(style.arg(fill_color));
    mark_label->setText(QString::number(grade));
    mark_label->setFixedSize(44, 24); // 22.56
    mark_label->setAlignment(Qt::AlignCenter);

    // mark_label->setMinimumHeight(50);

    return mark_label;
}
