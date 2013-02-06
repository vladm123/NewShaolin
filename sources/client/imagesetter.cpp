#include "imagesetter.h"

ImageSetter::ImageSetter(QWidget *parent, const int &wid, const int &hei)
{
    // setez parintele
    this->setParent(parent);

    // setez dimensiunile
    this->setGeometry(0,0, wid, hei);
}

void ImageSetter::paintEvent(QPaintEvent *pt)
{
    // declar optiune de stil
    QStyleOption opt;

    // initializez optiunea
    opt.init(this);

    // declar variabila care deseneaza
    QPainter p(this);

    // desenez poza
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    // arat elementul
    this->show();
}

// destructor
ImageSetter::~ImageSetter()
{

}

