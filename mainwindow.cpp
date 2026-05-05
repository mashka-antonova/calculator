#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupUI() {
    initDigitButtons();
    initOperatorButtons();
    initActionButtons();
    initMemoryButtons();

    for (auto const& [btn, action] : actionMap)
        connect(btn, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
}

void MainWindow::mapButton(QPushButton* btn, std::function<void()> action) {
    if (btn)
        actionMap[btn] = action;
}

void MainWindow::initDigitButtons() {
    mapButton(ui->btn0, [this](){ facade.pressAction("0"); });
    mapButton(ui->btn1, [this](){ facade.pressAction("1"); });
    mapButton(ui->btn2, [this](){ facade.pressAction("2"); });
    mapButton(ui->btn3, [this](){ facade.pressAction("3"); });
    mapButton(ui->btn4, [this](){ facade.pressAction("4"); });
    mapButton(ui->btn5, [this](){ facade.pressAction("5"); });
    mapButton(ui->btn6, [this](){ facade.pressAction("6"); });
    mapButton(ui->btn7, [this](){ facade.pressAction("7"); });
    mapButton(ui->btn8, [this](){ facade.pressAction("8"); });
    mapButton(ui->btn9, [this](){ facade.pressAction("9"); });
    mapButton(ui->btnDot, [this](){ facade.pressAction("."); });
}

void MainWindow::initOperatorButtons() {
    mapButton(ui->btnPlus, [this](){ facade.pressAction("+"); });
    mapButton(ui->btnMinus, [this](){ facade.pressAction("-"); });
    mapButton(ui->btnMult, [this](){ facade.pressAction("*"); });
    mapButton(ui->btnDiv, [this](){ facade.pressAction("/"); });
    mapButton(ui->btnOpen, [this](){ facade.pressAction("("); });
    mapButton(ui->btnClose, [this](){ facade.pressAction(")"); });

    mapButton(ui->btnSin, [this](){ facade.pressAction("sin"); });
    mapButton(ui->btnCos, [this](){ facade.pressAction("cos"); });
    mapButton(ui->btnTg, [this](){ facade.pressAction("tg"); });
    mapButton(ui->btnCtg, [this](){ facade.pressAction("ctg"); });
    mapButton(ui->btnSqrt, [this](){ facade.pressAction("sqrt"); });
    mapButton(ui->btnRecip, [this](){ facade.pressAction("1/x"); });
}

void MainWindow::initActionButtons() {
    mapButton(ui->btnEqual, [this](){ facade.pressAction("="); });
    mapButton(ui->btnClear, [this](){ facade.pressAction("C"); });
    mapButton(ui->btnDel, [this](){ facade.pressAction("Del"); });

    if (ui->btnUndo) connect(ui->btnUndo, &QPushButton::clicked, this, &MainWindow::handleUndoClicked);
}

void MainWindow::initMemoryButtons() {
    mapButton(ui->btnMPlus, [this](){ facade.pressAction("M+"); });
    mapButton(ui->btnMMinus, [this](){ facade.pressAction("M-"); });
    mapButton(ui->btnMR, [this](){ facade.pressAction("MR"); });
    mapButton(ui->btnMC, [this](){ facade.pressAction("MC"); });
}

void MainWindow::handleButtonClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (actionMap.count(btn)) {
        actionMap[btn]();
        updateDisplay();
    }
}

void MainWindow::handleUndoClicked() {
    facade.undo();
    updateDisplay();
}

void MainWindow::updateDisplay() {
    if (ui->display)
        ui->display->setText(QString::fromStdString(facade.getDisplay()));
}
