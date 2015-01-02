#include <QFile>
#include <QFileInfo>
#include "canvas.h"
#include "toolfactory.h"

Canvas::Canvas() :
    m_Image(WIDTH, HEIGHT, QImage::Format_RGB32),
    m_PreviousImage(m_Image),
    m_Path(""),
    m_Modified(false)
{
    m_Image.fill(Qt::white);
}

Canvas::~Canvas()
{

}

void Canvas::setPath(QString path)
{
    m_Path = path;
}

QString Canvas::getPath()
{
    return m_Path;
}

QString Canvas::getFileName()
{
    return QFileInfo(m_Path).fileName();
}

QImage* Canvas::getImage()
{
    return &m_Image;
}

bool Canvas::readFile()
{
    if (! m_Path.isEmpty()) {
        QImage newImage(m_Path);
        if (! newImage.isNull()) {
            m_Modified = false;
            m_Image = newImage;
            return true;
        }
    }
    return false;
}

bool Canvas::writeFile()
{
    if (m_Image.save(m_Path)) {
        m_Modified = false;
        return true;
    }
    return false;
}

bool Canvas::modified()
{
    return m_Modified;
}

void Canvas::setModified()
{
    m_Modified = true;
}

void Canvas::clear()
{
    QImage newImage(WIDTH, HEIGHT, QImage::Format_RGB32);
    m_Image = newImage;
    m_Image.fill(Qt::white);
    m_Path.clear();
    m_Modified = false;
}

void Canvas::undo()
{
    m_Image = m_PreviousImage;
}

void Canvas::storeImage()
{
    m_PreviousImage = m_Image;
}

int Canvas::getWidth()
{
    return m_Image.width();
}

int Canvas::getHeight()
{
    return m_Image.height();
}
