#include "imageedit.h"

ImageEdit::ImageEdit(QWidget *parent) :
    QWidget(parent),
    m_Image(),
    m_Modified(false)
{
    setAttribute(Qt::WA_StaticContents);
}

void ImageEdit::mouseMoveEvent (QMouseEvent *event){}
void ImageEdit::mousePressEvent (QMouseEvent *event){}
void ImageEdit::mouseReleaseEvent (QMouseEvent *event){}
