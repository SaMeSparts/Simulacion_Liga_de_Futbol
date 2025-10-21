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

## Estructuras y algoritmos utilizados

- `vector<Equipo>` para almacenar los 18 equipos.  
- `struct Jornada` con un `vector<Partido>` para almacenar los partidos de cada jornada.  
- Ordenamiento de la tabla usando `std::sort` o QuickSort, según conveniencia.  
- Opcional: `unordered_map<string,int>` para acceso rápido por nombre de equipo.  

**Análisis de complejidad:**

- Simulación de una jornada (9 partidos): O(N)  
- Simulación de todas las jornadas (17): O(N * J) ≈ O(N) para N = 18  
- Ordenamiento de tabla: O(N log N) usando `std::sort`  
- Búsqueda de equipo por nombre: O(N) lineal o O(1) usando `unordered_map`

---

## Avance 1 - SICT

**SICT0301: Evalúa los componentes**  
- Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

**SICT0302: Toma decisiones**  
- Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

---

## Avance 2 - SICT

**SICT0301: Evalúa los componentes**  
- Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.

**SICT0302: Toma decisiones**  
- Selecciona una estructura de datos adecuada al problema y la usa correctamente.

**SICT0303: Implementa acciones científicas**  
- Implementa mecanismos para consultar información de las estructuras de manera correcta.  
- Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

---

## Estructura del proyecto

