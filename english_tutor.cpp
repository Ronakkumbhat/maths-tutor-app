#include "english_tutor.h"
#include "ui_english_tutor.h"

english_tutor::english_tutor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::english_tutor)
{
    ui->setupUi(this);
}

english_tutor::~english_tutor()
{
    delete ui;
}
