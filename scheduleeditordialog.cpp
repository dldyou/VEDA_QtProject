#include "scheduleeditordialog.h"
#include "ui_scheduleeditordialog.h"
#include "schedule.h"

#include <QDateTime>

ScheduleEditorDialog::ScheduleEditorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScheduleEditorDialog) {
    ui->setupUi(this);

    QDateTime now = QDateTime::currentDateTime();

    //기본 인덱스 값
    ui->cbCategory->setCurrentIndex(-1);

    // 기본값 현재 날짜
    ui->deStart->setDate(now.date());
    ui->deEnd->setDate(now.date());

    // 기본값 현재 시간
    ui->deStart->setTime(now.time());
    ui->deEnd->setTime(now.time().addSecs(3600));
}

ScheduleEditorDialog::~ScheduleEditorDialog() {
    delete ui;
}

void ScheduleEditorDialog::on_btnSave_clicked() {
    QString title = ui->leTitle->text();
    QString content = ui->teContent->toPlainText();

    QString category = ui->cbCategory->currentText();     // 콤보박스
    QString categoryDetail = ui->leCategoryDetail->text(); // 옆 lineEdit

    QDateTime startDateTime = ui->deStart->dateTime();
    QDateTime endDateTime = ui->deEnd->dateTime();

    if (title.isEmpty()) {
        QMessageBox::warning(this, "경고", "제목을 입력하세요.");
        return;
    }

    if (ui->cbCategory->currentIndex() < 0) {
        QMessageBox::warning(this, "경고", "카테고리를 선택해주세요.");
        return;
    }

    if (startDateTime > endDateTime) {
        QMessageBox::warning(this, "경고", "종료 시간이 시작 시간보다 빠릅니다.");
        return;
    }

    Schedule scheduleData(
        title, 
        content, 
        startDateTime, 
        endDateTime,  
        category, 
        categoryDetail
    );

    schedule.setData(scheduleData);
    emit scheduleSaved(schedule);
    accept();
}

void ScheduleEditorDialog::setDate(const QDate &date) {
    ui->deStart->setDate(date);
    ui->deEnd->setDate(date);
}

void ScheduleEditorDialog::setSchedule(const Schedule &schedule) {
    this->schedule = schedule;
    ui->leTitle->setText(schedule.getTitle());
    ui->teContent->setText(schedule.getDescription());

    ui->deStart->setDateTime(schedule.getStartTime());
    ui->deEnd->setDateTime(schedule.getEndTime());

    ui->cbCategory->setCurrentText(schedule.getCategory());
    ui->leCategoryDetail->setText(schedule.getCategoryDetail());
}
void ScheduleEditorDialog::on_btnCancel_clicked() {
    reject();  // 그냥 창 닫기
}

