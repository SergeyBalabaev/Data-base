#include <QDebug>

#include "subjectsmoderation.h"
#include "ui_subjectsmoderation.h"
#include <tables_stuff/tableinterfacehelper.h>
#include <tables_stuff/colorcolumndelegate.h>
#include <tables_stuff/centeralignmentdelegate.h>

SubjectsModeration::SubjectsModeration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubjectsModeration)
{
    ui->setupUi(this);

    configureTableParameters();

    // connects
    connect(ui->search_button, &QPushButton::clicked, this, &SubjectsModeration::searchSubjects);

}

SubjectsModeration::~SubjectsModeration()
{
    delete ui;
}

void SubjectsModeration::fillUIOptions()
{
    fillTeachers();
    fillGroups();
    fillStructuralUnits();
}

void SubjectsModeration::setCurrentUser(User user)
{
    this->current_user_ = user;
}

void SubjectsModeration::configureTableParameters()
{
    ui->subjects_table->setColumnCount(4);

    // Создание таблички для отображения списка дисциплин
    ui->subjects_table->horizontalHeader()->setVisible(false);
    ui->subjects_table->verticalHeader()->setVisible(false);

    ui->subjects_table->setShowGrid(false);

    // Делегаты
    ui->subjects_table->setItemDelegateForColumn(0, new CenterAlignmentDelegate());
    ui->subjects_table->setItemDelegateForColumn(1, new ColorColumnDelegate());
    ui->subjects_table->setItemDelegateForColumn(2, new CenterAlignmentDelegate());

    // Установка политики изменения размера столбцов
    ui->subjects_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->subjects_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->subjects_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->subjects_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

void SubjectsModeration::searchSubjects()
{
    // Поиск по выбранным параметрам с помощью фильтров
    QSqlQuery search_query;
    QString base_query_text = "SELECT Professor.surname, Field.field_name, student.students_group_number, field.field_id, Structural_unit.full_title, Professor.name, "
                              "Professor.patronymic, Student.students_group_number, Professor.professor_id, Employment.structural_unit_number "
                              "FROM field "
                              "LEFT OUTER JOIN Professor "
                              "ON field.professor_id = Professor.professor_id "
                              "LEFT OUTER JOIN Employment "
                              "ON Employment.professor_id = Professor.professor_id "
                              "LEFT OUTER JOIN Field_comprehension "
                              "ON Field_comprehension.field = field.field_id "
                              "LEFT OUTER JOIN Student "
                              "ON Field_comprehension.student_id = Student.student_id "
                              "LEFT OUTER JOIN Structural_unit "
                              "ON Field.structural_unit_id = Structural_unit.structural_unit_id "
                              "WHERE students_group_number IS NOT null ";

    QString structural_id_condition = ui->structural_box->currentText();
    QString subject_name_condition = ui->subject_name->text();
    QString teacher_id_condition = (ui->teacher_box->currentText()).split(' ')[0];
    QString group_condition = ui->group_box->currentText();

    qDebug() << structural_id_condition << subject_name_condition << teacher_id_condition << group_condition;

    // Обрабатываю институт:
    if (structural_id_condition != "Все")
        base_query_text += QString("AND structural_unit_number = %1 ").arg(structs_id_[structural_id_condition]);

    // Обрабатываю название предмета:
    if (!subject_name_condition.isEmpty())
        base_query_text += QString("AND field_name = '%1' ").arg(subject_name_condition);

    // Обрабатываю учителя
    if (teacher_id_condition != "Все")
        base_query_text += QString("AND Professor.professor_id = %1 ").arg(teacher_id_condition);

    // Обрабатываю группу
    if (group_condition != "Все")
        base_query_text += QString("AND Student.students_group_number = '%1' ").arg(group_condition);

    // Добавляю группировку и выполняю запрос:
    base_query_text += QString("GROUP BY Employment.structural_unit_number, Field.field_name, field.field_id, "
                               "Professor.surname, Professor.name, "
                               "Student.students_group_number, Structural_unit.full_title, "
                               "Professor.professor_id ");
    search_query.prepare(base_query_text);
    search_query.exec();

    fillTableAfterSearch(std::move(search_query));

}

void SubjectsModeration::fillTeachers()
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

void SubjectsModeration::fillStructuralUnits()
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

void SubjectsModeration::fillGroups()
{
    QSqlQuery groups_query;
    groups_query.prepare("SELECT students_group_number "
                         "FROM Students_group");

    groups_query.exec();
    while (groups_query.next()) {
        ui->group_box->addItem(groups_query.value(0).toString());
    }
}

void SubjectsModeration::fillTableAfterSearch([[maybe_unused]] QSqlQuery subjects_query)
{   
    subjects_.clear();
    subjects_.resize(subjects_query.size());

    ui->subjects_table->clearContents();
    ui->subjects_table->setRowCount(0);

    int rows = 0;

    while (subjects_query.next()) {
        ui->subjects_table->insertRow(rows);
        ui->subjects_table->setRowHeight(rows, 50);

        QString teacher_surname = subjects_query.value(0).toString();
        QString subject_name = subjects_query.value(1).toString();
        QString group_name = subjects_query.value(2).toString();
        QString subject_id = subjects_query.value(3).toString();

        // Создаю привязки для журнала:
        QPushButton* journal_link = createOpenJournalButton();

        QWidget * button_container = new QWidget(this);
        QHBoxLayout * hlw = new QHBoxLayout;

        // hlw->SetMinimumSize(QSize(200, 200));
        hlw->addWidget(journal_link, 0, Qt::AlignCenter);
        button_container->setLayout(hlw);

        ui->subjects_table->setItem(rows, 0, new QTableWidgetItem(teacher_surname));
        ui->subjects_table->setItem(rows, 1, new QTableWidgetItem(subject_name));
        ui->subjects_table->setItem(rows, 2, new QTableWidgetItem(group_name));
        ui->subjects_table->setCellWidget(rows, 3, button_container);

        connect(journal_link, &QPushButton::clicked, this, [rows, this]() {
            handleJournalRequest(rows);
        });

        subjects_[rows] = Subject{subject_name, subject_id};

        ++rows;
    }
}

void SubjectsModeration::handleJournalRequest(int record_line)
{
    // Запрос на журнал, перекидываю его в teacher
    qDebug() << "Clicked: " << record_line;
    QString selected_group = ui->subjects_table->item(record_line, 2)->text();

    emit subjectSelected(subjects_[record_line]);
    emit journalRequested(selected_group);
}
