#include <QTableWidget>
#include <QTimer>

class JournalTableWidget : public QTableWidget {
    Q_OBJECT

public:
    JournalTableWidget(QWidget *parent = nullptr);
    ~JournalTableWidget();

    void setJournalMap(std::map<int, int> journal);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool viewportEvent(QEvent *event) override;

private:
    std::map<int, int> journal_;
    QTimer *timer;
    QPoint lastPosition;
};
