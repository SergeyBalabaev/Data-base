#include "teacher.h"
#include "ui_teacher.h"
#include <QMenu>

Teacher::Teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teacher)
{
    ui->setupUi(this);

    subjects_window_ = new SubjectSelection();
    groups_window_ = new GroupSelection();
    journal_window_ = new Journal();
    debtors_window_ = new Debtors();
    debtors_journal_window_ = new DebtorsJournal();

    ui->showing_selector_->addWidget(subjects_window_);
    ui->showing_selector_->addWidget(journal_window_);
    ui->showing_selector_->addWidget(groups_window_);
    ui->showing_selector_->addWidget(debtors_window_);
    ui->showing_selector_->addWidget(debtors_journal_window_);

    ui->showing_selector_->setCurrentWidget(subjects_window_);

    // Настраиваю функционал кнопки "обучение":
    configureStudyBox();

    // connects:
    connect(groups_window_, &GroupSelection::journalRequested, this, &Teacher::openJoural);
    connect(debtors_window_, &Debtors::debtorsJournalRequested, this, &Teacher::openDebtorsJournal);
    connect(subjects_window_, &SubjectSelection::groupListRequested, this, &Teacher::openGroupSelection);
    connect(journal_window_, &Journal::goBack, this, &Teacher::closeJournal);
    connect(groups_window_, &GroupSelection::goBack, this, &Teacher::openSubjectSelecion);
    connect(subjects_window_, &SubjectSelection::subjectSelected, this, &Teacher::setWorkflow);
    connect(debtors_journal_window_, &DebtorsJournal::goBack, this, &Teacher::openDebtorsSelection);
}

Teacher::~Teacher()
{
    delete ui;
}

void Teacher::initSubjectsList()
{
    subjects_window_->fillSubjectsTable();
    debtors_window_->findContingent();
}

void Teacher::setCurrentUser(User user)
{
    current_teacher_ = user;
    subjects_window_->setCurrentUser(current_teacher_);
    debtors_window_->setCurrentUser(current_teacher_);
    ui->homepage_button->setText(current_teacher_.getFullUsername());
}

void Teacher::setSqlUnit(std::shared_ptr<SqlService> unit)
{
    this->sql_unit_ = unit;
    subjects_window_->setSqlService(unit);
}

void Teacher::setWorkflow(Subject subject)
{
    groups_window_->setCurrentSubject(subject);
    journal_window_->setCurrentSubject(subject);
}

void Teacher::openJoural(QString group)
{
    ui->showing_selector_->setCurrentWidget(journal_window_);
    journal_window_->openGroup(group);
}

void Teacher::openDebtorsJournal(Subject subject)
{
    debtors_journal_window_->openSelectedSubject(subject);
    ui->showing_selector_->setCurrentWidget(debtors_journal_window_);
}

void Teacher::openGroupSelection(QStringList groups)
{
    groups_window_->fillGroups(groups);
    ui->showing_selector_->setCurrentWidget(groups_window_);
}

void Teacher::openSubjectSelecion()
{
    subjects_window_->fillSubjectsTable();
    ui->showing_selector_->setCurrentWidget(subjects_window_);
}

void Teacher::openDebtorsSelection()
{
    ui->showing_selector_->setCurrentWidget(debtors_window_);
}

void Teacher::closeJournal()
{
    ui->showing_selector_->setCurrentWidget(groups_window_);
}

void Teacher::configureStudyBox()
{
    QMenu* menu = new QMenu(this);
    menu->addAction("Список дисциплин", [this]() {
        ui->showing_selector_->setCurrentWidget(subjects_window_); });
    menu->addAction("Должники", [this]() {
        ui->showing_selector_->setCurrentWidget(debtors_window_); });

    menu->setStyleSheet("QMenu {"
                        "   background: none repeat scroll 0 0 #008cba;"
                        "   color: white;"
                        "   border: 0 none;"
                        "};");

    ui->study_button->setMenu(menu);
}
