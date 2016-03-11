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

#include <ht_editor_resourcedatabase.h>
#include <QMessageBox>

#include <QFileDialog>

namespace Hatchit
{
    namespace Editor
    {
        const QString ResourceDatabase::ASSET_DIRECTORY_CHECK = ".ht_asset";

        ResourceDatabase::ResourceDatabase(QWidget* parent)
            : QDialog(parent)
        {
            m_menuBar = new QMenuBar;
            
            /*create File menu*/
            m_fileMenu = new QMenu(tr("File"));
            QAction* open = new QAction(tr("Open"), nullptr);
            connect(open, SIGNAL(triggered()), this, SLOT(OnFileMenuOpen()));
            m_fileMenu->addAction(open);

            m_menuBar->addMenu(m_fileMenu);

            m_splitter = new QSplitter;

            m_textView = new ResourceDatabaseTextView;
            m_jsonTree = new ResourceDatabaseJsonTree;
            m_treeView = new ResourceDatabaseTreeView;
            connect(m_treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                this, SLOT(OnFileSelection(const QItemSelection&, const QItemSelection&)));

            m_splitter->addWidget(m_treeView);
            m_splitter->addWidget(m_textView);
            m_splitter->addWidget(m_jsonTree);

            m_layout = new QVBoxLayout;
            m_layout->setMenuBar(m_menuBar);

            QHBoxLayout* hLayout = new QHBoxLayout;
            hLayout->addWidget(m_splitter);
            m_layout->addLayout(hLayout);

            setLayout(m_layout);
        }

        void ResourceDatabase::OnFileSelection(const QItemSelection& selected,
            const QItemSelection& deselected)
        {
            QFileSystemModel* model = (QFileSystemModel*)m_treeView->model();

            QString path = model->filePath(selected.indexes()[0]);
            if (!path.isEmpty())
            {
                QFile file(path);
                if (file.open(QIODevice::ReadOnly))
                {
                    QString text = file.readAll();

                    m_jsonTree->loadJson(text);
                    m_textView->setText(text);
                }
            }
        }

        void ResourceDatabase::OnFileMenuOpen()
        {
            /*Open file browser to choose project directory to open*/
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly |
                QFileDialog::DontResolveSymlinks);
            if (!dir.isEmpty())
            {
                QDir directory(dir);
                QFileInfo checkFile(directory, ASSET_DIRECTORY_CHECK);
                if (checkFile.exists())
                {
                    m_treeView->setDirectory(directory);
                }
                else
                {
                    QMessageBox::warning(this, "Asset Directory", "Selected directory is not a Hatchit asset directory");
                }
            }

        }
    }
}