# Simulación de Liga de Futbol

Este proyecto consiste en la simulación de una liga de fútbol, donde varios equipos compiten entre sí en partidos generados de manera aleatoria. El sistema permite gestionar la tabla de posiciones de forma dinámica, actualizando los resultados de los equipos y mostrando el ranking de acuerdo con su desempeño durante la temporada.

La simulación incluye la generación automática de partidos entre los equipos participantes. Cada partido asigna aleatoriamente un marcador, el cual influye en el puntaje de cada equipo (victoria, empate o derrota). Con base en estos resultados, el sistema calcula y actualiza la tabla de posiciones.

Para garantizar que la tabla esté siempre organizada y clara, se utilizan algoritmos de ordenamiento básicos en C++, como Bubble Sort o Selection Sort, que permiten ordenar a los equipos de acuerdo con criterios como:

Puntos obtenidos.

Diferencia de goles.

Goles a favor.

De esta manera, la tabla de posiciones refleja en todo momento el desempeño real de los equipos dentro de la simulación.

Además, el sistema incorpora funciones adicionales para:

Mostrar los equipos y sus estadísticas.

Simular jornadas completas de la liga.

Reiniciar la liga para comenzar una nueva temporada.

La información puede guardarse en un archivo de texto llamado Liga.txt, el cual se actualiza solo cuando el usuario selecciona la opción de guardado en el menú. Esto brinda control sobre el momento en que se almacenan los datos y permite conservar el registro de las estadísticas para futuras consultas.

Este proyecto combina la programación estructurada en C++ con el uso de funciones básicas y algoritmos de ordenamiento, ofreciendo una herramienta entretenida y didáctica para comprender cómo se gestiona una liga de fútbol y cómo se aplican conceptos fundamentales de programación.

Descripción del avance 1

En este primer avance, se ha implementado lo siguiente:

Clase Equipo para gestionar la información de cada equipo (nombre, puntos, goles a favor, goles en contra, diferencia de goles).

Clase Liga para manejar el conjunto de equipos y la simulación de partidos.

Funcionalidad para generar partidos aleatorios y actualizar estadísticas de los equipos.

Funcionalidad para mostrar la tabla de posiciones en pantalla.

Implementación de algoritmos de ordenamiento (por puntos y diferencia de goles) para organizar la tabla de posiciones.

