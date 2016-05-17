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
class FileWindow : public QWidget
{

public:
    FileWindow(QWidget *parent = Q_NULLPTR);
    void setViewMrHolt();
    void setViewMrNilsen();
};

#endif // FILEWINDOW_H
