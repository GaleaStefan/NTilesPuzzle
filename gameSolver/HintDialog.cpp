#include "HintDialog.h"
#include "ui_HintDialog.h"
#include "PuzzleSolver.h"

HintDialog::HintDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::HintDialog)
{
    m_hintMessages  = std::vector<QString> {
        "Move the ",
        "The one and only one",
        "Two be or not two be, this is the question"
    };

    ui->setupUi(this);
}



HintDialog::~HintDialog()
{
    delete ui;
}

void HintDialog::getHint(const PuzzleState& state) const
{
    PuzzleSolver solver(state);
    solver.solvePuzzle();

    unsigned hintTile = state.getTile(solver.getFirstMovedTile());

    ui->hintText->setText((hintTile > m_hintMessages.size() ? m_hintMessages[0] + QString::number((int)hintTile) : m_hintMessages[hintTile]));
}
