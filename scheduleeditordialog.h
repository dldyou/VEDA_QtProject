#ifndef SCHEDULEEDITORDIALOG_H
#define SCHEDULEEDITORDIALOG_H

#include <QDialog>

namespace Ui {
class ScheduleEditorDialog;
}

class ScheduleEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleEditorDialog(QWidget *parent = nullptr);
    ~ScheduleEditorDialog();

private slots:
    void on_btnSave_2_clicked();

    void on_btnSave_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ScheduleEditorDialog *ui;
};

#endif // SCHEDULEEDITORDIALOG_H
