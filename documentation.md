# Mini- Documentación del avance del Trabajo Práctico Final
## ¿Qué necesito hacer para ejecutar las aplicaciones de cliente y servidor? 

### Compilar
Ingresar al directorio donde se encuentra el proyecto.
Para instalar las dependencias necesarias para que el proyecto compile ejecutar.
````bash
./scripts/install_depedencies.sh
````

Si por alguna razón no puedes ejecutar el script debido a restricciones de acceso, ejecuta el siguiente comando para darle permisos de ejecución, y luego intenta nuevamente instalar las dependencias:
````bash
chmod +x scripts/install_depedencies.sh
````

Una vez instaladas las dependencias se debe compilar el proyecto ejecutando el siguiente comando.
````bash
make
````

### Ejecucion del servidor
Para iniciar el juego, es requerido levantar primero el servidor. Para esto se debe ejecutar:

Si te encuentras en el directorio principal del proyecto, navega al directorio de compilación:
````bash
cd build
````
Luego ejecuta el servidor con el siguiente comando:
````bash
./taller_server
````

Si ya estás en el directorio build, puedes ejecutar directamente:
````bash
./taller_server
````

### Ejecucion del cliente
Una vez iniciado el servidor, ya es posible iniciar uno o mas clientes. Para esto se debe ejecutar.

Si te encuentras en el directorio principal del proyecto, navega al directorio build:
````bash
cd build
````
Luego ejecuta el cliente con el siguiente comando:
````bash
./taller_client
````

Si ya estás en el directorio build, simplemente ejecuta:
````bash
./taller_client
````

## Qué acciones puede realizar un usuario como cliente gráfico y cómo
* Al ejecutar la app de cliente el usuario debe introducir su nickname que será visible para otros jugadores, luego serás redirigido a un menú, donde podrás unirte a una partida existente o crear una nueva. Cada partida puede tener un máximo de 5 jugadores, y comenzará cuando el jugador que la creó decida iniciar. Para que la partida comience, deben estar al menos el creador y un jugador más.
* El jugador creador de cada partida es quien decide cuando esta deja de esperar por más jugadores, dando inicio a esta.
* Una vez iniciada la partida todos los jugadores se ubicarán en el mundo del primer game que finaliza cuando solo quede un jugador vivo, siendo que cada jugador (por ahora) aparece con una arma (una pistola cowboy). Dentro del mundo de cada game, puedes controlar a tu personaje con las siguientes teclas:
  * 'A': Desplazarse hacia la izquierda.
  * 'D': Desplazarse hacia la derecha.
  * 'F': Disparar.
  * Espaciadora: Saltar.
* A continuación se irán repitiendo games hasta que haya un jugador ganador de toda la partida según el criterio establecido por la cátedra.

## Requerimientos faltantes  a fecha 19/11/24

* Falta incluir en el modelo del mundo en el juego las cajas y los spawn places para las armas/armaduras/cascos (items colectables), por lo cual los patos no pueden recoger/dejar items de/en el mundo del juego, entonces inicialmente ya tienen una arma en la mano (pistola cowboy).
* Falta las funcionalidades de tirarse al suelo y aletear. 

* Falta mostrar entre cada grupo de games un marcador con las rondas ganadas por cada participante.

* No se incluyó nada relativo al editor de niveles, cheats ni Unit tests.

## ¿Qué sabemos de antemano que está mal?
* El cierre ordenado del sevridor.
* El cierre ordenado del cliente frente a la desconexión del  servidor.
* Frente a la desconexión de un jugador partície de una partida ya iniciada no se está sacando del modelo al duck del mismo.

