#include <QDebug>

#include "journal.h"
#include "ui_journal.h"
#include "tables_stuff/tabledelegate.h"

Journal::Journal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Journal)
{
    ui->setupUi(this);


    // Настройка отображения журнала:
    ui->journal->setColumnCount(2);

    ui->journal->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->journal->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->journal->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->journal->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);


    ui->journal->horizontalHeader()->setVisible(false);
    ui->journal->verticalHeader()->setVisible(false);

    // Установка делегата для покраски стобца
    TableDelegate *delegate = new TableDelegate(this);
    ui->journal->setItemDelegateForColumn(1, delegate);

    // connects:
    connect(ui->go_back, &QPushButton::clicked, this, &Journal::goBack);
    connect(ui->save, &QPushButton::clicked, this, &Journal::updateDatabaseGrades);
}

Journal::~Journal()
{
    delete ui;
}

void Journal::fillMarks(QSqlQuery marks_record)
{
    int rows = 0;

    ui->current_subject->setText(QString("Текущая дисциплина: %1").arg(current_subject_.subject_name));

    ui->journal->clearContents();
    ui->journal->setRowCount(0);
    ui->journal->setColumnCount(2);

    // Заполняю таблицу с оценками
    while (marks_record.next()) {
        QString surname = marks_record.value(1).toString();
        QString name = marks_record.value(2).toString();
        QString patronymic = marks_record.value(3).toString();
        QString fullname = QStringList{surname, name, patronymic}.join(' ');
        QString mark = marks_record.value(4).toString();

        // qDebug() << fullname << " " << mark;

        ui->journal->insertRow(rows);
        ui->journal->setItem(rows, 0, new QTableWidgetItem(fullname));
        ui->journal->setItem(rows, 1, new QTableWidgetItem(mark));

        ui->journal->setRowHeight(rows, 50);

        // Связываю номер записи в таблице со студенческим билетом
        students_id_[rows] = marks_record.value(0).toInt();

        ++ rows;
    }

    ui->journal->setJournalMap(students_id_);
    configurateView();
}

void Journal::updateDatabaseGrades()
{
    // Обновление данных об оценках на сервере
    QSqlQuery update_query;
    for (int row = 0; row < ui->journal->rowCount(); row ++) {
        // QString fullname =  ui->journal->item(row, 0)->text();
        int mark = ui->journal->item(row, 1)->text().toInt();
        int student_id = students_id_[row];

        // Подготавливаю запрос sql:
        // Есть subject id, grade, student id (прямой запрос)
        update_query.prepare("UPDATE Field_comprehension "
                             "SET mark = :mark "
                             "WHERE field = :subject_id "
                             "AND student_id = :student_id");

        // Делаю бинды для конкретной оценки
        update_query.bindValue(":subject_id", current_subject_.subject_id);
        update_query.bindValue(":student_id", student_id);
        update_query.bindValue(":mark", mark);

        update_query.exec();
    }
    qDebug() << "Marks list updated!";
}

void Journal::configurateView()
{
    // FIXME: функция старая и делалась до делегатов. При желании возможно
    // заменить ее функционал обычным делегатом столбца (смотри .../tables_stuff)
    // Оцентровка
    for (int row = 0; row < ui->journal->rowCount(); row++) {
        for (int col = 0; col < ui->journal->columnCount(); col++) {
            QTableWidgetItem *item = ui->journal->item(row, col);
            if(item) {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

    // Запрет на редактирование первого столбца
    for (int row = 0; row <ui->journal->rowCount(); ++row) {
        QTableWidgetItem* item = ui->journal->item(row, 0);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}


void Journal::openGroup(QString group)
{
    QSqlQuery query;
    group_name_ = group;

    qDebug() << "Subject: " << current_subject_.subject_name;

    query.prepare("SELECT student.student_id, student.surname, student.name, student.patronymic, Field_comprehension.mark "
                  "FROM Student LEFT OUTER JOIN Field_comprehension "
                  "ON Field_comprehension.student_id = Student.student_id "
                  "LEFT OUTER JOIN field ON Field_comprehension.field = field.field_id "
                  "WHERE student.students_group_number = :group and field.field_name = :subject "
                  "ORDER BY student.surname");
    query.bindValue(":group", group_name_);
    query.bindValue(":subject", current_subject_.subject_name);
    query.exec();

    fillMarks(std::move(query));

}

void Journal::setCurrentSubject(Subject subject)
{
    this->current_subject_ = subject;
}
