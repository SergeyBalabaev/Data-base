#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>

struct Subject {
    QString subject_name;
    QString subject_id;

    // Для того чтобы использовать предмет в качестве ключа словаря
    // необходимо определить оператор меньше (ключи в словаре сортируются):
    bool operator< (const Subject& other) const {
        if (subject_id < other.subject_id)
            return true;
        return false;
    }
};

#endif // SUBJECT_H
