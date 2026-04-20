#ifndef SCHEDULEEDITORDIALOG_H
#define SCHEDULEEDITORDIALOG_H
#include "schedule.h"
#include <QDialog>

namespace Ui {
class ScheduleEditorDialog;
}

class ScheduleEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleEditorDialog(QWidget *parent = nullptr);

    void setDate(const QDate &date);

    ~ScheduleEditorDialog();

private slots:
    void on_btnSave_clicked();

    void on_btnCancel_clicked();

signals:
    void scheduleSaved(const Schedule &schedule);

private:
    Ui::ScheduleEditorDialog *ui;
};

#endif // SCHEDULEEDITORDIALOG_H
