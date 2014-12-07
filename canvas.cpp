#include <QFile>
#include <QFileInfo>
#include "canvas.h"
#include "toolfactory.h"

Canvas::Canvas() :
    m_Width(WIDTH),
    m_Height(HEIGHT),
    m_Map(m_Width * m_Height),
    m_Tool(nullptr),
    m_Path(""),
    m_Modified(false)
{

}

Canvas::~Canvas()
{

}

void Canvas::setTool(Tool *tool)
{
    m_Tool.reset(tool);
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

bool Canvas::readFile()
{
    QFile file(m_Path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //mText = QString::fromUtf8(file.readAll());
        m_Modified = false;
        file.close();
        return true;
    }
    return false;
}

bool Canvas::writeFile()
{
    QFile file(m_Path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        //file.write(mText.toUtf8());
        file.close();
        m_Modified = false;
        return true;
    }
    return false;
}

bool Canvas::modified()
{
    return m_Modified;
}

void Canvas::clear()
{
    //mText.clear();
    m_Path.clear();
    m_Modified = false;
}
