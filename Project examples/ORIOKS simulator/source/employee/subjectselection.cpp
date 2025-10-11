#include <iostream>

#include "subjectselection.h"
#include "ui_subjectselection.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include <QDebug>

SubjectSelection::SubjectSelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubjectSelection)
{
    ui->setupUi(this);

    // Создание таблички для отображения списка дисциплин
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 50);


    ui->tableWidget->setShowGrid(false);

    // Установка политики изменения размера столбцов

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // ui->tableWidget->setHorizontalHeaderLabels({"Тип", "Название группы", "Действие"});

    // teacher_id_ = 81007;
    // initSubjects();
}

SubjectSelection::~SubjectSelection()
{
    delete ui;
}

void SubjectSelection::fillSubjectsTable()
{
    // Заполнение таблицы (sql запрос)
    // UPDATE -> предметы теперь перенесены на уровень структуры пользователя
    QSqlQuery subjects_query;
    subjects_query.prepare("SELECT field_name, field_id "
                           "FROM field "
                           "WHERE professor_id = :id");

    subjects_query.bindValue(":id", current_user_.getUserId());

    // заполнение таблицы данными
    subjects_query.exec();

    if (subjects_query.lastError().isValid()) {
        qDebug() << "Ошибка выполнения запроса:" << subjects_query.lastError().text();
    } else {
        qDebug() << "Query runned succesfully!";

        // Формирую список групп, существующих для каждой дисциплины:
        std::map<QString, vector<QString>> subject_links;
        QSqlQuery groups_query;

        while (subjects_query.next()) {

            // Заполняю список и фиксирую айди предмета:
            QString subject = subjects_query.value(0).toString();

            qDebug() << subject;

            // Возможно, стоит искать сразу по айди дисциплины:
            groups_query.prepare("select DISTINCT students_group.students_group_number "
                                 "from student LEFT OUTER JOIN students_group "
                                 "on student.students_group_number = students_group.students_group_number "
                                 "LEFT OUTER JOIN Field_comprehension "
                                 "ON Field_comprehension.student_id = student.student_id "
                                 "LEFT OUTER JOIN Field "
                                 "ON Field_comprehension.field = Field.field_id "
                                 "WHERE Field.field_name = :subject");
            groups_query.bindValue(":subject", subject);
            groups_query.exec();

            while (groups_query.next()) {
                QString group_name = groups_query.value(0).toString();
                subject_links[subject].push_back(group_name);
            }

            // Фиксирую айди предмета:
            subjects_id_[subject] = subjects_query.value(1).toString();
        }

        // Получаю полный список дисциплин:
        std::vector<QString> subjects;
        for (const auto& pair : subject_links)
            subjects.push_back(pair.first);

        // Очищаю старый список:
        // TODO: перенести в отдельную функцию
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(2);

        // Заполняю список дисциплин в интерфейсе:
        for (size_t i = 0; i < subjects.size(); ++i) {
            ui->tableWidget->insertRow(i);

            auto group_kit = subject_links[subjects[i]];
            QString groups = std::accumulate(group_kit.begin(), group_kit.end(), QString(), [](const QString& a, const QString& b) {
                return a.isEmpty() ? b : a + "," + b;
            });

            // Создаем кнопку
            QPushButton* group_list_link = new QPushButton(groups, ui->tableWidget);

            // Устанавливаем прозрачный фон для кнопки через CSS
            group_list_link->setStyleSheet("background-color: transparent; border: none; "
                                           "color: black; text-align: left;");

            connect(group_list_link, &QPushButton::clicked, this, [i, this]() {
                handleGroupListRequest(i);
            });

            qDebug() << subjects[i] << " " << groups;
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(subjects[i]));
            ui->tableWidget->setCellWidget(i , 1, group_list_link);

            qDebug() << ui->tableWidget->item(i, 0)->text();

            ui->tableWidget->setRowHeight(i, 50);
        }
    }
}

void SubjectSelection::handleGroupListRequest(int row)
{
    qDebug() << "Clicked! Row: " << row;

    QString subject_name = ui->tableWidget->item(row, 0)->text();
    QString subject_id = subjects_id_[subject_name];
    Subject current_subject{subject_name, subject_id};

    QWidget* group_cell =  ui->tableWidget->cellWidget(row, 1);
    QString group_button_text;

    // Получаю группы данной дисциплины из нажатой кнопки:
    QPushButton* group_button = qobject_cast<QPushButton*>(group_cell);
    group_button_text = group_button->text();

    QStringList groups = group_button_text.split(',');

    // Устанавливаю текущий предмет для журнала и перехожу к выбору группы:
    emit subjectSelected(current_subject);
    emit groupListRequested(groups);
}

void SubjectSelection::setCurrentUser(User user)
{
    current_user_ = user;
}


void SubjectSelection::setSqlService(std::shared_ptr<SqlService> database_unit_)
{
    this->database_unit_ = database_unit_;
}

