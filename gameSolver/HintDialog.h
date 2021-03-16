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
    explicit HintDialog(const PuzzleState& state, QWidget *parent = nullptr);
    ~HintDialog();

    void getHint() const;

private:
    Ui::HintDialog*         ui;
    std::vector<QString>    m_hintMessages;
    PuzzleState             m_state;
};

#endif // HINTDIALOG_H
