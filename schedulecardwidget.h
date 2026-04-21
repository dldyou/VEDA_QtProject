#ifndef SCHEDULECARDWIDGET_H
#define SCHEDULECARDWIDGET_H

#include <QWidget>
#include <QStyle>
#include <QEnterEvent>
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

signals:
    void deleteRequested(QString id);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    Ui::ScheduleCardWidget *ui;
    QString id;
};

#endif // SCHEDULECARDWIDGET_H
