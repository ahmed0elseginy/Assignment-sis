#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Assignmentsis.h"

class Assignmentsis : public QMainWindow
{
    Q_OBJECT

public:
    Assignmentsis(QWidget *parent = nullptr);
    ~Assignmentsis();

private:
    Ui::AssignmentsisClass ui;
};

