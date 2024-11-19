# Mini- Documentación del avance del Trabajo Práctico Final
## Requerimientos commpletados a fecha 18/11/24
**Globalmente**
* Se estableció un protocolo consistente para comunicar la información necesaria para cada cliente como para el servidor.\

**Respecto al servidor**
* Se logró levantar un servidor que acepta a múltiples clientes, permitiendo que según lo indicado por cada cliente, se creen nuevas partidas o se vincule a este mismo a alguna creada por algún otro jugador.
* Se permite decidir al jugador owner de cada match (quien la creó) decidir cuándo iniciar esta misma regulando que se inicie siempre con un mínimo de 2 jugadores.
* En caso de un jugador querer unirse a una partida que para ese momento ya inició se rebota al cliente adecauadamente.
* Se sostinenen múltiples partidas independientes que realizan los broadcasts necesarios únicamente a los participantes de esta misma.
* Se detecta la desconexión de un cliente y se maneja correctamente si este no alcanzó a unirse a alguna partida de forma exitosa.
* Se detecta la desconexión de un cliente que ya se había unido a una partida y se maneja de forma parcial: se lo saca de los jugadores a quienes se les hace broadcast
  
[... aquí más sobre la parte del modelo, las fisicas implementadas, la generacion de snapshots, etc...]:#


**Respecto al cliente gráfico**
* Se estableció la estructura multihilo con: un hilo renderizador e hilos de comunicación de manera que el proceso de renderizado no se bloquee. 
* Se perciben los comandos introducidos por teclado por el usuario, se codifican y envían según lo establecido por el protocolo al servidor.
* ...
## Requerimientos faltantes 
[... aqui la se unificará lo que cada uno mencione que es con lo que se topó que faltaba]:#
* Falta testear correctamente el cierre ordenado del servidor.
* Frente a la desconexión de un cliente que se unió a una partida aún no se saca a su personaje del modelo (figuraría como un personaje que no hace nada pues no se le envian actualizaciones del juego ni se toman comandos de este).
* Usar archivos YAML, para todas las configuraciones.



## ¿Qué sabemos de antemano que está mal?
[... aqui se unificará lo que cada uno note en el codigo que escribió]:#
* El cierre ordenado del sevridor.

## ¿Qué necesito hacer para ejecutar las aplicaciones de cliente y servidor? 

# Compilar
Ingresar al directorio donde se encuentra el proyecto.
Para instalar las dependencias necesarias para que el proyecto compile ejecutar.
'''bash
./install_depenencies.sh
'''

Si por alguna razón no puedes ejecutar el script debido a restricciones de acceso, ejecuta el siguiente comando para darle permisos de ejecución, y luego intenta nuevamente instalar las dependencias:
'''bash
chmod +x nombre_del_archivo.sh
'''

Una vez instaladas las dependencias se debe compilar el proyecto ejecutando el siguiente comando.
'''bash
make
'''

# Ejecucion del servidor
Para iniciar el juego, es requerido inciar el servidor antes que los clientes. Para esto se debe ejecutar:

Si te encuentras en el directorio principal del proyecto, navega al directorio de compilación:
'''bash
cd build
'''
Luego ejecuta el servidor con el siguiente comando:
'''bash
./taller_server
'''

Si ya estás en el directorio build, puedes ejecutar directamente:
'''bash
./taller_server
'''

# Ejecucion del cliente
Una vez iniciado el servidor, ya es posible iniciar uno o mas clientes. Para esto se debe ejecutar.

Si te encuentras en el directorio principal del proyecto, navega al directorio build:
'''bash
cd build
'''
Luego ejecuta el cliente con el siguiente comando:
'''bash
./taller_client
'''

Si ya estás en el directorio build, simplemente ejecuta:
'''bash
./taller_client
'''

## Ingresar al juego

Para unirte a una partida, primero debes ingresar un nombre (nickname) y hacer clic en 'Start'. Es importante señalar que este nombre no es utilizado por el servidor para identificarte como jugador, sino solo para que otros jugadores puedan reconocerte durante la partida.

Una vez que ingreses tu nombre, serás redirigido al lobby, donde podrás unirte a una partida existente o crear una nueva. Cada partida puede tener un máximo de 5 jugadores, y comenzará cuando el jugador que la creó decida iniciar. Para que la partida comience, deben estar al menos el creador y un jugador más.
Controles del jugador

Durante la partida, puedes controlar a tu personaje con las siguientes teclas:

* 'A': Desplazarse hacia la izquierda.
* 'D': Desplazarse hacia la derecha.
* 'R': Disparar.
* Espaciadora: Saltar.

# Rondas y Ganador

Una partida consta de 5 rondas. El ganador es el jugador que haya ganado la mayor cantidad de rondas. Para ganar una ronda, debes ser el último jugador sobreviviente. Si al final de las 5 rondas no hay un ganador claro (es decir, si varios jugadores tienen la misma cantidad de rondas ganadas), se continuará a otra partida, también con 5 rondas.