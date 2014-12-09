#ifndef CANVAS_H
#define CANVAS_H

#include <QString>
#include <QImage>
#include "tool.h"

#define WIDTH 400
#define HEIGHT 300

class Canvas
{
public:
    Canvas();
    ~Canvas();

    void setPath(QString newFileName);
    QString getPath();
    QString getFileName();
    QImage* getImage();
    bool readFile();
    bool writeFile();
    bool modified();
    void setModified();
    void clear();
    void undo();
    void storeImage();

private:
    QImage m_Image;
    QImage m_PreviousImage;
    QString m_Path;
    bool m_Modified;
};

#endif // CANVAS_H
