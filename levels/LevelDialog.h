#ifndef LEVELDIALOG_H
#define LEVELDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class LevelDialog;
}

class LevelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelDialog(QWidget *parent = nullptr);
    ~LevelDialog();

private:
    Ui::LevelDialog *ui;
    QMap<QPushButton*, int> m_btnLevels;
    QPushButton* m_currentLevel;

private slots:
    void onLevelButtonPress();
    void onStartButtonPress();

private:
    bool isSaveNameValid(const QString&);
};

#endif // LEVELDIALOG_H
