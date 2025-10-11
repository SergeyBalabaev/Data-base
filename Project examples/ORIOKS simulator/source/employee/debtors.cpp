#include <vector>

#include <QSqlQuery>
#include <QDebug>

#include "debtors.h"
#include "ui_debtors.h"

#include <tables_stuff/centeralignmentdelegate.h>
#include <tables_stuff/tableinterfacehelper.h>

Debtors::Debtors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::debtors)
{
    ui->setupUi(this);
    setDebtorTableParameters();
}

void Debtors::setDebtorTableParameters()
{
    ui->debtors_table->setColumnCount(3);

    ui->debtors_table->horizontalHeader()->setVisible(false);
    ui->debtors_table->verticalHeader()->setVisible(false);

    // Установка политики изменения размера столбцов
    ui->debtors_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->debtors_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->debtors_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->debtors_table->setShowGrid(false);

    // Делегаты для выравнивания контента
    CenterAlignmentDelegate *center_delegate = new CenterAlignmentDelegate();
    ui->debtors_table->setItemDelegateForColumn(0, center_delegate);
    ui->debtors_table->setItemDelegateForColumn(1, center_delegate);


    ui->debtors_table->setColumnWidth(0, 50);
}

void Debtors::setCurrentUser(User user)
{
    this->current_user_ = user;
}

void Debtors::fillDebtorsGroupsTable(QSqlQuery debtors_query)
{
    std::map<Subject, std::vector<QString>> journal_links;

    ui->debtors_table->clearContents();
    ui->debtors_table->setRowCount(0);

    // Получаю весь контингент должников:
    while (debtors_query.next()) {
        QString group_name = debtors_query.value(0).toString();
        QString subject = debtors_query.value(1).toString();
        QString subject_id = debtors_query.value(2).toString();
        Subject current_subject{subject, subject_id};
        journal_links[current_subject].push_back(group_name);
    }

    current_subjects_.clear();
    for (const auto& pair : journal_links)
        current_subjects_.push_back(pair.first);

    // Форматирую представление:
    for (size_t i = 0; i < current_subjects_.size(); ++i) {
        ui->debtors_table->insertRow(i);

        QString contingent;

        auto group_kit = journal_links[current_subjects_[i]];
        if (group_kit.size() != 1) {
            contingent = std::accumulate(group_kit.begin(), group_kit.end(), QString(), [](const QString& a, const QString& b) {
                return a.isEmpty() ? b : a + "," + b;
            });
        } else {
            // Один человек из группы получает индивидуальное
            // отображение в таблице:
            QSqlQuery find_debtor_student;
            find_debtor_student.prepare("SELECT debtor_students.surname "
                                        "FROM debtor_students LEFT OUTER JOIN field "
                                        "ON CAST(debtor_students.debt_subject_id AS UUID) = field.field_id "
                                        "WHERE debtor_students.group_id = :group");
            find_debtor_student.bindValue(":group", group_kit[0]);
            find_debtor_student.exec();
            find_debtor_student.next();

            contingent = find_debtor_student.value(0).toString();
        }

        QPushButton* journal_link = createOpenJournalButton();

        QWidget * button_container = new QWidget(this);
        QHBoxLayout * hlw = new QHBoxLayout;

        // hlw->SetMinimumSize(QSize(200, 200));
        hlw->addWidget(journal_link, 0, Qt::AlignCenter);
        button_container->setLayout(hlw);
        button_container->setStyleSheet("background-color: #f2dedf;");
        // button_container->setFixedSize(journal_link->size());


        connect(journal_link, &QPushButton::clicked, this, [i, this]() {
            handleDebtorsJournalRequest(i);
        });

        ui->debtors_table->setItem(i, 0, new QTableWidgetItem(current_subjects_[i].subject_name));
        ui->debtors_table->setItem(i, 1, new QTableWidgetItem(contingent));
        ui->debtors_table->setCellWidget(i, 2, button_container);

        ui->debtors_table->setRowHeight(i, 50);

    };
}

void Debtors::findContingent()
{
    QSqlQuery debtors_query;

    debtors_query.prepare("SELECT debtor_students.group_id, field.field_name, field.field_id "
                          "FROM debtor_students LEFT OUTER JOIN field "
                          "ON CAST(debtor_students.debt_subject_id AS UUID) = field.field_id "
                          "WHERE field.professor_id = :id");
    debtors_query.bindValue(":id", current_user_.getUserId());
    debtors_query.exec();

    fillDebtorsGroupsTable(std::move(debtors_query));

}

Debtors::~Debtors()
{
    delete ui;
}

void Debtors::handleDebtorsJournalRequest(int record_line)
{
    qDebug() << "Clicked! Line: " << record_line;
    Subject selected_subject = current_subjects_[record_line];
    emit debtorsJournalRequested(selected_subject);
}


