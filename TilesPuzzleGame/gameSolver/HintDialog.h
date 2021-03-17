#ifndef HINTDIALOG_H
#define HINTDIALOG_H

#include <QDialog>

#include <vector>

#include "gameLogic/PuzzleState.h"

namespace Ui {
class HintDialog;
}

class HintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HintDialog(QWidget *parent = nullptr);
    ~HintDialog();

    void getHint(const PuzzleState& state) const;

private:
    Ui::HintDialog*         ui;
    std::vector<QString>    m_hintMessages;
};

#endif // HINTDIALOG_H
