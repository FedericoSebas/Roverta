## Rover de Exploración

Este proyecto se centra en un rover de exploración que se divide en dos secciones principales: el controlador de motores y la estación meteorológica.

### Controlador de Motores

El controlador de motores es responsable de la locomoción del rover. Permite al rover moverse y navegar por su entorno.

### Estación Meteorológica

La estación meteorológica es controlada por un ESP32 y utiliza varios sensores para recopilar datos sobre el entorno. Los sensores incluyen:

- **Fotodiodo y LDR (Resistencia Dependiente de la Luz)**: Estos son sensores analógicos que miden la intensidad de la luz. El fotodiodo es sensible a la luz visible y cercana al infrarrojo, mientras que el LDR cambia su resistencia en función de la cantidad de luz que recibe.

- **DHT22**: Este es un sensor digital de temperatura y humedad. Puede medir temperaturas entre -40 y 80 grados Celsius, y humedad relativa entre 0 y 100%.

- **BMP280**: Este es un sensor digital que puede medir la presión barométrica y la temperatura. La presión barométrica se puede utilizar para calcular la altitud, lo que puede ser útil para determinar la posición del rover.

![Diagrama del Rover](./hardware/weather-station/schema/Schema.pdf)

## Software

El software proporcionado incluye la biblioteca MQTT creada por nuestro equipo, así como bibliotecas individuales para cada dispositivo que se relacionan con MQTT. Esto se debe a que cada dispositivo tiene una callback para topicos y suscripciones, por lo que es más claro qué topico está relacionado con cada dispositivo.

Esperamos que este proyecto sea de su interés y le invitamos a explorar más a fondo el código y las funcionalidades del rover.