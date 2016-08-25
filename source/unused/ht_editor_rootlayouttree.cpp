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

#include <include/unused/ht_editor_rootlayouttree.h>
#include <ht_path_singleton.h>
#include <ht_debug.h>
#include <include/unused/ht_editor_rootlayoutitemdelegate.h>
#include <QComboBox>


namespace Hatchit
{
    namespace Editor
    {
        RootLayoutTree::RootLayoutTree(QWidget* parent)
            : QTreeView(parent)
        {
        
            this->setSortingEnabled(false);

            m_model = new RootLayoutModel;

            this->setModel(m_model);

            

            m_model->load(QString::fromStdString(Core::Path::Value(Core::Path::Directory::Assets) + "TestRootDescriptor.json"));
            

            this->expandAll();
        
            QComboBox* combo = new QComboBox;
            combo->addItem("test");
            combo->addItem("test2");

            this->setItemDelegate(new RootLayoutItemDelegate);

            QJsonTreeItem* root = m_model->root();
            for (int i = 0; i < root->childCount(); i++)
            {
                QJsonTreeItem* child = root->child(i);
                if (child->key() == "Flags")
                {
                    QModelIndex parentIndex = m_model->index(child->modelRow(), 0);
                    
                    /*Iterate over all flags children*/
                    
                    //this->setIndexWidget(m_model->index(child->child(0)->modelRow(), 1, parentIndex), combo);
                    //this->setIndexWidget(m_model->index(child->child(1)->modelRow(), 1, parentIndex), combo);
                    /*for (auto flagChild : child->children())
                    {
                        if (flagChild->editable())
                        {
                            
                            
                        }
                    }*/
                }
            }
            
        }
    }
}
