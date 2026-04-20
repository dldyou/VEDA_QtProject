#include "scheduleeditordialog.h"
#include "ui_scheduleeditordialog.h"

ScheduleEditorDialog::ScheduleEditorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScheduleEditorDialog)
{
    ui->setupUi(this);
}

ScheduleEditorDialog::~ScheduleEditorDialog()
{
    delete ui;
}

void ScheduleEditorDialog::on_btnSave_clicked()
{

}


void ScheduleEditorDialog::on_btnCancel_clicked()
{

}

