#include "filewindow.h"

FileWindow::FileWindow(QWidget *parent) : QWidget(parent){

    this->setGeometry(100,100,600,400);
}

void FileWindow::setViewMrHolt(){
    this->setWindowTitle("File window");
    delete this->layout();
    QVBoxLayout *layout = new QVBoxLayout;
            QFile fichier("files/comb_traj_20160219_121123.dat");
            QScrollArea *zoneDefilement = new QScrollArea;
            QLabel *label = new QLabel("test");
            setLayout(layout);
    fichier.open(QIODevice::ReadOnly);

    QString s;
    QStringList liste;
    QStringList split;
    int countZero=0;
    QTableWidget *table = new QTableWidget(300, 38);
    table->setEditTriggers(QAbstractItemView::EditTriggers(0));
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //label->setText(s);
    zoneDefilement->setWidget(table);
    layout->addWidget(table);
    layout->addWidget(label);
    QTableWidgetItem *item;
    int i = 0;
    int l=0;
    while(!fichier.atEnd()) {
        s = fichier.readLine(10000);
        liste = s.split('\t');
        l=0;
        for(int j = 0 ; j < liste.size()-3 ; j+=3) {

            item = new QTableWidgetItem(liste.value(j)+liste.value(j+1)+liste.value(j+2));
            split=item->text().split(" ");


            table->setItem(i, l, item);
            QString x=split.value(0);
            QString y=split.value(1);
            QString z=split.value(2);

            if(x.toDouble()==0&&y.toDouble()==0&&z.toDouble()==0){
                item->setBackgroundColor(QColor(255, 0, 0));
                countZero++;
            }
            l++;
        }
        i++;
    }
    label->setText(""+ QString::number(countZero));
    table->resizeColumnsToContents();

    fichier.close();
}

void FileWindow::setViewMrNilsen(){
    this->setWindowTitle("File window");
    delete this->layout();
    QVBoxLayout *layout = new QVBoxLayout;
            QFile fichier("files/comb_traj_20160219_121123.dat");
            QScrollArea *zoneDefilement = new QScrollArea;
            QLabel *label = new QLabel("ligne vide");
            setLayout(layout);
    fichier.open(QIODevice::ReadOnly);

      QString s;
      QStringList liste;
      int countZero=0;
      QTableWidget *table = new QTableWidget(114,300);
      table->setEditTriggers(QAbstractItemView::EditTriggers(0));
      table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      zoneDefilement->setWidget(table);
      layout->addWidget(table);
      layout->addWidget(label);
;
      QTableWidgetItem *item;
      int i = 0;
      QTableWidgetItem *itemx;
      QTableWidgetItem* itemy;
      while(!fichier.atEnd()) {
          s = fichier.readLine(10000);
          liste = s.split('\t');
          for(int j = 0 ; j < liste.size() ; j++) {
              item = new QTableWidgetItem(liste.value(j));

              table->setItem(j, i, item);

              if(j%3==0){
                  itemx=item;
              }
              else if(j%3==1){
                  itemy=item;
              }
              else if(item->text().toDouble()==0||itemx->text().toDouble()==0||itemy->text().toDouble()==0){
                  itemx->setBackgroundColor(QColor(255,0,0));
                  itemy->setBackgroundColor(QColor(255,0,0));
                  item->setBackgroundColor(QColor(255, 0, 0));
                  countZero++;
              }
          }
          i++;
      }
      label->setText(""+ QString::number(countZero));
      table->resizeColumnsToContents();
      fichier.close();
}
