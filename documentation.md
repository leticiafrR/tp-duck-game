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


## ¿Qué sabemos de antemano que está mal?
[... aqui se unificará lo que cada uno note en el codigo que escribió]:#

## ¿Qué necesito hacer para ejecutar las aplicaciones de cliente y servidor? 
[... aquí la parte que cande ya hizo]:#
