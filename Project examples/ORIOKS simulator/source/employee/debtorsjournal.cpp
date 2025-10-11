#include "debtorsjournal.h"
#include "ui_debtorsjournal.h"
#include "tables_stuff/centeralignmentdelegate.h"
#include "tables_stuff/tabledelegate.h"

DebtorsJournal::DebtorsJournal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebtorsJournal)
{
    ui->setupUi(this);
    setJournalTableParameters();

    connect(ui->go_back_button, &QPushButton::clicked, this, &DebtorsJournal::goBack);
}

DebtorsJournal::~DebtorsJournal()
{
    delete ui;
}

void DebtorsJournal::openSelectedSubject(Subject subject)
{
    QSqlQuery debtors_query;

    debtors_query.prepare("SELECT debtor_students.group_id, debtor_students.surname, debtor_students.name, debtor_students.patronymic "
                              "FROM debtor_students LEFT OUTER JOIN field "
                              "ON CAST(debtor_students.debt_subject_id AS UUID) = field.field_id "
                              "WHERE field.field_id = :id");

    debtors_query.bindValue(":id", subject.subject_id);
    debtors_query.exec();

    fillDebtorsList(std::move(debtors_query));
}

void DebtorsJournal::fillDebtorsList(QSqlQuery query)
{
    ui->journal->clearContents();
    ui->journal->setRowCount(0);

    int rows = 0;

    while (query.next()) {
        QString group = query.value(0).toString();
        QString surname = query.value(1).toString();
        QString name = query.value(2).toString();
        QString patronymic = query.value(3).toString();
        QString fullname = QStringList{surname, name, patronymic}.join(' ');

        ui->journal->insertRow(rows);

        ui->journal->setItem(rows, 0, new QTableWidgetItem(group));
        ui->journal->setItem(rows, 1, new QTableWidgetItem(fullname));
        ui->journal->setItem(rows, 2, new QTableWidgetItem("2"));

        ui->journal->setRowHeight(rows, 50);
    }
}


void DebtorsJournal::setJournalTableParameters()
{

    ui->journal->horizontalHeader()->setVisible(false);
    ui->journal->verticalHeader()->setVisible(false);

    ui->journal->setColumnCount(3);

    ui->journal->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->journal->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->journal->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->journal->setShowGrid(false);

    // Делегаты для оцентровки:
    CenterAlignmentDelegate *center_delegate = new CenterAlignmentDelegate();
    ui->journal->setItemDelegateForColumn(0, center_delegate);
    ui->journal->setItemDelegateForColumn(1, center_delegate);

    // Установка делегата для покраски стобца:
    TableDelegate *delegate = new TableDelegate(this);
    ui->journal->setItemDelegateForColumn(2, delegate);
}
