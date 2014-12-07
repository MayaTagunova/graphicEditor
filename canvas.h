#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <memory>
#include <stdint.h>
#include <QString>
#include "tool.h"

#define WIDTH 400
#define HEIGHT 300

class Canvas
{
public:
    Canvas();
    ~Canvas();
    void setTool(Tool *tool);
    void setPath(QString newFileName);
    QString getPath();
    QString getFileName();
    bool readFile();
    bool writeFile();
    bool modified();
    void clear();

private:
    int m_Width;
    int m_Height;
    canvasMap m_Map;

    std::unique_ptr<Tool> m_Tool;
    QString m_Path;
    bool m_Modified;
};

#endif // CANVAS_H
