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
#include <QSplitter>

#include <ht_editor_projectinfo.h>
#include <ht_inisettings.h>
#include <ht_os.h>
#include <ht_file.h>
#include <ht_jsonhelper.h>
#include <ht_os.h>

namespace Hatchit
{
    namespace Editor
    {
        Launcher::Launcher(QWidget* parent)
            : QDialog(parent)
        {
            setObjectName("Launcher");
            setFixedSize(800, 600);

            SetupUI();
            ProcessRecent();
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

                    /**
                     * We should now check to see if this project path already exists in the
                     * recent projects list. If it does not, we should add it
                     */
                    auto res = std::find(m_recent.begin(), m_recent.end(), dir.toStdString());
                    if(res == m_recent.end())
                        m_recent.push_back(dir.toStdString());
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

        void Launcher::SaveRecent()
        {
            using namespace Hatchit::Core;

            /**
             * Here we want to save all the paths to all the recent projects
             * in the launcher's recent list.
             */
            QFile file(QString::fromStdString(os_exec_dir()) + QString("recent.json"));
            if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                JSON json;
                for(auto recent : m_recent)
                    json["RecentProjects"].push_back(recent);

                file.write(QByteArray::fromStdString(json.dump(4)));
            }

        }

        bool Launcher::ProcessRecent()
        {
            using namespace Hatchit::Core;

            /**
             * We want to show the user all the recent projects they have created or
             * been working on. To do this we will load the recent.json file
             * that is created each time editor is run. This means
             * we need to maintain a list of all the VALID recent projects
             *
             * NOTE:
             *      If we fail to open the recent.json this method will return false
             */

            QFile file(QString::fromStdString(os_exec_dir()) + QString("recent.json"));
            if(!file.open(QIODevice::ReadOnly))
                return false;

            JSON j = JSON::parse(file.readAll().toStdString());

            JSON recent = j["RecentProjects"];
            if(!recent.is_null() && recent.is_array())
            {
                std::vector<std::string> list = recent.get<std::vector<std::string>>();
                for(auto& s : list)
                {
                    if(os_isdir(s))
                    {
                        QDir dir(QString::fromStdString(s));
                        QFileInfo check(dir, ".ht_proj");
                        if(check.exists())
                        {
                            m_recent.push_back(s);

                            /**
                             * We want to clean the file paths on Linux so that a users /home/*
                             * path signature is instead replaces with the relative version ~/
                             */
#ifdef HT_SYS_LINUX
                            std::string homePath = QDir::homePath().toStdString();
                            size_t loc = s.find(homePath);
                            if(loc != std::string::npos)
                                s.replace(loc, homePath.size(), "~");
#endif
                            m_recentList->addItem(QString::fromStdString(s));
                        }

                    }
                }
            }

            return true;
        }

        void Launcher::SetupUI()
        {
            m_recentList = new QListWidget;
            m_recentList->setObjectName("Launcher_RecentList");
            //m_recentList->setFixedSize(300, 600);

            QHBoxLayout* mainLayout = new QHBoxLayout;
            QSplitter*   mainSplitter = new QSplitter;
            mainSplitter->addWidget(m_recentList);

            QWidget* mainWidget = new QWidget;
            mainWidget->setObjectName("Launcher_Main");
            QLabel* label = new QLabel("Hatchit Editor");
            label->setAlignment(Qt::AlignCenter);
            QVBoxLayout* mainWLayout = new QVBoxLayout;
            mainWLayout->addWidget(label);
            mainWidget->setLayout(mainWLayout);

            mainSplitter->addWidget(mainWidget);
            mainSplitter->setCollapsible(0, true);
            mainSplitter->setCollapsible(1, false);
            mainLayout->addWidget(mainSplitter);
            setLayout(mainLayout);

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
            mainWLayout->addLayout(layout);

            connect(m_createNew, SIGNAL(clicked()), this, SLOT(OnCreateNew()));
            connect(m_openExisting, SIGNAL(clicked()), this, SLOT(OnOpenExisting()));


            m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    }
}
