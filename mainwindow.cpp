#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->BTN_SRC_FOLDER,&QPushButton::clicked, this, &MainWindow::SelectSrcFolder);
    QObject::connect(ui->BTN_DST_FOLDER, &QPushButton::clicked, this, &MainWindow::SelectDstFloder);
    QObject::connect(ui->BTN_START_ORGANIZATION, &QPushButton::clicked, this, &MainWindow::StartOrganization);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectSrcFolder()
{
    QFileDialog srcDialog(this, "请选择待整理的文件夹", "C:/Users/taoli/Desktop/2DObject");

    //设置对话框属性

    /***********************************************************************************************************
     * Option
     * 设置是否使用本地文件对话框
     * 设置对话框中的显示内容（对系统对话框无效）
     * 设置是否请求重写确认
     * 设置是否显示用户图标
     * 设置文件的读写属性
     * 设置是否隐藏文件名的过滤细节
     ************************************************************************************************************/
    //srcDialog.setOption(QFileDialog::DontUseNativeDialog);                                //仅能设置一种选项
    //srcDialog.setOptions(QFileDialog::DontUseNativeDialog | QFileDialog::ShowDirsOnly);   //可以同时设置多种选项




    /************************************************************************************************************
     * ViewMode
     * 用于设置对话框中文件的显示方式，详细还是列表（使用系统对话框时无效）
    *************************************************************************************************************/
    //srcDialog.setViewMode(QFileDialog::Detail);




    /************************************************************************************************************
     * AcceptMode
     * 设置对话框类型是用于读取还是用于保存
    **************************************************************************************************************/
    srcDialog.setAcceptMode(QFileDialog::AcceptOpen);




    /*************************************************************************************************************
     * FileMode
     * 用于设置对话框中的显示内容，用途与Option中的部分功能相同，该属性对系统对话框有效
     * AnyFile: 任何文件(包括不存在的文件)
     * ExistingFile: 任何一个存在的文件
     * ExistingFiles: 任何多个存在的文件
     * Directory: 任何存在的文件夹
    **************************************************************************************************************/
    srcDialog.setFileMode(QFileDialog::Directory);




    /**************************************************************************************************************
     * DialogLabel
     * 用于设置对话框上的标签
    ***************************************************************************************************************/
    //DialogLabel
    srcDialog.setLabelText(QFileDialog::LookIn, "My Look In:");     //使用系统对话框时无效
    srcDialog.setLabelText(QFileDialog::FileType, "My File Type:"); //使用系统对话框时无效
    srcDialog.setLabelText(QFileDialog::FileName, "My File Name:");
    srcDialog.setLabelText(QFileDialog::Accept, "My Accept:");
    srcDialog.setLabelText(QFileDialog::Reject, "My Reject");

    //设置默认打开路径


    //获取待整理的文件夹路径
    if(srcDialog.exec())
    {
        QStringList strlSourceDir = srcDialog.selectedFiles();
        m_strSourceDirectory = strlSourceDir[0];
        ui->LINEEIDT_SRC_FOLDER->setText(m_strSourceDirectory);
    }
}

void MainWindow::SelectDstFloder()
{
    QFileDialog dstDialog(this, "请选择目标文件夹……", "C:/Users/taoli/Desktop/copy");
    dstDialog.setAcceptMode(QFileDialog::AcceptOpen);
    dstDialog.setFileMode(QFileDialog::Directory);

    if(dstDialog.exec())
    {
        QStringList strlDestination =dstDialog.selectedFiles();
        m_strDestinationDirectory = strlDestination[0];
        ui->LINEEIDT_DST_FOLDER->setText(m_strDestinationDirectory);
    }
}

void MainWindow::StartOrganization()
{
    QDir dirSrc;
    dirSrc.setPath(m_strSourceDirectory);

    //设置名称过滤器
    //QStringList strlNameFilter;
    //strlNameFilter << "*.jpg" << "*.png" << "*.bmp" << "*.tif";


    /********************************************************************
     * 设置属性过滤器
     * Dirs: 获得与名称过滤器相匹配的所有文件夹路径，包括"."和".."
     * AllDirs: 忽略名称过滤器，列出指定路径中的所有文件夹路径, 包括"."和".."
     * Files: 获得与名称过滤器相匹配的所有文件的路径
     * NotDot: 不包括"."
     * NotDotDot: 不包括".."
     * NotDotAndDotDot: 不包括"."和".."
    *********************************************************************/
    m_srcFileInfoList = dirSrc.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (int i = 0; i < m_srcFileInfoList.size(); i++)
    {
        QFileInfo folderInfoI = m_srcFileInfoList[i];
        QDir dirSrcSubFolder;
        dirSrcSubFolder.setPath(folderInfoI.absoluteFilePath());


        //设置名称过滤器
        QStringList strlNameFilter;
        strlNameFilter << "*.bmp" << "*.jpg" << "*.png";

        //获取该路径下的所有文件
        QFileInfoList tempFileInfoList = dirSrcSubFolder.entryInfoList(strlNameFilter, QDir::Files);
        for(int j=0; j<tempFileInfoList.size(); j++)
        {
            //在目标目录下创建与该文件名称相同的文件夹
            QString strDstSubFolder = m_strDestinationDirectory + "/" + tempFileInfoList[j].baseName();
            QDir dirDstSub;
            dirDstSub.mkdir(strDstSubFolder);

            //拷贝并将文件重命名为"源文件夹名+图像名"
            QFile::copy(tempFileInfoList[j].absoluteFilePath(),
                        strDstSubFolder + "/" + folderInfoI.baseName() +"_" +tempFileInfoList[j].baseName()  + ".bmp");
        }
    }
}

