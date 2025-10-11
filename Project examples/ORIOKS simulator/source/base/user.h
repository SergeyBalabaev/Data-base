#ifndef USER_H
#define USER_H


#include <QString>
#include <vector>
#include <map>

class User
{
public:
    User();

    enum AcessLevel {
        student, teacher, methodist
    };

    AcessLevel acess_level_;

    void setFullname(QString name, QString surname, QString patronymic);
    void setUserId(int user_id);
    void setAcessLevel(AcessLevel level);

    AcessLevel getAcessLevel() {return this->acess_level_;};
    int getUserId() {return this->user_id_;};

    QString getFullUsername();

private:
    int user_id_{}; // Номер в системе (к примеру, 8200434)
    QString name_{};
    QString surname_{};
    QString patronymic_{};
    // std::map<QString, QString> user_subjects_;
};

#endif // USER_H
