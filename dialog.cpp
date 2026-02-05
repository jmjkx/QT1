#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QApplication>
#include <QIntValidator>

BinarizationDialog::BinarizationDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BinarizationDialog),
    m_lowValue(100),
    m_highValue(200)
{
    ui->setupUi(this);

    // 设置数值输入限制
    QIntValidator *validator = new QIntValidator(m_minValue, m_maxValue, this);
    ui->lineLow->setValidator(validator);
    ui->lineHigh->setValidator(validator);

    // 连接按钮信号
    connect(ui->btnIncLow, &QPushButton::clicked, this, &BinarizationDialog::onIncLowClicked);
    connect(ui->btnDecLow, &QPushButton::clicked, this, &BinarizationDialog::onDecLowClicked);
    connect(ui->btnIncHigh, &QPushButton::clicked, this, &BinarizationDialog::onIncHighClicked);
    connect(ui->btnDecHigh, &QPushButton::clicked, this, &BinarizationDialog::onDecHighClicked);

    // 连接输入框信号
    connect(ui->lineLow, &QLineEdit::textChanged, this, [this](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok && value >= m_minValue && value <= m_maxValue) {
            m_lowValue = value;
        }
    });
    connect(ui->lineHigh, &QLineEdit::textChanged, this, [this](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok && value >= m_minValue && value <= m_maxValue) {
            m_highValue = value;
        }
    });

    // 创建按钮组，确保互斥
    m_groupType = new QButtonGroup(this);
    m_groupType->addButton(ui->radioGraphic, 0);
    m_groupType->addButton(ui->radioImage, 1);

    m_groupCreate = new QButtonGroup(this);
    m_groupCreate->addButton(ui->radioDraw, 0);
    m_groupCreate->addButton(ui->radioInherit, 1);

    // 显示选项按钮组 - 每个按钮独立，互不干扰
    m_groupDisplay1 = new QButtonGroup(this);
    m_groupDisplay1->addButton(ui->ck1);
    m_groupDisplay1->setExclusive(false);

    m_groupDisplay2 = new QButtonGroup(this);
    m_groupDisplay2->addButton(ui->ck2);
    m_groupDisplay2->setExclusive(false);

    m_groupDisplay3 = new QButtonGroup(this);
    m_groupDisplay3->addButton(ui->ck3);
    m_groupDisplay3->setExclusive(false);

    // 确保默认选中
    ui->radioGraphic->setChecked(true);
    ui->radioDraw->setChecked(true);

    loadStyle();
}

BinarizationDialog::~BinarizationDialog()
{
    delete ui;
}

void BinarizationDialog::onIncLowClicked()
{
    if (m_lowValue < m_maxValue) {
        m_lowValue++;
        updateLineEdit(ui->lineLow, m_lowValue);
    }
}

void BinarizationDialog::onDecLowClicked()
{
    if (m_lowValue > m_minValue) {
        m_lowValue--;
        updateLineEdit(ui->lineLow, m_lowValue);
    }
}

void BinarizationDialog::onIncHighClicked()
{
    if (m_highValue < m_maxValue) {
        m_highValue++;
        updateLineEdit(ui->lineHigh, m_highValue);
    }
}

void BinarizationDialog::onDecHighClicked()
{
    if (m_highValue > m_minValue) {
        m_highValue--;
        updateLineEdit(ui->lineHigh, m_highValue);
    }
}

void BinarizationDialog::updateLineEdit(QLineEdit *lineEdit, int value)
{
    lineEdit->setText(QString::number(value));
}

void BinarizationDialog::onLowValueChanged(int value)
{
    Q_UNUSED(value);
}

void BinarizationDialog::onHighValueChanged(int value)
{
    Q_UNUSED(value);
}

void BinarizationDialog::loadStyle()
{
    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        this->setStyleSheet(qss);
        file.close();
    }
}