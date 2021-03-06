#include "process_view.h"
#include <QTimer>

ProcessView::ProcessView()
{
    // Set row height.
    setRowHeight(36);
    
    // Set column widths.
    QList<int> widths;
    widths << -1 << 60 << 70 << 80 << 80 << 70 << 70 << 60;
    setColumnWidths(widths);
    
    // Set column titles.
    QList<QString> titles;
    titles << "进程名" << "CPU" << "内存" << "磁盘写入" << "磁盘读取" << "下载" << "上传" << "序号";
    setColumnTitles(titles, 36);
    
    // Set column hide flags.
    QList<bool> toggleHideFlags;
    toggleHideFlags << false << true << true << true << true << true << true << true;
    setColumnHideFlags(toggleHideFlags);
    
    // Focus keyboard when create.
    QTimer::singleShot(0, this, SLOT(setFocus()));
}
