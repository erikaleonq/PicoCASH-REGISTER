# PICOCASH REGISTER: GESTIÓN ELECTRÓNICA DE VENTAS

## IDEA PROYECTO FINAL

   Para el proyecto final se quiere hacer un modelo de caja registradora electrónica utilizando la Raspberry Pi Pico y el lenguaje de programación C, el sistema manejará información en tiempo real de los productos que el cliente desee adquirir, tales como su precio y su peso, en caso de requerirlo. La caja registradora contará con autenticación de usuarios, en el caso del cliente se verificará si es miembro del establecimiento, por medio de su número de identificación, lo que le otorgará un porcentaje de descuento en su compra. También existirán usuarios administradores, los cuales tendrán permisos exclusivos en el sistema, como agregar nuevos usuarios de vendedores, estos usuarios vendedores, tendrán otros tipos de permisos como la apertura y cierre de la caja y la creación de nuevos usuarios miembros del establecimiento.
   Por otra parte, el sistema PicoCash contará con una base de datos para el manejo de inventario, el cual tendrá diferentes funcionalidades. Cuando el usuario identificado sea un vendedor y se pase uno de los productos este se descontará automáticamente del inventario. Si el usuario es administrador podrá ver y agregar productos al inventario. 

## REQUISITOS FUNCIONALES.
   
   •	Procesamiento de datos: El vendedor escanea una tarjeta RFID en representación de un producto, en caso de que se necesiten registrar varios productos, se podrá seleccionar el numero en el teclado, sin necesidad de pasar cada uno por el lector. El sistema reconoce el producto y muestra su ID y precio en la pantalla LCD. Si el producto es pesable, frutas o verduras, el usuario coloca el producto en la pesa. El sistema mide el peso y lo muestra en la pantalla junto con el precio. 
    
   •	Control: Inicialmente, se debe ingresar las credenciales de un encargado para activar el sistema, ya sea administrador o un vendedor. Cuando el sistema registra una transacción completa (cuando se presiona la tecla enter) permite la apertura de la caja y muestra en pantalla el total y el cambio una vez el vendedor ingresa la cantidad de dinero proporcionada por el cliente.
   
   •	Gestión de energía: Se define un botón para poner en reposo la caja (Modo de bajo consumo) mientras espera que se ingresen las credenciales de un encargado para volver a iniciarse.
   
   •	Interfaz de usuarios: La interacción entre el usuario y el sistema se da principalmente con el teclado y la pantalla LCD, permitiendo así inicializar el sistema, gestionar inventario o realizar una venta y visualizando lo que se está haciendo en la pantalla.

## REQUISITOS NO FUNCIONALES
   
   •	Fiabilidad: Teniendo en cuenta que la mayoría de los componentes electrónicos que se usarán para el proyecto ya se han estudiado con anterioridad, y que estos tienen una alta adaptabilidad con la Raspberry Pi Pico, se espera que el sistema completo tenga una baja probabilidad de fallo. 
    
   •	Usabilidad: El sistema está diseñado para un público muy específico (Administrador o vendedor), por lo que la navegación en el mismo necesitará una capacitación básica sobre sus funcionalidades, ya que la interfaz en sí es amigable con el usuario y sencilla de utilizar.
   
   •	Consumo de energía: Ya que el sistema no cuenta con componentes electrónicos que demanden alto consumo de corriente, el consumo de energía del mismo será mínimo.
   
   •	Tiempo de respuesta: La caja registradora debe responder rápidamente a las acciones del usuario, como escanear productos o calcular el total.
   
   •	Seguridad: Se implementará un sistema de autenticación para los empleados, administrador o vendedor, que operan la caja registradora.

## COMPONENTES

   
   |Componente                                                                   |Precio      |
   |-----------------------------------------------------------------------------|------------|
   |Solenoide                                                                    | $ 12.799,64|
   |Celda de carga 5Kg                                                           | $  15.232  |
   |Módulo driver Celda de Carga                                                 | $  4.284|
   |Kit Lector/Escritor RFID MFRC522                                             | $ 10.805,20|
   |Tarjeta inteligente sin contacto                                             | $  5.471,62|
   |Teclado matricial de membrana de 20 teclas                                   | $  9.647,33|
   |Display LCD caracteres 4x20 Azul                                             | $ 18.599,70|
   |Implementos electrónicos básicos (cables, transistores, resistencias, etc.)	|          -|
   |Materiales para montaje físico	                                             |          -|
   |TOTAL ESTIMADO                                                               | $ 150000|


## INTEGRANTES
   
   Erika Dayana León Quiroga - CC 1007848726
    
   Juan Pablo Sepúlveda Sánchez - CC 1007291927
    
   Esteban Rodriguez Ordonñez - CC 1061817922
   

## FUNCIONES DE CADA INTEGRANTE

   Erika Dayana León Quiroga: Planeación general del proyecto, asignación de tareas, codificación de flujos.
   
   Juan Pablo Sepúlveda Sánchez: Conexiones y planeación de montajes, codificación de módulos.
   
   Esteban Rodriguez Ordoñez: Codificación de módulos y flujos del proyecto.
   
## CRONOGRAMA

## DIAGRAMA DE FLUJO 

 ![diagramaDeFlujo](https://github.com/erikaleonq/PicoCASH-REGISTER/assets/80007851/3a40b7e9-eda6-4382-ad0d-62a01c5a5b67)

## DIAGRAMA DE BLOQUES DE HARDWARE

   ![Diagrama de bloques PICOca$h drawio](https://github.com/erikaleonq/PicoCASH-REGISTER/assets/80007851/ee0b0f2d-1cb5-47c1-9eee-597e333ff782)

   ### LCD 16x4
   
   Para llevar a cabo el montaje del hardware, se procederá a conectar inicialmente una pantalla LCD 16x4. Se utilizará el controlador desarrollado en prácticas anteriores o, en su defecto, se empleará una interfaz I2C para simplificar la conexión. En este proceso, se emplearán los mismos 6 pines de conexión, distribuidos de la siguiente manera: 4 pines para la transmisión de datos y los 2 pines restantes para el control de la pantalla LCD.
   La asignación de pines será crucial para asegurar una conexión adecuada. Los 4 pines de datos permitirán la transmisión de la información necesaria para la visualización en la pantalla, mientras que los 2 pines de control serán esenciales para gestionar las funciones específicas de la LCD, como la habilitación, la lectura/escritura y la selección de comandos o datos.
   
   ### TECLADO MATRICIAL 
   
   En la conexión del teclado, se utilizará el firmware desarrollado durante las prácticas de laboratorio como punto de partida. Sin embargo, será necesario realizar algunas adaptaciones para acomodarse a las especificaciones del nuevo teclado, que cuenta con una fila adicional. Además, se llevará a cabo la integración del uso de interrupciones para mejorar la eficiencia y la capacidad de respuesta del sistema.
   El ajuste del firmware se centrará en la modificación de las rutinas de lectura del teclado para manejar la fila adicional de manera adecuada, asegurando la compatibilidad y el correcto funcionamiento con el nuevo hardware. Además, la incorporación de interrupciones en el firmware permitirá al sistema detectar de manera inmediata y responder eficientemente a eventos generados por el teclado. Esto optimizará el rendimiento general, ya que el procesador podrá atender rápidamente las señales del teclado sin la necesidad de un constante escaneo manual. La implementación de interrupciones contribuirá a una mejor gestión de recursos y una mayor capacidad de respuesta del sistema en general.
   
   ### RFID
   
   El lector RFID está equipado con varios protocolos de comunicación, entre los que se incluyen UART, I2C y SPI. Cada uno de estos protocolos posee sus propias particularidades y ventajas distintivas. Actualmente, no se ha tomado una decisión definitiva sobre cuál de estos protocolos utilizar. Por lo tanto, se planifica realizar pruebas exhaustivas para evaluar y determinar cuál de ellos se adapta de manera óptima a los requisitos específicos del sistema. Este proceso de pruebas es esencial para seleccionar el protocolo que garantice un rendimiento eficiente y una integración efectiva del lector RFID a nuestro proyecto.
   
 ### CELDA DE CARGA
   
   La conexión de la celda de carga al amplificador se realiza mediante los dos cables de salida de la celda. El amplificador de instrumentación, a su vez, cuenta con pines de entrada diseñados para recibir la señal de la celda de carga y pines de salida destinados a la conexión con la Raspberry Pi Pico. La salida del amplificador de instrumentación suele ser una señal analógica.
   Dado que la Raspberry Pi Pico carece de entradas analógicas directas, será necesario utilizar las entradas ADC (convertidor analógico a digital) del microcontrolador para leer la señal analógica proveniente del amplificador de instrumentación. Este proceso permitirá que la Raspberry Pi Pico interprete los datos generados por la celda de carga a través del amplificador.
   Por lo tanto, será esencial configurar y emplear las entradas ADC de la Raspberry Pi Pico para leer y procesar la señal analógica proveniente del amplificador de instrumentación conectado a la celda de carga. Esta adaptación posibilitará la adquisición precisa de datos analógicos y su posterior procesamiento digital por parte de la Raspberry Pi Pico, facilitando la integración efectiva de la celda de carga en el sistema.
