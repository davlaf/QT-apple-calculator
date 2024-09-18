#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum NumberButton {
        Button0 = '0',
        Button1 = '1',
        Button2 = '2',
        Button3 = '3',
        Button4 = '4',
        Button5 = '5',
        Button6 = '6',
        Button7 = '7',
        Button8 = '8',
        Button9 = '9',
        Period = '.',
    };
    enum Operator {
        Multiply = '*',
        Add = '+',
        Subtract = '-',
        Divide = '/',
        NoneOperator,
    };
    void addToExpression(enum NumberButton button);

    void highlightCurrentOperatorButton(enum MainWindow::Operator operation);
    void hideAllOperatorButtons();

private slots:
    void on_button_0_pressed();
    void on_period_button_pressed();
    void on_equals_button_pressed();
    void on_button_1_pressed();
    void on_button_2_pressed();
    void on_button_3_pressed();
    void on_add_button_pressed();
    void on_button_4_pressed();
    void on_button_5_pressed();
    void on_button_6_pressed();
    void on_subtract_button_pressed();
    void on_button_7_pressed();
    void on_button_8_pressed();
    void on_button_9_pressed();
    void on_multiply_button_pressed();
    void on_ac_button_pressed();
    void on_plus_minus_button_pressed();
    void on_percent_button_pressed();
    void on_divide_button_pressed();

private:
    Ui::MainWindow *ui;
    QString expression;
    double previousNumber = 0;
    Operator currentOperator = NoneOperator;
    bool justSetOperator = true;
    void setCurrentOperator(enum Operator operation);

};
#endif // MAINWINDOW_H
