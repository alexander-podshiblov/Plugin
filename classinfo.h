#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <QList>
#include <string>

class ClassInfo
{
    struct Data
    {
        QString access;
        QString type;
        QString name;
    };

    struct Methods
    {
        QString access;
        QString type;
        QString name;
        QList<Data> parameters;
    };

public:
    ClassInfo();
    QString name;
    QList<Data> data;
    QList<Methods> methods;

    QList<QString> parents;
};

#endif // CLASSINFO_H
