#ifndef SCHEDULECARDWIDGET_H
#define SCHEDULECARDWIDGET_H

#include <QWidget>
#include <QStyle>
#include "schedule.h"

namespace Ui {
class ScheduleCardWidget;
}

class ScheduleCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleCardWidget(const Schedule &schedule, QWidget *parent = nullptr);
    ~ScheduleCardWidget();

    void setCardSelected(bool isSelected);

private:
    Ui::ScheduleCardWidget *ui;
};

#endif // SCHEDULECARDWIDGET_H
