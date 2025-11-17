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
5. La tabla general se ordena utilizando un algoritmo de ordenamiento eficiente, como QuickSort o `std::sort` de C++ (Introsort).

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

Se utiliza una **lista doblemente ligada** para la carga inicial de los 18 equipos. La razón principal es la eficiencia de inserción: al leer el archivo `equipos.csv`, cada equipo se añade al final de la lista (`cola`) en tiempo constante **O(1)**, haciendo que la carga total de los `n` equipos sea **O(n)**.

Para operaciones posteriores que requieren acceso aleatorio o reordenamiento complejo (como la **simulación de jornadas y la ordenación de la tabla**), los datos se copian temporalmente a un `std::vector`. Esta es una decisión de diseño pragmática que permite usar algoritmos de la STL altamente optimizados (`std::rotate`, `std::sort`) que operan de manera más eficiente sobre la memoria contigua de un vector.

### Selecciona un algoritmo de ordenamiento adecuado al problema

Para organizar la tabla de posiciones se utiliza `std::sort` de C++, que implementa **Introsort**, una combinación de QuickSort, HeapSort e InsertionSort.
- En los primeros niveles de recursión utiliza QuickSort por su velocidad promedio O(n log n).
- Si la recursión es muy profunda (indicador de peor caso), cambia a HeapSort para garantizar O(n log n).
- Para pequeños subconjuntos, usa InsertionSort, optimizando el rendimiento.

De esta forma, se garantiza una complejidad estable y eficiente en todos los escenarios. Las funciones donde se usa el ordenamiento se encuentran en `liga.h`, dentro de la parte que genera la tabla general.

---

## SICT0301B: Evalúa los componentes

Presenta casos de prueba correctos y completos para todas las funciones y procedimientos del programa:
- Casos de prueba para simular todas las jornadas.
- Casos de prueba para actualizar correctamente estadísticas de equipos.
- Casos de prueba para ordenar la tabla de posiciones.
- Casos de prueba para reiniciar la liga.

Hace un análisis de complejidad correcto y completo de los componentes del programa:

**Lista doblemente ligada (Análisis de la estructura)**
- **Inserción (al final/inicio):**
  - Mejor caso: O(1)
  - Promedio: O(1)
  - Peor caso: O(1)
- **Eliminación (al final/inicio):**
  - Mejor caso: O(1)
  - Promedio: O(1)
  - Peor caso: O(1)
- **Búsqueda (por nombre):**
  - Mejor caso: O(1) (Si es el primer nodo)
  - Promedio: O(n)
  - Peor caso: O(n) (Si es el último o no existe)
- **Reinicio de estadísticas (Función `reiniciarLiga`):** O(n), donde n = 18 equipos.

**Ordenamiento de tabla (`std::sort` / Introsort)**
- Mejor caso: **O(n log n)**
- Promedio: O(n log n)
- Peor caso: O(n log n), garantizado por el cambio interno a HeapSort.

**Simulación de jornadas**
- Generación de una jornada (9 partidos): O(n)
- Generación de todas las jornadas (Función `simularLiga`): O(n^2)

---

## SICT0303B: Implementa acciones científicas

Implementa mecanismos para consultar información de las estructuras de manera correcta y útil dentro del programa:
- Se puede visualizar la tabla general ordenada en tiempo real.
- Se pueden consultar los resultados de cualquier jornada simulada.
- Se puede reiniciar la liga y volver a simular una nueva temporada desde cero.

Implementa mecanismos de lectura y escritura de archivos para manejar datos de forma eficiente:
- Los equipos se cargan desde el archivo `equipos.csv` al iniciar la simulación.
- Los resultados de **todos los partidos** se guardan en `resultados.csv`.
- La **tabla general de posiciones** generada se guarda en `tabla_general.csv`.
- Estos archivos permiten mantener la información entre ejecuciones y facilitan la validación de datos.
