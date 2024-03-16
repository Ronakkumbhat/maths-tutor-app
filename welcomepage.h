#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>
#include <mainwindow.h>
namespace Ui {
class welcomepage;
}

class welcomepage : public QWidget
{
    Q_OBJECT

public:
    explicit welcomepage(QWidget *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event);

    ~welcomepage();

private:
    Ui::welcomepage *ui;
signals:

public slots:
    void executemathtutor();
};

#endif // WELCOMEPAGE_H
