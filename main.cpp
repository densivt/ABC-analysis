#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <ctime>
#include <limits>

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

void toFile(QList<QString> id, QList<double> value){
    QFile file("out.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i=0; i<id.size(); i++){
        out << id.at(i) << "\t" << value.at(i) << "\n";
    }
    return;
}

int main(/*int argc, char *argv[]*/)
{
    //QCoreApplication a(argc, argv);
    //return a.exec();
    int start_time = clock();
    QString INPUT_FILE_NAME = "input.txt";
    QFile file(INPUT_FILE_NAME);
    double SUMM = 0;
    if(!file.exists())
    {
        qDebug() << "Where is my f#$kin' file!";
    }
    QMap<QString, QString> map = getInfo(INPUT_FILE_NAME);
    QList<QString> id;
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
    toFile(id, value);
    qDebug() << SUMM;
    int finish_time = clock();
    qDebug() << (finish_time - start_time) / 1000.0;
    return 0;
}
