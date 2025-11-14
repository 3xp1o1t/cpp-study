# Arrays

## ¿Qué es un Array?

Un **array** es una colección de elementos del mismo tipo almacenados en posiciones consecutivas de memoria. Cada elemento se accede mediante un índice (normalmente empezando en 0).

### Características principales

- **Acceso directo**: O(1) para leer/escribir en un índice conocido.
- **Tamaño fijo** (C-arrays): `int arr[10];` → 10 enteros, tamaño definido en compilación.
- **Tamaño dinámico** (C++ STL): `std::vector<int>` → crece automáticamente.
- **Localidad de referencia**: Elementos consecutivos en memoria → cache-friendly.

---

## Operaciones comunes

| Operación                   | C-style array        | `std::vector`          | Complejidad     |
| --------------------------- | -------------------- | ---------------------- | --------------- |
| Acceso por índice           | `arr[i]`             | `vec[i]` / `vec.at(i)` | O(1)            |
| Insertar al final           | N/A (fijo)           | `vec.push_back(x)`     | O(1) amortizado |
| Insertar en medio           | N/A                  | `vec.insert(it, x)`    | O(n)            |
| Eliminar del final          | N/A                  | `vec.pop_back()`       | O(1)            |
| Buscar elemento (sin orden) | Recorrer linealmente | `std::find`            | O(n)            |
| Buscar (ordenado)           | `binary_search`      | `std::binary_search`   | O(log n)        |

---

## Ventajas

- Acceso rápido O(1) si conoces el índice.
- Simple y ampliamente compatible.
- Bajo overhead de memoria (sin punteros extra como listas enlazadas).

## Desventajas

- Inserción/eliminación en medio es costosa O(n).
- C-arrays tienen tamaño fijo.
- `std::vector` puede realocar memoria cuando crece (invalidando punteros/iteradores).

---

## Patrones comunes en problemas de LeetCode/HackerRank

### 1. **Two Pointers (Dos punteros)**

Usados en arrays ordenados o para detectar pares/tripletas:

```cpp
// Ejemplo: encontrar dos números que suman target (array ordenado)
vector<int> twoSumSorted(const vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) return {left, right};
        else if (sum < target) left++;
        else right--;
    }
    return {};
}
```

### 2. **Sliding Window (Ventana deslizante)**

Para subarrays contiguos de longitud variable o fija:

```cpp
// Ejemplo: suma máxima de k elementos consecutivos
int maxSumK(const vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return 0;

    int windowSum = 0;
    for (int i = 0; i < k; i++) windowSum += arr[i];

    int maxSum = windowSum;
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}
```

### 3. **Prefix Sum (Suma de prefijos)**

Precalcula sumas acumuladas para consultas rápidas de subarrays:

```cpp
// prefixSum[i] = suma desde arr[0] hasta arr[i-1]
vector<int> buildPrefixSum(const vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    return prefix;
}

// Suma desde arr[L] hasta arr[R] (inclusive)
int rangeSum(const vector<int>& prefix, int L, int R) {
    return prefix[R + 1] - prefix[L];
}
```

### 4. **Kadane's Algorithm (subarray de suma máxima)**

Para encontrar la subsecuencia contigua con suma máxima:

```cpp
int maxSubarraySum(const vector<int>& nums) {
    int maxSoFar = nums[0], maxEndingHere = nums[0];
    for (size_t i = 1; i < nums.size(); i++) {
        maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}
```

### 5. **In-place manipulation (manipulación sin memoria extra)**

Modificar el array sin usar O(n) espacio extra:

```cpp
// Ejemplo: remover duplicados de un array ordenado in-place
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int writeIdx = 1;
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[i - 1]) {
            nums[writeIdx++] = nums[i];
        }
    }
    return writeIdx;
}
```

---

## Tips para debugging

- **Imprimir arrays**: Usa un loop o `std::copy` con `ostream_iterator`.
- **Verificar límites**: Cuidado con `arr[n]` cuando el último índice válido es `n-1`.
- **Usa `vec.at(i)` en debug**: Lanza excepción si `i` está fuera de rango (mejor que `vec[i]` que puede dar UB).
- **Visualiza con breakpoints**: En VS Code, inspecciona `vec` en el depurador para ver todos los elementos.

---

## Problemas recomendados (LeetCode)

| #   | Título                              | Dificultad | Patrón principal        |
| --- | ----------------------------------- | ---------- | ----------------------- |
| 1   | Two Sum                             | Easy       | Hash map / Two pointers |
| 26  | Remove Duplicates from Sorted Array | Easy       | Two pointers in-place   |
| 53  | Maximum Subarray                    | Medium     | Kadane's algorithm      |
| 121 | Best Time to Buy and Sell Stock     | Easy       | One-pass tracking       |
| 238 | Product of Array Except Self        | Medium     | Prefix/Suffix products  |
| 283 | Move Zeroes                         | Easy       | Two pointers in-place   |
| 15  | 3Sum                                | Medium     | Two pointers            |
| 560 | Subarray Sum Equals K               | Medium     | Prefix sum + hash map   |

---

## Recursos adicionales

- [C++ std::vector reference](https://en.cppreference.com/w/cpp/container/vector)
- [LeetCode array tag](https://leetcode.com/tag/array/)
- [GeeksforGeeks Arrays](https://www.geeksforgeeks.org/array-data-structure/)

---

## Estructura de este módulo

- **`include/ds/Array.hpp`**: Estructura de datos Array (wrapper de `std::vector` con utilidades)
- **`src/playground/debug_arrays.cpp`**: Playground para probar la estructura Array
- **`src/playground/debug_array_algorithms.cpp`**: Ejemplos de patrones comunes (two pointers, sliding window, prefix sum, Kadane, etc.)
- **`tests/ds/test_array_ds.cpp`**: Tests unitarios de la estructura
- **`tests/algo/test_arrays.cpp`**: Tests de algoritmos/patrones
- **`src/platforms/leetcode/easy/0001_two_sum.cpp`**: Ejemplo de problema usando la estructura

**Cómo usar**:

```bash
cd build
./debug_arrays              # prueba la estructura ds::Array
./debug_array_algorithms    # demuestra patrones comunes
./tests/unit_tests          # ejecuta todos los tests
```
