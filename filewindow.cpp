#include "filewindow.h"

FileWindow::FileWindow(QWidget *parent) : QWidget(parent){

    this->setGeometry(100,100,600,400);
}

void FileWindow::setViewMrHolt(){
    this->setWindowTitle("View from Mr. Holt");
    delete this->layout();
    QVBoxLayout *layout = new QVBoxLayout;
            QFile fichier("comb_traj_20160219_121123.dat");
            QScrollArea *zoneDefilement = new QScrollArea;
            QLabel *label = new QLabel("test");
            setLayout(layout);
    fichier.open(QIODevice::ReadOnly);

    QString s;
    QStringList liste;
    QStringList split;
    int countZero=0;
    QTableWidget *table = new QTableWidget(38, 300);
    table->setEditTriggers(QAbstractItemView::EditTriggers(0));
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //label->setText(s);
    zoneDefilement->setWidget(table);
    layout->addWidget(table);
    QTableWidgetItem *item;
    int i = 0;
    int l=0;
    while(!fichier.atEnd()) {
        s = fichier.readLine(10000);
        liste = s.split('\t');
        l=0;
        for(int j = 0 ; j < liste.size() ; j++) {

            item = new QTableWidgetItem(liste.value(j)+liste.value(j+1)+liste.value(j+2));
            split=item->text().split(" ");


            table->setItem(l, i, item);
            QString x=split.value(0);
            const char *xchar=x.toStdString().c_str();
            QString y=split.value(1);
            const char *ychar=y.toStdString().c_str();
            QString z=split.value(2);
            const char *zchar=z.toStdString().c_str();
            if(strcmp(xchar,"0")==0&&strcmp(ychar,"0")==0&&strcmp(zchar,"0")==0){
                item->setBackgroundColor(QColor(255, 0, 0));
                countZero++;
            }
            l++;
        }
        i++;
    }
    label->setText(""+countZero);
    table->resizeColumnsToContents();

    fichier.close();
}

void FileWindow::setViewMrNilsen(){
    this->setWindowTitle("View from Mr. Nilsen");
    delete this->layout();
    QVBoxLayout *layout = new QVBoxLayout;
            QFile fichier("comb_traj_20160219_121123.dat");
            QScrollArea *zoneDefilement = new QScrollArea;
            QLabel *label = new QLabel("ligne vide");
            setLayout(layout);
    fichier.open(QIODevice::ReadOnly);

      QString s;
      QStringList liste;

      QTableWidget *table = new QTableWidget(114,300);
      table->setEditTriggers(QAbstractItemView::EditTriggers(0));
      table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      zoneDefilement->setWidget(table);
      layout->addWidget(table);
;
      QTableWidgetItem *item;
      int i = 0;
      while(!fichier.atEnd()) {
          s = fichier.readLine(10000);
          liste = s.split('\t');
          for(int j = 0 ; j < liste.size() ; j++) {
              item = new QTableWidgetItem(liste.value(j));

              table->setItem(j, i, item);
              if(item->text().toDouble()==0)
              item->setBackgroundColor(QColor(255, 0, 0));
          }
          i++;
      }
      table->resizeColumnsToContents();
      fichier.close();
}
