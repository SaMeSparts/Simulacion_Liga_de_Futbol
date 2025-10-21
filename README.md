# Simulación de Liga de Fútbol

Este proyecto simula una liga de fútbol con 18 equipos (modelo Liga MX) en una sola vuelta de 17 jornadas.  
El sistema genera partidos y marcadores de manera aleatoria, actualiza las estadísticas de los equipos y permite al usuario decidir qué visualizar: simular la liga completa, ver la tabla general, revisar los resultados de cualquier jornada ya simulada o reiniciar la liga.

---

## Flujo de uso / Ejemplo de funcionamiento

1. El usuario inicia el programa.  
2. El usuario elige si quiere simular la liga completa.  
   - Si elige simular, el programa genera aleatoriamente los resultados de las 17 jornadas (cada jornada contiene 9 partidos, dado que hay 18 equipos).  
3. Tras simular todas las jornadas, el usuario puede:
   - Seleccionar una jornada específica (1..17) para ver sus partidos y resultados.
   - Volver al menú principal y elegir ver la **tabla general** (posición acumulada después de todas las jornadas).
   - **Reiniciar la liga** (borrar todas las jornadas y estadísticas acumuladas).
4. Todas las simulaciones producen resultados aleatorios.  
5. La tabla general se ordena usando un algoritmo de ordenamiento (recomendado: `std::sort` / QuickSort o Introsort; ver sección “Estructuras y algoritmos” para detalles).

---

## Descripción del avance (nueva funcionalidad)

En esta versión se ha implementado:

- Ajuste para **18 equipos** (estructura y validaciones).  
- Simulación de una **vuelta completa** (17 jornadas).  
- **Generación aleatoria** de marcadores por partido.  
- Almacenamiento de las 17 jornadas para poder revisarlas posteriormente.  
- **Menú interactivo** donde el usuario puede:
  - Simular la liga completa.
  - Seleccionar y ver cualquier jornada (1–17).
  - Ver la tabla de posiciones general.
  - **Reiniciar la liga** (borrar jornadas y estadísticas).
- Ordenamiento de la tabla por puntos y criterios de desempate.

---

## Estructuras y algoritmos utilizados

### Representación principal de datos

- `struct Equipo`  
  - `string nombre`  
  - `int puntos`  
  - `int golesAFavor`  
  - `int golesEnContra`  
  - `int diferencia`  
- `struct Partido`  
  - `int idLocal`, `int idVisitante` (índices en el vector de equipos)  
  - `int golesLocal`, `int golesVisitante`  
- `using Jornada = vector<Partido>`  
- `vector<Equipo> equipos`  — lista de 18 equipos.  
- `vector<Jornada> calendario` — tamaño 17; cada `Jornada` contiene 9 partidos.

Esta organización (vectores de objetos) facilita indexado, recorrido y serialización a CSV si se requiere.

### Algoritmo de ordenamiento recomendado

**Opción 1 — Usar `std::sort` (recomendado):**  
- `std::sort` implementa *Introsort* (quicksort + heapsort + insertion sort), que ofrece:
  - Complejidad promedio: `O(n log n)`
  - Peor caso garantizado: `O(n log n)`
  - Implementación robusta y optimizada en la STL
- Recomendación: usar `std::sort(equipos.begin(), equipos.end(), cmp)` donde `cmp` compara:
  1. Puntos (descendente)
  2. Diferencia de goles (descendente)
  3. Goles a favor (descendente)
  4. (Opcional) Nombre (alfabético) para estabilidad determinística

**Opción 2 — Implementar QuickSort propio:**  
- Complejidad promedio: `O(n log n)`  
- Peor caso: `O(n²)` (evitable si se usa pivote aleatorio o particionado aleatorio)  
- Si se implementa, recomiendo usar *randomized pivot* o mezclar con heapsort para evitar degeneración.

**Elección recomendada:** `std::sort` (Introsort) — es la opción más segura, con mejor rendimiento promedio y sin riesgo práctico de peor caso, además de ser fácil de usar.

---

## Almacenamiento de jornadas y operaciones típicas

- Simular liga completa:
  - Generar las 17 jornadas completas y guardarlas en `calendario`.
  - Actualizar las estadísticas en `equipos` tras cada partido.
- Ver jornada `k`:
  - Mostrar la lista de 9 partidos con sus resultados en `calendario[k-1]`.
- Ver tabla general:
  - Ordenar copia de `equipos` con `std::sort` usando `cmp`.
  - Mostrar posición, puntos, GF, GC, diferencia.
- **Reiniciar liga:**
  - Vaciar `calendario` y reiniciar estadísticas de `equipos` a 0.
  - Permite volver a simular una nueva temporada desde cero.

---

## Casos de prueba y validación

- `pruebas.cpp` debe incluir pruebas para:
  - Generación de calendario (17 jornadas con 9 partidos cada una, sin repetir emparejamientos por jornada de forma inválida).  
  - Simulación de partidos y acumulación correcta de estadísticas (puntos y goles).  
  - Ordenamiento correcto de la tabla según criterios.  
  - Visualización de jornadas y reinicio de liga.

---

## Análisis de complejidad

**N = número de equipos (aquí N = 18)**

- Generar una jornada (9 partidos) y actualizar estadísticas por jornada: `O(N)` (recorrer cada partido y actualizar dos equipos).  
- Simular todas las 17 jornadas: `O(N * J)` con `J = 17` → `O(N)` en práctica (constante por diseño de la liga).  
- Ordenamiento de la tabla: `O(N log N)` si se usa `std::sort` (recomendado).  
- Búsqueda de un equipo por nombre (si se implementa lineal): `O(N)`; se puede acelerar con `unordered_map<string, int>` para `O(1)` promedio.

---

## SICT0302B: Toma decisiones

### Selección y uso de estructura lineal adecuada
Se utiliza un `vector<Equipo>` para almacenar los 18 equipos por facilidad de indexado, iteración y compatibilidad con algoritmos STL (`std::sort`). Para acceso rápido por nombre, se puede mantener además un `unordered_map<string, int>` que mapea nombre → índice en el vector.

### Selección de algoritmo de ordenamiento adecuado
Se recomienda `std::sort` (Introsort) por su rendimiento y robustez (`O(n log n)` promedio y peor caso). Si se desea implementar QuickSort propio, hacerlo con pivote aleatorio para mitigar el peor caso.

### Uso de árbol o estructura adicional (opcional)
No es necesario un BST para el problema base con 18 equipos. Sin embargo, si se quisiera soportar consultas por rangos de puntos o búsquedas frecuentes por métricas, se podría usar un árbol balanceado (AVL/Red-Black) o un multimap. Para el alcance actual, `vector` + `unordered_map` + `std::sort` es suficiente.

---

## SICT0301B: Evalúa los componentes

### Casos de prueba
- Pruebas en `pruebas.cpp` para:
  - Correcta simulación y acumulación de puntos/goles.
  - Ordenamiento por puntos/diferencia/goles a favor.
  - Visualización de jornadas y reinicio de liga.

### Análisis de complejidad (resumen)
- Acceso por índice al vector: `O(1)`  
- Búsqueda por nombre (lineal): `O(n)` (mejor con `unordered_map` → `O(1)` promedio)  
- Ordenamiento con `std::sort`: `O(n log n)`.

---

## SICT0303B: Implementa acciones científicas

### Mecanismos de consulta
- Buscar equipo por nombre (opción de menú).  
- Mostrar reporte de la tabla ordenada.  
- Mostrar resultados completos de cualquier jornada simulada.  
- **Reiniciar la liga** y volver a simular.

### Lectura y escritura de archivos
- Lectura: en futuras versiones el programa podrá cargar equipos/estadísticas desde `equipos.csv`.  
- Escritura: guardar calendario y tabla final en CSV para análisis posterior.

---



