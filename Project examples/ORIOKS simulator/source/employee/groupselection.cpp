#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include "groupselection.h"
#include "ui_groupselection.h"
#include <QSqlQuery>
#include "tables_stuff/centeralignmentdelegate.h"
#include "tables_stuff/tableinterfacehelper.h"

GroupSelection::GroupSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupSelection)
{
    ui->setupUi(this);

    ui->groups_table->horizontalHeader()->setVisible(false);
    ui->groups_table->verticalHeader()->setVisible(false);

    ui->groups_table->setColumnCount(2);
    // ui->groups_table->setColumnWidth(0, 50);
    CenterAlignmentDelegate *center_delegate = new CenterAlignmentDelegate();
    ui->groups_table->setItemDelegateForColumn(0, center_delegate);


    ui->groups_table->setShowGrid(true);

    // Установка политики изменения размера столбцов
    ui->groups_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->groups_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // connects:
    connect(ui->back_to_subjects, &QPushButton::clicked, this, &GroupSelection::goBack);
}

GroupSelection::~GroupSelection()
{
    delete ui;
}

void GroupSelection::fillGroups(QStringList groups)
{
    QString group_name;

    ui->groups_table->clearContents();
    ui->groups_table->setRowCount(0);

    ui->groups_table->insertRow(0);
    ui->groups_table->setSpan(0, 0, 1, 2); // Объединяем ячейку спра
    //ui->groups_table->setItem(0, 0, new QTableWidgetItem(subject));

    QLabel* label = new QLabel(current_subject_.subject_name);
    label->setStyleSheet("background-color: #ebf4f9; color: black;"); // Задаем стили для виджета (в данном случае QLabel)
    label->setAlignment(Qt::AlignCenter);
    ui->groups_table->setCellWidget(0, 0, label);

    int rows = 1;

    for (auto &group: groups) {
        group_name = group;

        // Создаю привязки для журнала:
        QPushButton* journal_link = createOpenJournalButton();

        QWidget * button_container = new QWidget(this);
        QHBoxLayout * hlw = new QHBoxLayout;

        // hlw->SetMinimumSize(QSize(200, 200));
        hlw->addWidget(journal_link, 0, Qt::AlignCenter);
        button_container->setLayout(hlw);
        // button_container->setFixedSize(journal_link->size());


        connect(journal_link, &QPushButton::clicked, this, [rows, this]() {
            handleJournalRequest(rows);
        });

        ui->groups_table->insertRow(rows);
        ui->groups_table->setItem(rows, 0 , new QTableWidgetItem(group_name));
        ui->groups_table->setCellWidget(rows, 1, button_container);

        ui->groups_table->setRowHeight(rows, 50);

        ++ rows;

        qDebug() << group_name;
    }
}

void GroupSelection::setCurrentSubject(Subject subject)
{
    this->current_subject_ = subject;
}

void GroupSelection::handleJournalRequest(int record_line)
{
    // Запрос на журнал, перекидываю его в teacher
    qDebug() << "Clicked: " << record_line;
    QString selected_group = ui->groups_table->item(record_line, 0)->text();
    emit journalRequested(selected_group);
}


