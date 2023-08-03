# Descripción del Código - Lectura de Datos desde un Puerto Serie

Este repositorio contiene un programa en C++ que utiliza la biblioteca Qt para establecer una comunicación serial con un dispositivo a través del puerto serie (COM6 en este caso). El programa recibe datos del dispositivo y los muestra en una interfaz gráfica.

## Requisitos

- Compilador C++
- Biblioteca Qt

## Cómo funciona

1. El programa comienza incluyendo las cabeceras necesarias y define una clase `MainWindow` que hereda de `QMainWindow`.
2. En el constructor `MainWindow::MainWindow(QWidget *parent)`, se inicializa la interfaz de usuario y se configura la comunicación serial mediante la clase `QSerialPort`.
3. La función `connect` establece una conexión entre la señal `readyRead()` emitida por el objeto `COMPORT` y el método `Read_Data()` en la instancia actual (`this`). Esto permite que cuando haya datos disponibles para leer en el puerto serial, se active automáticamente la función `Read_Data()` para procesar esos datos.
4. En la función `Read_Data()`, se verifica si el puerto serie está abierto y se itera mientras haya bytes disponibles para leer. Los datos leídos se acumulan en la variable `Data_From_SerialPort`.
5. Se verifica si el último caracter leído es un salto de línea (caracter ASCII 10), indicando la finalización de una transmisión de datos.
6. Si se detecta un salto de línea, se establece la bandera `IS_Data_Recevied` en verdadero.
7. Si ha sido recibido un conjunto completo de datos (`IS_Data_Recevied` es verdadero), se muestran los datos recibidos en la salida de depuración y en un widget de texto en la interfaz gráfica (`textEdit`).
8. Las variables se reinician para futuras lecturas.

## Uso

1. Asegúrate de cumplir con los requisitos mencionados anteriormente.
2. Compila y ejecuta el programa.
3. Conecta el dispositivo al puerto COM6.
4. Observa cómo los datos recibidos del dispositivo se muestran tanto en la consola de depuración como en la interfaz gráfica.

## Notas

- Este código es un ejemplo básico para demostrar la lectura de datos desde un puerto serie utilizando Qt. Puedes adaptarlo y expandirlo según tus necesidades.
- Asegúrate de tener los controladores adecuados para el puerto serie y el dispositivo con el que deseas comunicarte.
- Si deseas cambiar el puerto COM o la configuración de comunicación, modifica las respectivas líneas de código en el constructor.
