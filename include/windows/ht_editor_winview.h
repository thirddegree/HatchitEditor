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

#pragma once

#include <QWidget>
#include <QEvent>
#include <QPaintEngine>
#include <QTimer>

#include <ht_renderer.h>

namespace Hatchit {

    namespace Editor
    {
        class WinView : public QWidget
        {
            Q_OBJECT
        public:
            WinView(Graphics::RendererType type, QWidget* parent = 0);

            ~WinView();

            inline virtual QPaintEngine* paintEngine() const { return NULL; }

        signals:
            void NeedsRepaint();

        protected slots:
            void OnFrameUpdate();

        protected:
            void paintEvent(QPaintEvent* e);
            void resizeEvent(QResizeEvent* e);
           
            virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result);
            
            void render();
            
            QTimer timer;
        };
    }

}