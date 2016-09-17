/**
**    Hatchit Editor
**    Copyright(c) 2015 Third-Degree
**
**    GNU General Public License
**    This file may be used under the terms of
**    the GNU General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.GPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU General Public License requirements
**    will be met: https://www.gnu.org/licenses/gpl.html
**
**/

#include <ht_editor_launcher.h>
#include <QBoxLayout>
#include <QLabel>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <ht_editor_projectinfo.h>
#include <ht_inisettings.h>
#include <ht_os.h>
#include <ht_file.h>

namespace Hatchit
{
    namespace Editor
    {
        Launcher::Launcher(QWidget* parent)
            : QDialog(parent)
        {
            setMinimumWidth(500);
            setMaximumHeight(100);

            m_createNew = new QPushButton(tr("Create New"));
            m_openExisting = new QPushButton(tr("Open Existing"));

            m_directoryEdit = new QLineEdit;
            m_directoryEdit->setText(QDir::homePath());
            m_directoryEdit->setReadOnly(true);

            QLabel* dirLabel = new QLabel(tr("Project Directory:"));
            QHBoxLayout* dirEditLayout = new QHBoxLayout;
            dirEditLayout->addWidget(dirLabel);
            dirEditLayout->addWidget(m_directoryEdit);

            m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
            connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
            
            QVBoxLayout* layout = new QVBoxLayout;
            layout->addLayout(dirEditLayout, Qt::AlignTop);
            QHBoxLayout* createOpenLayout = new QHBoxLayout;
            createOpenLayout->addWidget(m_createNew, Qt::AlignRight);
            createOpenLayout->addWidget(m_openExisting, Qt::AlignRight);
            layout->addLayout(createOpenLayout);
            layout->addWidget(m_buttonBox);
            setLayout(layout);

            connect(m_createNew, SIGNAL(clicked()), this, SLOT(OnCreateNew()));
            connect(m_openExisting, SIGNAL(clicked()), this, SLOT(OnOpenExisting()));


            m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }

        void Launcher::OnCreateNew()
        {
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
            if(!dir.isEmpty())
            {
                QDir directory(dir);
                QFile file(directory.filePath(".ht_proj"));
                if(!file.open(QIODevice::ReadWrite))
                    return;
                else
                {
                    /*Need to now build the directory structure for a Hatchit project*/
                    m_directoryEdit->setText(dir);
                    m_projectPath = dir;
                    m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
                    
                    /*Core::INIReader reader;
                    Core::File file;
                    try
                    {
                        file.Open(Core::os_exec_dir() + "projectconf.ini", Core::File::FileMode::ReadText);

                        reader.Load(&file);
                    }
                    catch(std::exception& e)
                    {
                        
                    }*/

                    /*QString assetPath = QString::fromStdString(reader.GetValue("PATHS", "sAssetPath", std::string("")));
                    QString modelPath = QString::fromStdString(reader.GetValue("PATHS", "sModelPath", std::string("")));
                    QString texturePath = QString::fromStdString(reader.GetValue("PATHS", "sTexturePath", std::string("")));
                    directory.mkpath(m_projectPath + QDir::separator() + assetPath);
                    directory.mkpath(m_projectPath + QDir::separator() + modelPath);
                    directory.mkpath(m_projectPath + QDir::separator() + texturePath);
                    QFile assetFile(m_projectPath + QDir::separator() + assetPath + ".ht_asset");
                    assetFile.open(QIODevice::ReadWrite);
                    */
                }
            }
        }

        void Launcher::OnOpenExisting()
        {
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
            if(!dir.isEmpty())
            {
                QDir directory(dir);
                QFileInfo checkFile(directory, ".ht_proj");
                if(checkFile.exists())
                {
                    m_directoryEdit->setText(dir);                  
                    m_projectPath = dir;
                    m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
                }
                else
                {
                    QMessageBox::warning(this, "Project Directory", "Selected directory is not a Hatchit project directory");
                }
            }
        }

        QString Launcher::ProjectPath()
        {
            return m_projectPath;
        }
    }
}
