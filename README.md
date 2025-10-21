# Simulación de Liga de Fútbol

Este proyecto consiste en la simulación de una liga de fútbol con 18 equipos, similar a la Liga MX, en una vuelta completa de 17 jornadas.  
El programa genera partidos y resultados aleatorios, actualiza las estadísticas de cada equipo y permite al usuario decidir qué visualizar: la tabla general, resultados de una jornada específica o reiniciar la liga para comenzar una nueva temporada.

---

## Funcionamiento del programa

1. El usuario inicia el programa.  
2. Decide si quiere simular la liga completa.  
3. Una vez simuladas todas las jornadas, puede:
   - Consultar los resultados de cualquier jornada (1–17).  
   - Ver la tabla general de posiciones ordenada por puntos, diferencia de goles y goles a favor.  
   - Reiniciar la liga para volver a simular una nueva temporada.  
4. Todos los resultados de los partidos son generados de manera aleatoria.  
5. La tabla general se ordena utilizando un algoritmo de ordenamiento eficiente, como QuickSort o `std::sort` de C++.

---

## Descripción de funcionalidades

- Registro de 18 equipos con estadísticas: puntos, goles a favor, goles en contra y diferencia de goles.  
- Simulación automática de 17 jornadas completas.  
- Visualización de la tabla de posiciones general y resultados de cada jornada.  
- Menú interactivo que permite simular, consultar jornadas, ver la tabla general y reiniciar la liga.  
- Ordenamiento de la tabla según criterios: puntos, diferencia de goles, goles a favor y nombre del equipo.

---

## SICT0302B: Toma decisiones

### Selecciona y usa una estructura lineal adecuada al problema
Se utiliza un `vector<Equipo>` para almacenar los 18 equipos porque permite acceder rápidamente a cada equipo mediante índices y facilita recorrerlos para actualizar estadísticas tras cada partido.  
Cada equipo es un objeto que contiene nombre, puntos, goles a favor, goles en contra y diferencia de goles.  
Los elementos se pueden actualizar y reiniciar usando funciones del programa como simular jornada, actualizar estadísticas y reiniciar liga.

### Selecciona un algoritmo de ordenamiento adecuado al problema
Para organizar la tabla de posiciones se utiliza `std::sort` de C++, que implementa Introsort (mezcla de QuickSort y HeapSort). Esto permite ordenar los equipos por puntos, diferencia de goles y goles a favor de manera eficiente.  
Las funciones donde se usa el ordenamiento se encuentran en `liga.cpp` en las funciones que generan la tabla general.

### Uso de árbol o estructura adicional (opcional)
No se requiere un BST para este proyecto, pero si se deseara buscar equipos por rangos de puntos o por estadísticas rápidamente, se podría implementar un `unordered_map` o un árbol balanceado.

---

## SICT0301B: Evalúa los componentes

Presenta casos de prueba correctos y completos para todas las funciones y procedimientos del programa:  
- Casos de prueba para simular todas las jornadas.  
- Casos de prueba para actualizar correctamente estadísticas de equipos.  
- Casos de prueba para ordenar la tabla de posiciones.  
- Casos de prueba para reiniciar la liga.  

Hace un análisis de complejidad correcto y completo de los componentes del programa:

**Lista de equipos (vector)**  
- Acceso por índice: O(1)  
- Actualización de estadísticas: O(1) por equipo  
- Reinicio de estadísticas: O(N), N = 18

**Ordenamiento de tabla (std::sort / Introsort)**  
- Complejidad promedio: O(N log N)  
- Peor caso: O(N log N) garantizado por Introsort

**Simulación de jornadas**  
- Generación de una jornada (9 partidos): O(N)  
- Generación de todas las jornadas (17): O(N * 17) ≈ O(N) para N = 18

---

## SICT0303B: Implementa acciones científicas

Implementa mecanismos para consultar información de las estructuras de manera correcta y útil dentro del programa:  
- El usuario puede buscar información de cada equipo por índice o nombre.  
- Se puede visualizar la tabla general ordenada.  
- Se puede consultar los resultados de cualquier jornada simulada.  
- Se puede reiniciar la liga y simular nuevamente.

Implementa mecanismos de lectura de archivos para cargar datos a las estructuras:  
- En futuras versiones, los equipos pueden cargarse desde un archivo `equipos.csv`.  
- Los resultados de jornadas y la tabla general pueden guardarse en CSV para análisis posterior.  

Implementa mecanismos de escritura de archivos para guardar datos de manera correcta:  
- Las jornadas simuladas y la tabla de posiciones se podrían guardar al final de un archivo CSV, de modo que no sea necesario recapturar la información cada vez que se corre el programa.

---

