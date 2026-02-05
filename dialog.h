#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QButtonGroup>
#include <QLineEdit>

namespace Ui {
class BinarizationDialog;
}

class BinarizationDialog : public QWidget
{
    Q_OBJECT

public:
    explicit BinarizationDialog(QWidget *parent = nullptr);
    ~BinarizationDialog();

private slots:
    void onLowValueChanged(int value);
    void onHighValueChanged(int value);
    void onIncLowClicked();
    void onDecLowClicked();
    void onIncHighClicked();
    void onDecHighClicked();

private:
    Ui::BinarizationDialog *ui;

    // 按钮组
    QButtonGroup *m_groupType;
    QButtonGroup *m_groupCreate;
    QButtonGroup *m_groupDisplay1;
    QButtonGroup *m_groupDisplay2;
    QButtonGroup *m_groupDisplay3;

    // 值范围
    int m_lowValue;
    int m_highValue;
    const int m_minValue;
    const int m_maxValue;

    // 用于加载QSS样式
    void loadStyle();

    void updateLineEdit(QLineEdit *lineEdit, int value);
};

#endif // DIALOG_H