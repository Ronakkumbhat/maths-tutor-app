#ifndef ENGLISH_TUTOR_H
#define ENGLISH_TUTOR_H

#include <QWidget>

namespace Ui {
class english_tutor;
}

class english_tutor : public QWidget
{
    Q_OBJECT

public:
    explicit english_tutor(QWidget *parent = nullptr);
    ~english_tutor();

private:
    Ui::english_tutor *ui;
};

#endif // ENGLISH_TUTOR_H
