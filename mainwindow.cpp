#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextToSpeech>
#include <QDebug>
#include <cstdlib>
#include <QRegularExpression>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    speech = new QTextToSpeech(this);
    generateQuestion(); // Generate the initial question

    // Initialize QTextToSpeech object
    speech = new QTextToSpeech(this);

    // Connect signal for operation change
    connect(ui->operation, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::operationChanged);
    connect(ui->Difficulty_levels, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::generateQuestion);
    connect(this, &MainWindow::newquestion, this, &MainWindow::clearUserAnswer);
    connect(ui->user_ans, &QLineEdit::textChanged, this, &MainWindow::validateUserInput);

    ui->user_ans->setFocus();
    ui->user_ans->installEventFilter(this);
}
MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destructor called";
    delete ui;
    delete speech; // Release QTextToSpeech object
}
void MainWindow::validateUserInput(const QString &text) {
    // Regular expression pattern to match numeric input
     QRegularExpression regex("[0-9]+(\\.[0-9]+)?");

    // Match the input text against the regular expression pattern
    QRegularExpressionMatch match = regex.match(text);

    // If the input text does not match the pattern, clear the QLineEdit
    if (!match.hasMatch()) {
        ui->user_ans->clear();
    }
}
void MainWindow::clearUserAnswer() {
    ui->user_ans->clear();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
     QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (event->type() == QEvent::KeyPress) {
        switch (keyEvent->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            checkAnswer();
            break;
        case Qt::Key_Semicolon:
            speech->setRate(speech->rate()-0.2);
            break;
        case Qt::Key_Apostrophe:
            speech->setRate(speech->rate()+0.2);
            break;
        case Qt::Key_Shift:
            verbosesay();
            break;
        case Qt::Key_Space:
            speech->say(question);
            break;
        case Qt::Key_A: // Addition
            ui->operation->setCurrentIndex(0);
            break;
        case Qt::Key_S: // Subtraction
            ui->operation->setCurrentIndex(1);
            break;
        case Qt::Key_D: // Division
            ui->operation->setCurrentIndex(2);
            break;
        case Qt::Key_M: // Multiplication
            ui->operation->setCurrentIndex(3);
            break;
        default:
            break;
        }
    }
   // ui->user_ans->clear();
    return QObject::eventFilter(obj, event);
}
QString MainWindow::spellOutNumber(int number) {
    QString spelledNumber;
    QString digits[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    // Convert each digit to its spelled-out form
    QString numStr = QString::number(number);
    for (int i = 0; i < numStr.length(); ++i) {
        QChar digit = numStr.at(i);
        if (digit.isDigit()) {
            int index = digit.digitValue();
            spelledNumber += digits[index];
            spelledNumber += " "; // Add space between digits
        }
    }

    return spelledNumber.trimmed(); // Remove trailing space
}
void MainWindow::verbosesay() {
    QString n1_v=spellOutNumber(_n1);
    QString n2_v=spellOutNumber(_n2);
    QString v_ques=QString("What is %1 %2 %3?").arg(n1_v).arg(operation).arg(n2_v);
    speech->say(v_ques);
}
void MainWindow::generateQuestion() {
    if(ui->Difficulty_levels->currentIndex()==0){
        _n1 = rand() % 5;
        _n2 =  rand() % 5;
    }
    else if(ui->Difficulty_levels->currentIndex()==1){
        _n1 = rand() % 50;
        _n2 =  rand() % 50;
    }
    else if(ui->Difficulty_levels->currentIndex()==2){
        _n1 = rand() % 4000;
        _n2 =  rand() % 4000;
    }
    else if(ui->Difficulty_levels->currentIndex()==3){
        _n1 = rand() % 50000;
        _n2 =  rand() % 50000;
    }
    else if(ui->Difficulty_levels->currentIndex()==4){
        _n1 = rand() % 500000;
        _n2 =  rand() % 500000;
    }
    else{
        _n1 = rand() % 1000;
        _n2 =  rand() % 1000;
    }
    if(_n2>_n1){
        int temp=_n1;
        _n1=_n2;
        _n2=temp;
    }
    if(_n2==0){
        _n2=1;
    }
    ui->n1->display(_n1);
    ui->n2->display(_n2);

    if(ui->operation->currentIndex() == 0){
        tans = _n1 + _n2;
    }
    else if(ui->operation->currentIndex() == 1){
        tans = _n1 - _n2;
    }
    else if(ui->operation->currentIndex() == 2){
        tans = _n1 / _n2;
    }
    else{
        tans = _n1 * _n2;
    }

    operation = ui->operation->currentText();
    question = QString("What is %1 %2 %3?").arg(_n1).arg(operation).arg(_n2);
    speech->say(question);
    ui->user_ans->setFocus();
   // ui->result->clear();
    emit newquestion();
}
void MainWindow::operationChanged() {
    if(ui->operation->currentIndex() == 0){
        ui->op_label->setText("+");
    }
    else if(ui->operation->currentIndex() == 1){
       ui->op_label->setText("-");
    }
    else if(ui->operation->currentIndex() == 2){
        ui->op_label->setText("/");
    }
    else{
      ui->op_label->setText("*");
    }

    generateQuestion(); // Generate a new question when the operation changes
   // speech->say(ui->operation->currentText());
}
void MainWindow::checkAnswer() {
    // Get the user's answer
    double userans = ui->user_ans->text().toDouble();
    userans = static_cast<int>(userans * 10) / 10.0; // Truncate to 1 decimal place
    tans= static_cast<int>(tans * 10) / 10.0; // Truncate to 1 decimal place
    // Check if the answer is correct
    if (qFuzzyCompare(userans, static_cast<double>(tans))) { // Using qFuzzyCompare to compare floating-point numbers
        ui->result->setText("Correct");
        speech->say("Correct");
        generateQuestion(); // Generate a new question
    } else {
        ui->result->setText("Wrong");
        speech->say("Wrong");
        ui->user_ans->clear();
        speech->say(question);
    }
}
