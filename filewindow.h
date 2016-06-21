#ifndef FILEWINDOW_H
#define FILEWINDOW_H
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QTableWidget>
#include <QFile>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QScrollArea>
#include <iostream>
#include <QTextEdit>
#include <QTableWidget>
#include <QStringList>
#include <QTableWidgetItem>
#include <QSizePolicy>
#include "data.h"
/**
 * @brief The FileWindow class
 * FileWindow is a class that enables two display possibilities for coordinates in a table.
 */
class FileWindow : public QWidget
{
private:
    const Data *data;
public:
    /**
     * @brief FileWindow
     * Constructor that creates an instance of a FileWindow
     */
    FileWindow(QWidget *parent = Q_NULLPTR);

    /**
     * @brief setViewMrHolt
     * Sets the window view to a table with the 3 coordinates in one same cell, the timesteps in rows and the markers in columns.
     */
    void setViewMrHolt();

    /**
     * @brief setViewMrNilsen
     * Sets the window view to a table with one coordinate in one cell, the timesteps in columns and the markers in rows.
     */
    void setViewMrNilsen();

    /**
     * @brief setData
     * @param pointerToData The pointer to set
     * Sets the data to a pointer of a data
     */
    void setData(const Data *pointerToData);
};

#endif // FILEWINDOW_H
