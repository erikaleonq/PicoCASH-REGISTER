# ProyectoFinalED3

PICOCASH REGISTER: GESTIÓN ELECTRÓNICA DE VENTAS

1. IDEA PROYECTO FINAL
Para el proyecto final se quiere hacer un modelo de caja registradora electrónica utilizando la Raspberry Pi Pico y el lenguaje de programación C, el sistema manejará información en tiempo real de los productos que el cliente desee adquirir, tales como su precio y su peso, en caso de requerirlo. La caja registradora contará con autenticación de usuarios, en el caso del cliente se verificará si es miembro del establecimiento, por medio de su número de identificación, lo que le otorgará un porcentaje de descuento en su compra. También existirán usuarios administradores, los cuales tendrán permisos exclusivos en el sistema, como agregar nuevos usuarios de vendedores, estos usuarios vendedores, tendrán otros tipos de permisos como la apertura y cierre de la caja y la creación de nuevos usuarios miembros del establecimiento.
Por otra parte, el sistema PicoCash contará con una base de datos para el manejo de inventario, el cual tendrá diferentes funcionalidades. Cuando el usuario identificado sea un vendedor y se pase uno de los productos este se descontará automáticamente del inventario. Si el usuario es administrador podrá ver y agregar productos al inventario. 

2. REQUISITOS FUNCIONALES.
•	Procesamiento de datos: El vendedor escanea una tarjeta RFID en representación de un producto, en caso de que se necesiten registrar varios productos, se podrá seleccionar el numero en el teclado, sin necesidad de pasar cada uno por el lector. El sistema reconoce el producto y muestra su ID y precio en la pantalla LCD. Si el producto es pesable, frutas o verduras, el usuario coloca el producto en la pesa. El sistema mide el peso y lo muestra en la pantalla junto con el precio. 
 
•	Control: Inicialmente, se debe ingresar las credenciales de un encargado para activar el sistema, ya sea administrador o un vendedor. Cuando el sistema registra una transacción completa (cuando se presiona la tecla enter) permite la apertura de la caja y muestra en pantalla el total y el cambio una vez el vendedor ingresa la cantidad de dinero proporcionada por el cliente.

•	Gestión de energía: Se define un botón para poner en reposo la caja (Modo de bajo consumo) mientras espera que se ingresen las credenciales de un encargado para volver a iniciarse.

•	Interfaz de usuarios: La interacción entre el usuario y el sistema se da principalmente con el teclado y la pantalla LCD, permitiendo así inicializar el sistema, gestionar inventario o realizar una venta y visualizando lo que se está haciendo en la pantalla.

3. REQUISITOS NO FUNCIONALES
•	Fiabilidad: Teniendo en cuenta que la mayoría de los componentes electrónicos que se usarán para el proyecto ya se han estudiado con anterioridad, y que estos tienen una alta adaptabilidad con la Raspberry Pi Pico, se espera que el sistema completo tenga una baja probabilidad de fallo. 
 
•	Usabilidad: El sistema está diseñado para un público muy específico (Administrador o vendedor), por lo que la navegación en el mismo necesitará una capacitación básica sobre sus funcionalidades, ya que la interfaz en sí es amigable con el usuario y sencilla de utilizar.

•	Consumo de energía: Ya que el sistema no cuenta con componentes electrónicos que demanden alto consumo de corriente, el consumo de energía del mismo será mínimo.

•	Tiempo de respuesta: La caja registradora debe responder rápidamente a las acciones del usuario, como escanear productos o calcular el total.

•	Seguridad: Se implementará un sistema de autenticación para los empleados, administrador o vendedor, que operan la caja registradora.

4. COMPONENTES

Solenoide $12.799,64
Celda de carga 5Kg $15.232
Módulo driver Celda de Carga $4.284
Kit Lector/Escritor RFID MFRC522 $10.805,20
Tarjeta inteligente sin contacto $5.471,62
Teclado matricial de membrana de 20 teclas $9.647,33
Display LCD caracteres 4x20 Azul $18.599,70
Implementos electrónicos básicos (cables, transistores, resistencias, etc.)	-
Materiales para montaje físico	-
TOTAL ESTIMADO $150000


5. INTEGRANTES
Erika Dayana León Quiroga - CC 1007848726
Juan Pablo Sepúlveda Sánchez - CC 1007291927
Esteban Rodriguez Ordonñez - CC 1061817922



