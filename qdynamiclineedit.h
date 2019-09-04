#ifndef QDYNAMICLINEEDIT_H
#define QDYNAMICLINEEDIT_H

#include <QObject>
#include <QLineEdit>
#include <QKeyEvent>
#include <QApplication>
#include <Qt>

class qdynamiclineedit : public QLineEdit
{
    Q_OBJECT
public:
    explicit qdynamiclineedit(QWidget *parent = 0);
    ~qdynamiclineedit();
    static int ResID;
    int getID();

public slots:

private:
    int lineID = 0;
};

#endif // QDYNAMICLINEEDIT_H
