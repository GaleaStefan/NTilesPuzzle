#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class GameLoader;
}

class GameLoader : public QDialog
{
    Q_OBJECT

public:
    explicit GameLoader(QWidget *parent = nullptr);
    ~GameLoader();

signals:
    void saveChosenSignal(const QString& saveName) const;

private slots:
    void onSelectButtonPress();

private:
    void loadSaveFiles() const;
    //void closeEvent(QCloseEvent* event);

private:
    Ui::GameLoader *ui;
};

#endif // GAMELOADER_H
