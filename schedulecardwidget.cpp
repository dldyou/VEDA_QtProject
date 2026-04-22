#include <QPixmap>
#include "schedulecardwidget.h"
#include "ui_schedulecardwidget.h"
#include <QGraphicsDropShadowEffect>

ScheduleCardWidget::ScheduleCardWidget(const Schedule &schedule, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleCardWidget) {
    ui->setupUi(this);

    // 데이터 세팅
    ui->lblTitle->setText(schedule.getTitle());
    ui->lblTime->setText(schedule.getStartTime().toString("MM.dd") + "-" + schedule.getEndTime().toString("MM.dd"));
    ui->lblDesc->setText(schedule.getDescription());

    // 긴 내용에 '...' 처리 (elidedText 활용)
    QFontMetrics metrics(ui->lblDesc->font());
    QString elidedText = metrics.elidedText(schedule.getDescription(), Qt::ElideRight, 300); // 300px 기준
    ui->lblDesc->setText(elidedText);

    setCategoryIcon(schedule.getCategory());

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 4);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAttribute(Qt::WA_Hover, true);
    this->setProperty("selected", false);

    id = schedule.getId();
    ui->btnDelete->hide();
    ui->btnDelete->setCursor(Qt::PointingHandCursor);
    connect(ui->btnDelete, &QPushButton::clicked, this, [this]() {
        emit deleteRequested(id);
    });
}

ScheduleCardWidget::~ScheduleCardWidget() {
    delete ui;
}

void ScheduleCardWidget::setCardSelected(bool isSelected) {
    // 위젯의 "selected" 속성값을 변경
    this->setProperty("selected", isSelected);

    // 변경된 속성을 바탕으로 QSS 스타일을 강제로 다시 계산하여 적용
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}

// 마우스가 카드 안으로 들어올 때
void ScheduleCardWidget::enterEvent(QEnterEvent *event) {
    ui->btnDelete->show(); // 버튼 나타남
    QWidget::enterEvent(event);
}

// 마우스가 카드 밖으로 나갈 때
void ScheduleCardWidget::leaveEvent(QEvent *event) {
    ui->btnDelete->hide(); // 버튼 숨김
    QWidget::leaveEvent(event);
}

// 아이콘 매핑
QMap<QString, QString> ScheduleCardWidget::iconMap = {
    {"운동", ":/icons/exercise.svg"},
    {"공부", ":/icons/study.svg"},
    {"약속", ":/icons/promise.svg"},
    {"업무", ":/icons/work.svg"},
    {"취미", ":/icons/hobby.svg"}
};

//아이콘 세팅
void ScheduleCardWidget::setCategoryIcon(const QString &category) {
    QString path = iconMap.value(category, ":/icons/default.svg");

    QPixmap pix(path);

    ui->lblCategoryIcon->setPixmap(
        pix.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );
}