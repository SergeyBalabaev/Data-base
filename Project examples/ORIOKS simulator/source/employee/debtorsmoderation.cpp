#include "debtorsmoderation.h"
#include "ui_debtorsmoderation.h"

#include <tables_stuff/tableinterfacehelper.h>
#include <tables_stuff/centeralignmentdelegate.h>

#include <QDebug>

DebtorsModeration::DebtorsModeration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebtorsModeration)
{
    ui->setupUi(this);
    configureDebtorsTable();

    fillGroups();
    fillTeachers();
    fillStructuralUnits();

    //connects
    connect(ui->search_button, &QPushButton::clicked, this, &DebtorsModeration::searchDebtors);
}

DebtorsModeration::~DebtorsModeration()
{
    delete ui;
}

void DebtorsModeration::searchDebtors()
{
    QSqlQuery debtors_query;
    QString base_query_text = "select Professor.surname, Field.field_name, string_agg(DISTINCT debtor_students.group_id, ', '), "
                              "Field.field_id, Professor.professor_id, Structural_unit.structural_unit_id "
                              "from debtor_students "
                              "LEFT OUTER JOIN  Field "
                              "ON CAST(debtor_students.debt_subject_id AS UUID) = field.field_id "
                              "LEFT OUTER JOIN Structural_unit "
                              "ON Field.structural_unit_id = Structural_unit.structural_unit_id "
                              "LEFT OUTER JOIN Professor "
                              "ON field.professor_id = Professor.professor_id "
                              "WHERE 1 = 1 "; // Такая запись позволяет далее гибко добавлять условия через AND

    QString structural_id_condition = ui->structural_box->currentText();
    QString subject_name_condition = ui->subject_name->text();
    QString teacher_id_condition = (ui->teacher_box->currentText()).split(' ')[0];
    QString group_condition = ui->group_box->currentText();

    // Обрабатываю институт:
    if (structural_id_condition != "Все")
        base_query_text += QString("AND Structural_unit.structural_unit_id = %1 ").arg(structs_id_[structural_id_condition]);

    // Обрабатываю название предмета:
    if (!subject_name_condition.isEmpty())
        base_query_text += QString("AND field_name = '%1' ").arg(subject_name_condition);

    // Обрабатываю учителя
    if (teacher_id_condition != "Все")
        base_query_text += QString("AND Professor.professor_id = %1 ").arg(teacher_id_condition);

    // Обрабатываю группу
    if (group_condition != "Все")
        base_query_text += QString("AND group_id LIKE '%%%%1%%' ").arg(group_condition);

    // Добавляю группировку и выполняю запрос
    base_query_text += QString("GROUP BY Field.field_id, Professor.surname, Professor.professor_id, Structural_unit.structural_unit_id; ");
    debtors_query.prepare(base_query_text);
    debtors_query.exec();


    fillDebtorsTable(std::move(debtors_query));
}

void DebtorsModeration::fillDebtorsTable(QSqlQuery debtors_query)
{
    ui->debtors_table->clearContents();
    ui->debtors_table->setRowCount(0);

    std::map<QString, std::vector<QString>> journal_links;


    subjects_.clear();
    subjects_.resize(debtors_query.size());

    int rows = 0;

    while (debtors_query.next()) {
        ui->debtors_table->insertRow(rows);
        ui->debtors_table->setRowHeight(rows, 50);

        QString teacher_surname = debtors_query.value(0).toString();
        QString subject_name = debtors_query.value(1).toString();
        QString groups_name = debtors_query.value(2).toString();
        QString subject_id = debtors_query.value(3).toString();

        // Создаю привязки для журнала:
        QPushButton* journal_link = createOpenJournalButton();

        QWidget * button_container = new QWidget(this);
        QHBoxLayout * hlw = new QHBoxLayout;

        // hlw->SetMinimumSize(QSize(200, 200));
        hlw->addWidget(journal_link, 0, Qt::AlignCenter);
        button_container->setLayout(hlw);

        ui->debtors_table->setItem(rows, 0, new QTableWidgetItem(teacher_surname));
        ui->debtors_table->setItem(rows, 1, new QTableWidgetItem(subject_name));
        ui->debtors_table->setItem(rows, 2, new QTableWidgetItem(groups_name));
        ui->debtors_table->setCellWidget(rows, 3, button_container);

        connect(journal_link, &QPushButton::clicked, this, [rows, this]() {
            handleDebtorsJournalRequest(rows);
        });

        subjects_[rows] = Subject{subject_name, subject_id};

        ++rows;

    }
}

void DebtorsModeration::fillTeachers()
{
    QSqlQuery teachers_query;
    teachers_query.prepare("SELECT professor_id, surname, name, patronymic "
                           "FROM Professor");
    teachers_query.exec();

    QStringList query_info;

    while (teachers_query.next()) {
        for (int i = 0; i < 4; ++i) {
            query_info << teachers_query.value(i).toString();
        }
        ui->teacher_box->addItem(query_info.join(' '));
        query_info.clear();
    }
}

void DebtorsModeration::fillStructuralUnits()
{
    QSqlQuery structurals_query;
    structurals_query.prepare("SELECT full_title, structural_unit_id "
                              "FROM Structural_unit");

    structurals_query.exec();
    while (structurals_query.next()) {
        QString title = structurals_query.value(0).toString();
        int id = structurals_query.value(1).toInt();
        ui->structural_box->addItem(title);
        structs_id_[title] = id;
    }
}

void DebtorsModeration::fillGroups()
{
    QSqlQuery groups_query;
    groups_query.prepare("SELECT students_group_number "
                         "FROM Students_group");

    groups_query.exec();
    while (groups_query.next()) {
        ui->group_box->addItem(groups_query.value(0).toString());
    }
}

void DebtorsModeration::configureDebtorsTable()
{
    ui->debtors_table->setColumnCount(4);

    // Создание таблички для отображения списка дисциплин
    ui->debtors_table->horizontalHeader()->setVisible(false);
    ui->debtors_table->verticalHeader()->setVisible(false);

    ui->debtors_table->setShowGrid(false);

    // Установка политики изменения размера столбцов
    ui->debtors_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->debtors_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->debtors_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->debtors_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    // Установка делегатов
    ui->debtors_table->setItemDelegateForColumn(0, new CenterAlignmentDelegate());
    ui->debtors_table->setItemDelegateForColumn(1, new CenterAlignmentDelegate());
    ui->debtors_table->setItemDelegateForColumn(2, new CenterAlignmentDelegate());


}

void DebtorsModeration::handleDebtorsJournalRequest(int record_line)
{
    // TODO
    qDebug() << "Clicked! Line: " << record_line;
    emit debtorsJournalRequested(subjects_[record_line]);
}
