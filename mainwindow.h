#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextToSpeech>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    double tans; // Correct answer
    double _n1,_n2; // Numbers to be operated
    QString question,operation;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void verbosesay();
    QString spellOutNumber(int number);
    bool eventFilter(QObject *obj, QEvent *event);

    void validateUserInput(const QString &text);
public slots:
    void generateQuestion();
    void operationChanged();
    void checkAnswer();
    void clearUserAnswer();
signals:
    void newquestion();
private:
    Ui::MainWindow *ui;
    QTextToSpeech *speech; // QTextToSpeech object

};

#endif // MAINWINDOW_H
