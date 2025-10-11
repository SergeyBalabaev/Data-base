QT       += core gui
QT += sql
QT += core
LIBS += -L/usr/lib/x86_64-linux-gnu/qt5/plugins/sqldrivers -lqsqlpsql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_LFLAGS += -Wl,-rpath,/usr/lib/x86_64-linux-gnu

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    employee/debtorsmoderation.cpp \
    employee/subjectsmoderation.cpp \
    employee/teachersmoderation.cpp \
    tables_stuff/centeralignmentdelegate.cpp \
    employee/debtors.cpp \
    employee/debtorsjournal.cpp \
    student/diary.cpp \
    employee/groupselection.cpp \
    base/homepage.cpp \
    employee/journal.cpp \
    login/loginform.cpp \
    base/main.cpp \
    base/mainwindow.cpp \
    employee/methodist.cpp \
    tables_stuff/colorcolumndelegate.cpp \
    tables_stuff/journaltablewidget.cpp \
    tables_stuff/nonclickabletablewidget.cpp \
    sql_service/sqlservice.cpp \
    student/student.cpp \
    student/studentpractice.cpp \
    employee/subjectselection.cpp \
    tables_stuff/tabledelegate.cpp \
    tables_stuff/tableinterfacehelper.cpp \
    employee/teacher.cpp \
    base/user.cpp

HEADERS += \
    base/subject.h \
    employee/debtorsmoderation.h \
    employee/subjectsmoderation.h \
    employee/teachersmoderation.h \
    tables_stuff/centeralignmentdelegate.h \
    employee/debtors.h \
    employee/debtorsjournal.h \
    student/diary.h \
    employee/groupselection.h \
    base/homepage.h \
    employee/journal.h \
    login/loginform.h \
    base/mainwindow.h \
    employee/methodist.h \
    tables_stuff/colorcolumndelegate.h \
    tables_stuff/journaltablewidget.h \
    tables_stuff/nonclickabletablewidget.h \
    sql_service/sqlservice.h \
    student/student.h \
    student/studentpractice.h \
    employee/subjectselection.h \
    tables_stuff/tabledelegate.h \
    tables_stuff/tableinterfacehelper.h \
    employee/teacher.h \
    sql_service/configuratedatabase.h \
    base/user.h

FORMS += \
    employee/debtors.ui \
    employee/debtorsjournal.ui \
    employee/debtorsmoderation.ui \
    employee/subjectsmoderation.ui \
    employee/teachersmoderation.ui \
    student/diary.ui \
    employee/groupselection.ui \
    base/homepage.ui \
    employee/journal.ui \
    login/loginform.ui \
    base/mainwindow.ui \
    employee/methodist.ui \
    student/student.ui \
    student/studentpractice.ui \
    employee/subjectselection.ui \
    employee/teacher.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
