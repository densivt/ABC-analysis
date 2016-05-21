#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <ctime>
#include <limits>
#include <cstdlib>

using namespace std;

QMap<QString, QString> getInfo(QString fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Fuck!";
    }
    QTextStream in(&file);
    QMap<QString, QString> map;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList fields = line.split("\t");
        map[fields.at(0)] = fields.at(1);
    }
    file.close();
    return map;
}

void toFile(QString fileName, QList<QString> id, QList<QString> letter){
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i=0; i<id.size(); i++){
        out << id.at(i) << "\t" << letter.at(i) << "\n";
    }
    return;
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //return a.exec();
    QString INPUT_FILE_NAME;
    QString OUTPUT_FILE_NAME;
    int POWER;
    int AB;
    int BC;
    QList<QString> id;
    QList<QString> letter;
    if (argc < 5){
        qDebug() << "ERROR! WRONG PARAMETERS!";
        qDebug() << "Press ANY key.";
        return 0;
    } else {
        INPUT_FILE_NAME = argv[1];
        OUTPUT_FILE_NAME = argv[2];
        POWER = atoi(argv[3]);
        AB = atoi(argv[4]);
        BC = atoi(argv[5]);
    }
    int start_time = clock();
    qDebug() << "Starting...";
    double SUMM = 0;
    qDebug() << "Reading from file...";
    QFile file(INPUT_FILE_NAME);
    if(!file.exists())
    {
        qDebug() << "ERROR! NO INPUT FILE!";
        qDebug() << "Press ANY key.";
        return 0;
    }
    QMap<QString, QString> map = getInfo(INPUT_FILE_NAME);
    qDebug() << "Calculating...";
    QList<double> value;
    id << "toDel";
    value << 0.0;
    foreach(QString key, map.keys()){
        double temp = map.value(key).toDouble();
        for(int i = 0; i < value.size(); i++){
            if (temp > value.at(i)){
                id.insert(i, key);
                value.insert(i, temp);
                break;
            }
        }
        SUMM += temp;
    }
    value[0] = (value[0]/SUMM)*100;
    for (int i=1; i < value.size(); i++){
        value[i] = (value[i]/SUMM)*100 + value[i-1];
    }
    id.removeLast();
    value.removeLast();
    for(int i=0; i<value.size(); i++){
        if (value.at(i)<AB){
            letter << "A";
        } else if (value.at(i)<BC){
            letter << "B";
        } else {
            letter << "C";
        }
    }
    qDebug() << "Writing to file...";
    toFile(OUTPUT_FILE_NAME, id, letter);
    int finish_time = clock();
    qDebug() << "Performed for: " << (finish_time - start_time) / 1000.0 <<"s.";
    qDebug() << "Press ANY key.";
    return 0;
}
