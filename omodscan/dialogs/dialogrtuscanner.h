#ifndef DIALOGRTUSCANNER_H
#define DIALOGRTUSCANNER_H

#include <QTimer>
#include <QListWidgetItem>
#include "qfixedsizedialog.h"
#include "connectiondetails.h"

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #include <QModbusRtuSerialMaster>
    typedef QModbusRtuSerialMaster QModbusRtuSerialClient;
#else
    #include <QModbusRtuSerialClient>
#endif

namespace Ui {
class DialogRtuScanner;
}

///
/// \brief The DialogRtuScanner class
///
class DialogRtuScanner : public QFixedSizeDialog
{
    Q_OBJECT

public:
    explicit DialogRtuScanner(QWidget *parent = nullptr);
    ~DialogRtuScanner();

protected:
    void changeEvent(QEvent* event) override;

signals:
    void attemptToConnect(const SerialConnectionParams& params, int deviceId);

private slots:
    void on_awake();
    void on_timeout();
    void on_pushButtonScan_clicked();
    void on_pushButtonClear_clicked();
    void on_errorOccurred(QModbusDevice::Error error);
    void on_stateChanged(QModbusDevice::State state);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void startScan();
    void stopScan();

    void clearScanTime();
    void clearProgress();

    void printScanInfo(const SerialConnectionParams& params, int deviceId);
    void printResult(const SerialConnectionParams& params, int deviceId);

    void prepareParams();
    void setScanTme(quint64 time);

    void connectDevice(const SerialConnectionParams& params);
    void sendRequest(int deviceId);

private:
    Ui::DialogRtuScanner *ui;
    QModbusRtuSerialClient* _modbusClient;

private:
    quint64 _scanTime = 0;
    bool _scanning = false;

    QTimer _scanTimer;
    QList<SerialConnectionParams> _connParams;
    QList<SerialConnectionParams>::ConstIterator _iterator;
};

#endif // DIALOGRTUSCANNER_H
