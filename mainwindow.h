#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileInfoList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString m_strSourceDirectory;
    QString m_strDestinationDirectory;
    QFileInfoList m_srcFileInfoList;


protected slots:
    void SelectSrcFolder();
    void SelectDstFloder();
    void StartOrganization();

};
#endif // MAINWINDOW_H
