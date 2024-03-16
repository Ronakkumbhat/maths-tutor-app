#include "welcomepage.h"
#include "ui_welcomepage.h"
#include "mainwindow.h"
#include<qdebug.h>
#include <QKeyEvent>
welcomepage::welcomepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcomepage)
{
    ui->setupUi(this);
    //connect(ui->math_window_button, &QPushButton::clicked, this, &welcomepage::executemathtutor);
    ui->enter_box->setFocus();
    ui->enter_box->installEventFilter(this);
}

welcomepage::~welcomepage()
{
    delete ui;
}
void welcomepage::executemathtutor(){
    qDebug() << "Proceeding to main window";
    // Initialize the main window
    MainWindow *mainWindow = new MainWindow(this);
    mainWindow->show();
    this->hide();
}
bool welcomepage::eventFilter(QObject *obj, QEvent *event) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (event->type() == QEvent::KeyPress) {
        switch (keyEvent->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            executemathtutor();
        }
    }
    return QObject::eventFilter(obj, event);
}
