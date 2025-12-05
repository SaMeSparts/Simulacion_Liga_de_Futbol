# Evidencia de Problemas de Programación

**LeetCode Perfil:** [SaMesparts](https://leetcode.com/u/SaMesparts/)  


## Problemas Resueltos

### 1. Minimum Replacements to Sort the Array (Hard)
**Problema:** [LeetCode 2366](https://leetcode.com/problems/minimum-replacements-to-sort-the-array/)  
**Video Explicativo:** [Ver en YouTube](https://youtu.be/R9hlPIqlQU8)  
**Solución:** [Ver Solución](https://leetcode.com/problems/minimum-replacements-to-sort-the-array/submissions/1820940051)

## Análisis y Fundamentación Teórica (Relación con Ordenamiento)

### 1. Definición del Problema como Ordenamiento
Aunque este problema no utiliza comparaciones e intercambios (swaps) tradicionales como *Bubble Sort* o *Quicksort*, su fundamento teórico es la **satisfacción de la Propiedad de Orden No Decreciente**.
Matemáticamente, buscamos transformar el arreglo tal que se cumpla la condición:
$$nums[i] \leq nums[i+1]$$
para todo $0 \leq i < n-1$.

### 2. Estrategia de Solución: Propagación de Restricciones
La relación con los algoritmos de ordenamiento reside en la técnica de **recorrido inverso** (de derecha a izquierda).

* **Analogía con Insertion Sort/Bubble Sort:** Al igual que en algoritmos clásicos donde la parte "ordenada" se construye progresivamente (generalmente al final del arreglo), aquí establecemos un **sufijo ordenado válido**.
* **El Invariante:** Al iterar desde `n-2` hasta `0`, garantizamos que el elemento actual `nums[i]` sea compatible con el elemento ya procesado a su derecha (`nums[i+1]` o `next`). El valor `next` actúa como una **cota superior** (upper bound) estricta.

### 3. Lógica Greedy vs. Swapping
En un ordenamiento tradicional, si encontramos una inversión ($nums[i] > nums[i+1]$), intercambiamos posiciones. En este problema, la "inversión" se resuelve **dividiendo** el elemento $nums[i]$.

* Si $nums[i] > next$: Existe una violación del orden.
* **Acción:** Dividimos $nums[i]$ en $k$ partes.
* **Optimización (Greedy):** Para afectar lo menos posible a los elementos restantes a la izquierda (y facilitar su ordenamiento), el nuevo valor límite (`next`) debe ser **el máximo posible** resultante de esa división.
    * Fórmula: `next = nums[i] / parts`.

Esta estrategia asegura que el arreglo resultante cumpla la propiedad de estar ordenado ascendentemente con el mínimo costo computacional.

**Código Principal:**
```cpp
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        long long ops = 0;
        int n = nums.size();
        long long next = nums[n - 1]; // último elemento
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] > next) {
                long long parts = (nums[i] + next - 1) / next; // ceil division
                ops += parts - 1; 
                next = nums[i] / parts; // nuevo valor máximo permitido
            } else {
                next = nums[i];
            }
        }
        return ops;
    }
};

```

### 2. Balanced Binary Tree (Easy)
**Problema:** [LeetCode 110](https://leetcode.com/problems/balanced-binary-tree/)  
**Video Explicativo:** [Ver en YouTube](https://youtu.be/u8_72xqOl8o)  
**Solución:** [Ver Solución](https://leetcode.com/problems/balanced-binary-tree/submissions/1820939492)

**Análisis y Estrategia:**
Un árbol está balanceado si la diferencia de alturas entre subárboles izquierdo y derecho no es mayor a 1.
* Utilicé DFS (Depth First Search) con un enfoque `Bottom-Up` para eficiencia O(n).
* En lugar de calcular la altura repetidamente, la función retorna la altura si el subárbol es válido, o -1 si encuentra un desbalance.
* Si recibimos un -1 de cualquier hijo, propagamos el -1 inmediatamente hacia arriba, evitando cálculos innecesarios.

**Código Principal:**

```cpp
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return height(root) != -1;
    }
private:
    int height(TreeNode* node) {
        if (node == nullptr) return 0;
        int leftH = height(node->left);
        if (leftH == -1) return -1;
        int rightH = height(node->right);
        if (rightH == -1) return -1;
        if (std::abs(leftH - rightH) > 1) return -1;
        return 1 + std::max(leftH, rightH);
    }
};

```
### 3. Product of Array Except Self (Medium)
**Problema:** [LeetCode 238](https://leetcode.com/problems/product-of-array-except-self/)  
**Video Explicativo:** [Ver en YouTube](https://youtu.be/se3ruMbBCMs)  
**Solución:** [Ver Solución](https://leetcode.com/problems/product-of-array-except-self/submissions/1820940298)

## Análisis y Estrategia: Product of Array Except Self

### Descripción del Problema
El objetivo es transformar un arreglo de entrada `nums` en un arreglo de salida `answer` donde cada elemento `answer[i]` es igual al producto de todos los elementos de `nums` excepto `nums[i]`.

**Restricciones Críticas:**
1.  **Sin División:** No se permite calcular el producto total y dividir entre el elemento actual (esto fallaría si hay ceros).
2.  **Tiempo Lineal:** La solución debe ejecutarse en $O(N)$.

### Estrategia de Solución: Prefijos y Sufijos
Para resolver el problema sin división, descomponemos el cálculo en dos partes. Para cualquier posición `i`, el resultado deseado es:
$$Resultado[i] = (Producto_{izquierda}) \times (Producto_{derecha})$$

Implementamos un algoritmo de **Doble Barrido (Two-Pass Approach)**:

1.  **Primer Barrido (Forward Pass - Prefijos):**
    * Iteramos de izquierda a derecha ($0 \rightarrow N-1$).
    * Calculamos el producto acumulado de todos los números anteriores a la posición actual.
    * Almacenamos estos valores en el arreglo de respuesta.

2.  **Segundo Barrido (Backward Pass - Sufijos):**
    * Iteramos de derecha a izquierda ($N-1 \rightarrow 0$).
    * Mantenemos una variable acumuladora (`rightProduct`) que lleva el producto de todos los números posteriores a la posición actual.
    * Multiplicamos el valor que ya existía en el arreglo (prefijo) por el valor de la variable acumuladora (sufijo) para obtener el resultado final.

### Análisis de Complejidad

* **Complejidad Temporal:** $O(N)$.
    * Realizamos dos iteraciones lineales independientes sobre el arreglo. Como no hay bucles anidados, el tiempo de ejecución escala linealmente con el tamaño de la entrada.
* **Complejidad Espacial:** $O(1)$ (Auxiliar).
    * Aparte del arreglo de salida (que no cuenta como espacio extra según el enunciado), solo utilizamos variables escalares (`leftProduct`, `rightProduct`, `i`, `n`) para el control de flujo. No utilizamos estructuras de datos adicionales como matrices o listas auxiliares.

**Código Principal:**

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> answer(n);
        
        int leftProduct = 1;
        // Primer pase: productos a la izquierda
        for (int i = 0; i < n; i++) {
            answer[i] = leftProduct;
            leftProduct *= nums[i];
        }
        
        int rightProduct = 1;
        // Segundo pase: productos a la derecha
        for (int i = n - 1; i >= 0; i--) {
            answer[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        
        return answer;
    }
};
```

---

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

---

