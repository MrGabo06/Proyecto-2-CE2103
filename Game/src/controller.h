#include <iostream>
#include <libserial/SerialPort.h>  // Incluye la biblioteca LibSerial
#include <thread>
#include <chrono>

using namespace LibSerial;

class Controller{
    public:
        char entry;
        bool playing = true;
        std::thread controllerThread = std::thread(&Controller::start, this);

    public:
        Controller(){}

        void start(){
        // Crear un objeto SerialStream
        SerialPort serial_port;

        // Intentar abrir el puerto serial
        try {
            serial_port.Open("/dev/ttyACM0");  // Cambia a tu puerto serial
        } catch (const OpenFailed&) {
            entry = 'u';
        }

        // Configurar las propiedades del puerto serial
        serial_port.SetBaudRate(BaudRate::BAUD_9600);
        serial_port.SetCharacterSize(CharacterSize::CHAR_SIZE_8);
        serial_port.SetParity(Parity::PARITY_NONE);
        serial_port.SetStopBits(StopBits::STOP_BITS_1);
        serial_port.SetFlowControl(FlowControl::FLOW_CONTROL_NONE);

        // Verificar si el puerto serial está abierto
        if (!serial_port.IsOpen()) {
            entry = 'u';
        }

        // Leer e imprimir datos del puerto serial
        while (playing) {
            try{
                char data;
                serial_port.ReadByte(data);
                if(data == 'w' || data == 'a' || data == 's' || data == 'd' || data == 'e' || data == 'c' || data == 'v'){
                    entry = data;
                }
            }catch (const ReadTimeout&) {
                entry = 'u';
            } catch (const NotOpen&) {
            std::cerr << "Error: Intentando leer de un puerto serial no abierto." << std::endl;
            break;
        }
        }
        

        // Cerrar el puerto serial antes de salir
        serial_port.Close();
        }

        void startThread(){
            
        }
};