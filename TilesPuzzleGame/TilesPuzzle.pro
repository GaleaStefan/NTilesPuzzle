QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameLogic/GameWindow.cpp \
    gameLogic/PuzzleLogic.cpp \
    gameLogic/PuzzleState.cpp \
    gameSolver/HintDialog.cpp \
    gameSolver/PuzzleSolver.cpp \
    gameSolver/SolverNode.cpp \
    gameSolver/SolverState.cpp \
    handler/JsonFile.cpp \
    handler/SaveFile.cpp \
    levels/LevelDialog.cpp \
    loader/GameLoader.cpp \
    main.cpp \
    main/MainWindow.cpp

HEADERS += \
    gameLogic/GameWindow.h \
    gameLogic/PuzzleLogic.h \
    gameLogic/PuzzleState.h \
    gameSolver/HintDialog.h \
    gameSolver/PuzzleSolver.h \
    gameSolver/SolverNode.h \
    gameSolver/SolverState.h \
    gameSolver/eAction.h \
    handler/JsonFile.h \
    handler/SaveData.h \
    handler/SaveFile.h \
    levels/LevelDialog.h \
    loader/GameLoader.h \
    main/MainWindow.h

FORMS += \
    gameLogic/GameWindow.ui \
    gameSolver/HintDialog.ui \
    levels/LevelDialog.ui \
    loader/GameLoader.ui \
    main/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
