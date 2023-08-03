#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuración de comunicación por medio de la clase QSerialPort

    COMPORT = new QSerialPort();
    COMPORT->setPortName("COM6");
    COMPORT->setBaudRate(QSerialPort::BaudRate::Baud9600);
    COMPORT->setParity(QSerialPort::Parity::NoParity);
    COMPORT->setDataBits(QSerialPort::DataBits::Data8);
    COMPORT->setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    COMPORT->open(QIODevice::ReadWrite);

    if (COMPORT->isOpen())
    {
        qDebug() << "Serial Port se encuentra conectado";
        qDebug() << COMPORT->error();
    }
    else
    {
        qDebug() << "Serial Port no se encuentra conectado";
        qDebug() << COMPORT->error();
    }
    /*
    La función connect establece una conexión entre la señal readyRead()
    emitida por el objeto COMPORT y la ranura (método) Read_Data en el objeto actual (this).
    Cuando el objeto COMPORT emite la señal readyRead(), que ocurre cuando hay datos disponibles
    para leer en el puerto serial, la ranura Read_Data se ejecutará para manejar esos datos.
    En otras palabras, cada vez que datos nuevos estén disponibles en el puerto serie (COMPORT),
    la función Read_Data se activará y podrá leer y procesar esos datos.
    */

        connect(COMPORT,SIGNAL(readyRead()),this,SLOT(Read_Data()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Read_Data()
{
    // Verifica si el puerto serie está abierto
    if (COMPORT->isOpen())
    {
        // Itera mientras haya bytes disponibles para leer en el puerto
        while (COMPORT->bytesAvailable())
        {
            // Lee todos los datos disponibles en el puerto y los agrega a la variable Data_From_SerialPort
            Data_From_SerialPort += COMPORT->readAll();

            // Verifica si el último caracter leído es un salto de línea (caracter ASCII 10)
            if (Data_From_SerialPort.at(Data_From_SerialPort.length() - 1) == char(10))
            {
                // Si se detecta un salto de línea, establece IS_Data_Recevied en verdadero
                IS_Data_Recevied = true;
            }
        }
        // Si se ha recibido algún dato completo
        if (IS_Data_Recevied == true)
        {
            // Muestra los datos recibidos en la salida de depuración
            qDebug() << "Data From Serial Port: " << Data_From_SerialPort;
            ui->textEdit->append(Data_From_SerialPort);
            // Reinicia la variable Data_From_SerialPort para futuras lecturas
            Data_From_SerialPort = "";
            // Reinicia la bandera de recepción de datos
            IS_Data_Recevied = false;
        }
    }
}
