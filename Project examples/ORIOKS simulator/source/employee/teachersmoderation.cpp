#include <QSqlQuery>
#include <QString>
#include <QDebug>

#include "qsqlerror.h"
#include "teachersmoderation.h"
#include "ui_teachersmoderation.h"

TeachersModeration::TeachersModeration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeachersModeration)
{
    ui->setupUi(this);

    fillTeachers();

    // connects
    connect(ui->search_button, &QPushButton::clicked, this, &TeachersModeration::searchByDiscipline);
    connect(ui->save_button, &QPushButton::clicked, this, &TeachersModeration::save);

    ui->current_teacher->setReadOnly(true);

}

TeachersModeration::~TeachersModeration()
{
    delete ui;
}

void TeachersModeration::fillTeachers()
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
        ui->new_teacher_box->addItem(query_info.join(' '));
        query_info.clear();
    }
}

void TeachersModeration::updateFieldTable()
{
    QSqlQuery update_query;
    update_query.prepare("UPDATE Field "
                         "SET professor_id = :teacher_id "
                         "WHERE Field.field_id = :subject_id");

    // Получаю айди нового преподавателя
    int new_teacher_id = (ui->new_teacher_box->currentText()).split(' ')[0].toInt();

    update_query.bindValue(":teacher_id", new_teacher_id);
    update_query.bindValue(":subject_id", current_subject_.subject_id);
    update_query.exec();

    qDebug() << update_query.lastError();
    // qDebug() << "Fields table updated! New teacher id: " << new_teacher_id;
}

void TeachersModeration::updateEmploymentTable()
{
    QSqlQuery update_query;
    update_query.prepare("UPDATE Employment "
                         "SET structural_unit_number = ( "
                         "SELECT structural_unit_id FROM Field "
                         "WHERE professor_id = :teacher_id) "
                         "WHERE professor_id = :teacher_id ");
    update_query.bindValue(":teacher_id", current_teacher_id_);
    update_query.exec();

    // Обновляем позицию текущего преподавателя
    // searchByDiscipline();
    qDebug() << update_query.lastError();
    qDebug() << "Employment table updated!";
}

void TeachersModeration::searchByDiscipline()
{
    QSqlQuery search_query;
    search_query.prepare("select Professor.professor_id, Professor.surname, Professor.name, Professor.patronymic, field_id "
                         "from Field "
                         "left outer join Professor "
                         "on field.professor_id = Professor.professor_id "
                         "WHERE field.field_name = :name");
    search_query.bindValue(":name", ui->subject_line->text());
    search_query.exec();

    // Получаю результат запроса и формирую ФИО препода вместе с его id:
    QStringList teacher_info;

    if (search_query.size() != 0) {
        search_query.next();
        for (int i = 0; i < 4; ++i) {
            teacher_info << search_query.value(i).toString();
        }

        ui->current_teacher->setText(teacher_info.join(' '));

        QString subject_id = search_query.value(4).toString();

        current_subject_ = Subject{ui->subject_line->text(), subject_id};
        current_teacher_id_ = teacher_info[0].toInt();
    }

}

void TeachersModeration::save()
{
    updateFieldTable();
    updateEmploymentTable();
}
