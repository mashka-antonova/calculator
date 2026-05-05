#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <map>
#include <functional>
#include "Facade.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    Facade facade;
    Ui::MainWindow* ui;
    std::map<QPushButton*, std::function<void()>> actionMap;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void handleButtonClicked();
    void handleUndoClicked();

    void setupUI();
    void updateDisplay();
    void mapButton(QPushButton* btn, std::function<void()> action);

    void initDigitButtons();
    void initOperatorButtons();
    void initActionButtons();
    void initMemoryButtons();
};
#endif // MAINWINDOW_H
