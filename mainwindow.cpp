#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_0_pressed()
{
    qDebug() << "0";
    addToExpression(MainWindow::Button0);
}

void MainWindow::on_period_button_pressed()
{
    qDebug() << ".";
    addToExpression(MainWindow::Period);
}


void MainWindow::on_equals_button_pressed()
{
    qDebug() << "=";

    double& prev_number = MainWindow::previousNumber;

    qDebug() << prev_number;
    double current_number = MainWindow::expression.toDouble();
    qDebug() << MainWindow::currentOperator;
    qDebug() << current_number;
    switch(MainWindow::currentOperator) {
    case Multiply:
        prev_number = prev_number * current_number;
        break;
    case Add:
        prev_number = prev_number + current_number;
        break;
    case Subtract:
        prev_number = prev_number - current_number;
        break;
    case Divide:
        prev_number = prev_number / current_number;
        break;
    case NoneOperator:
        prev_number = current_number;
        break;
    };

    MainWindow::currentOperator = MainWindow::NoneOperator;
    MainWindow::expression = QString::number(prev_number);
    ui->expression->setText(MainWindow::expression);
}


void MainWindow::on_button_1_pressed()
{
    qDebug() << "1";
    addToExpression(MainWindow::Button1);
}


void MainWindow::on_button_2_pressed()
{
    qDebug() << "2";
    addToExpression(MainWindow::Button2);
}


void MainWindow::on_button_3_pressed()
{
    qDebug() << "3";
    addToExpression(MainWindow::Button3);
}


void MainWindow::on_add_button_pressed()
{
    qDebug() << "+";
    setCurrentOperator(MainWindow::Add);
}


void MainWindow::on_button_4_pressed()
{
    qDebug() << "4";
    addToExpression(MainWindow::Button4);
}


void MainWindow::on_button_5_pressed()
{
    qDebug() << "5";
    addToExpression(MainWindow::Button5);
}


void MainWindow::on_button_6_pressed()
{
    qDebug() << "6";
    addToExpression(MainWindow::Button6);
}


void MainWindow::on_subtract_button_pressed()
{
    qDebug() << "-";
    setCurrentOperator(MainWindow::Subtract);
}


void MainWindow::on_button_7_pressed()
{
    qDebug() << "7";
    addToExpression(MainWindow::Button7);
}


void MainWindow::on_button_8_pressed()
{
    qDebug() << "8";
    addToExpression(MainWindow::Button8);
}


void MainWindow::on_button_9_pressed()
{
    qDebug() << "9";
    addToExpression(MainWindow::Button9);
}



void MainWindow::on_multiply_button_pressed()
{
    qDebug() << "x";
    setCurrentOperator(MainWindow::Multiply);
}


void MainWindow::on_ac_button_pressed()
{
    qDebug() << "ac";
    MainWindow::expression = "";
    MainWindow::previousNumber = 0;
    ui->expression->setText("0");
}


void MainWindow::on_plus_minus_button_pressed()
{
    qDebug() << "+/-";
    double number = MainWindow::expression.toDouble();
    if (number == 0) {
        return;
    }

    double flipped_number = number*-1;
    MainWindow::expression = QString::number(flipped_number);
    ui->expression->setText(MainWindow::expression);
}


void MainWindow::on_percent_button_pressed()
{
    qDebug() << "%";
    double number = MainWindow::expression.toDouble();
    double percent_number = number/100;
    MainWindow::expression = QString::number(percent_number);

    ui->expression->setText(MainWindow::expression);
}

void MainWindow::on_divide_button_pressed()
{
    qDebug() << "/";
    setCurrentOperator(MainWindow::Divide);
}

void MainWindow::addToExpression(enum MainWindow::NumberButton button)
{
    MainWindow::justSetOperator = false;

    hideAllOperatorButtons();

    if (MainWindow::expression == "0" && button == MainWindow::Button0) {
        return; // do nothing
    }

    if ((MainWindow::expression == "" || MainWindow::expression == "0") && button == MainWindow::Period) {
        MainWindow::expression = "0.";
        ui->expression->setText(MainWindow::expression);
        return;
    }

    if (MainWindow::expression == "0") {
        MainWindow::expression = "";
    }

    QString new_expression = MainWindow::expression;
    new_expression.append(QChar(button));

    // try to convert to double
    bool ok;
    new_expression.toDouble(&ok);
    if (!ok) {
        return; // do nothing
    }

    MainWindow::expression = new_expression;
    ui->expression->setText(new_expression);
}

void MainWindow::hideAllOperatorButtons() {
    QMap<MainWindow::Operator, QPushButton*> operatorButtons {
        {MainWindow::Add, ui->add_button},
        {MainWindow::Subtract, ui->subtract_button},
        {MainWindow::Multiply, ui->multiply_button},
        {MainWindow::Divide, ui->divide_button}
    };

    for (QPushButton* button: operatorButtons) {
        button->setProperty("isSelected", false);
        button->style()->polish(button);
    }
}

void MainWindow::highlightCurrentOperatorButton(enum MainWindow::Operator operation)
{
    hideAllOperatorButtons();
    QMap<MainWindow::Operator, QPushButton*> operatorButtons {
        {MainWindow::Add, ui->add_button},
        {MainWindow::Subtract, ui->subtract_button},
        {MainWindow::Multiply, ui->multiply_button},
        {MainWindow::Divide, ui->divide_button}
    };

    QPushButton* currentButton = operatorButtons[operation];

    currentButton->setProperty("isSelected", true);
    currentButton->style()->polish(currentButton);
}

void MainWindow::setCurrentOperator(enum MainWindow::Operator operation)
{
    MainWindow::Operator previous_operator = MainWindow::currentOperator;
    MainWindow::currentOperator = operation;

    highlightCurrentOperatorButton(operation);

    if (MainWindow::justSetOperator) {
        return; // we just set an operator so do nothing else
    }

    MainWindow::justSetOperator = true;

    // if someone types 3 + 5 and then selects - operator,
    // we want the calculator to say 8 and show the - operator selected for the next number

    // if the previous operator was nothing, no evaluation to do
    if (previous_operator == MainWindow::NoneOperator) {
        MainWindow::previousNumber = MainWindow::expression.toDouble();
        MainWindow::expression = "";
        return;
    }

    double& prev_number = MainWindow::previousNumber;
    double current_number = MainWindow::expression.toDouble();

    switch(previous_operator) {
    case Multiply:
        prev_number = prev_number * current_number;
        break;
    case Add:
        prev_number = prev_number + current_number;
        break;
    case Subtract:
        prev_number = prev_number - current_number;
        break;
    case Divide:
        prev_number = prev_number / current_number;
        break;
    case NoneOperator:
        break;
    };

    MainWindow::expression = "";
    ui->expression->setText(QString::number(prev_number));
}
