#include "qdynamiclineedit.h"

qdynamiclineedit::qdynamiclineedit(QWidget *parent) :
    QLineEdit (parent)
{
    ResID++;
    lineID = ResID;
}

qdynamiclineedit::~qdynamiclineedit(){}

int qdynamiclineedit::getID(){
    return lineID;
}

int qdynamiclineedit::ResID = 0;
