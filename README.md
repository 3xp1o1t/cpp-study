**Descripción**

- **Proyecto:**: Repositorio para estudiar Algoritmos y Estructuras de Datos en C++.
- **Objetivo:**: Mantener implementaciones reutilizables en `include/`, resolver problemas en `src/platforms/` (LeetCode / HackerRank) y organizar notas en `notes/`.

**Quickstart**

- **Clonar:**: ya lo tienes en tu máquina si estás trabajando aquí.
- **Compilar con CMake:**:

```
mkdir -p build
cd build
cmake ..
cmake --build .
```

- **Compilar un archivo individual (rápido):**:

```
g++ -std=c++17 -Iinclude src/platforms/leetcode/easy/0001_two_sum.cpp -o bin/two_sum
./bin/two_sum
```

**Estructura recomendada**

- **`include/ds/`**: Estructuras de datos reutilizables (Array, LinkedList, Stack, Queue, Tree, Graph, etc.). Implementaciones limpias y bien documentadas.
- **`include/algo/`**: Algoritmos y patrones comunes (sorting, searching, two pointers, sliding window, DP, etc.).
- **`src/platforms/`**: Soluciones por plataforma y por dificultad. Cada problema es un archivo `.cpp` independiente que incluye lo necesario desde `include/`.
- **`src/playground/`**: Archivos para depurar y experimentar con estructuras y algoritmos de forma interactiva.
- **`tests/`**: Pruebas unitarias (configurado con GoogleTest via CMake).
- **`notes/`**: Notas en Markdown por tema (arrays, listas enlazadas, grafos, DP, patrones de problema).

**Cómo agregar un problema ejecutable al CMake**

- Edita el `CMakeLists.txt` raíz y añade una entrada `add_executable(...)`:

```
# ejemplo: añadir un problema de LeetCode
add_executable(leetcode_0001 src/platforms/leetcode/easy/0001_two_sum.cpp)
target_include_directories(leetcode_0001 PRIVATE ${CMAKE_SOURCE_DIR}/include)
```

- Luego compila con `cmake --build . --target leetcode_0001` o simplemente `cmake --build .` para todo.

**Tests**

- El proyecto usa **GoogleTest** descargado por CMake (FetchContent). Los tests se encuentran en `tests/` y se compilan en el ejecutable `unit_tests`.
- Para ejecutar tests desde el build:

```bash
cd build
cmake --build . -- -j2
./tests/unit_tests
# o usando filtro para tests nombrados
./tests/unit_tests --gtest_filter="ArrayDSTest.*"
# o usando CTest:
ctest --output-on-failure
```

**Playgrounds (debug interactivo)**

- Los playgrounds en `src/playground/` permiten probar estructuras y algoritmos de forma interactiva con salida en consola.
- Ejemplos disponibles:
  - `debug_arrays` - Prueba la estructura `ds::Array` (construcción, modificación, búsqueda, etc.)
  - `debug_array_algorithms` - Demuestra patrones comunes (two pointers, sliding window, prefix sum, Kadane, etc.)

```bash
cd build
./debug_arrays              # estructura de datos
./debug_array_algorithms    # algoritmos/patrones
```

**Ejemplo rápido de test (GoogleTest)**

- Crea archivos `tests/mi_test.cpp` con contenido similar a:

```cpp
#include <gtest/gtest.h>
TEST(MiTest, EjemploSimple) {
  EXPECT_EQ(1 + 1, 2);
}
```

**Consejos de uso y depuración**

- **Reutiliza:** Implementa estructuras en `include/` y úsalas en `src/` para resolver problemas.
- **Playground:** Usa `src/playground/` para crear pequeños archivos de depuración con breakpoints.
- **VS Code:** Configura `tasks.json` y `launch.json` para compilar y depurar fácilmente (puedo generarlos si quieres).
- **Formato:** Usa `clang-format` si quieres consistencia; no lo agregué por defecto para mantenerlo simple.

**Cómo contribuir nuevas soluciones**

- Añade el archivo `.cpp` en `src/platforms/leetcode/<dificultad>/` o `src/platforms/hackerrank/...`.
- Añade la entrada en `CMakeLists.txt` raíz (ver sección anterior).
- Si tu solución necesita tests, añade un archivo en `tests/` y será recogido por CMake.

**Recursos y recomendaciones**

- **Lenguaje:** C++17 recomendado (control de memoria + STL potente).
- **Testing:** GoogleTest es robusto y similar a frameworks de LeetCode/HackerRank.
- **Patrones:** Anota en `notes/` patrones que repites en problemas (dos-punteros, sliding window, fast-slow pointers, DFS/BFS, DP states).
- **Organización:**
  - **Estructuras de datos** → `include/ds/` (ej: `Array.hpp`, `LinkedList.hpp`)
  - **Algoritmos/Patrones** → `include/algo/` (ej: `array_algorithms.hpp`, `sorting.hpp`)
  - **Problemas de plataformas** → `src/platforms/leetcode/` o `src/platforms/hackerrank/`
  - **Debug/Experimentación** → `src/playground/`
- **Estado actual:**
  - ✅ Estructura `ds::Array` con utilidades (print, sort, reverse, find, etc.)
  - ✅ Algoritmos de arrays: two pointers, sliding window, prefix sum, Kadane, in-place manipulation
  - ✅ Ejemplo LeetCode #1 (Two Sum) usando `ds::Array`
  - ✅ Playgrounds para estructura y algoritmos
  - ✅ 41 tests unitarios (GoogleTest)

Si quieres, puedo generar `tasks.json` / `launch.json` para VS Code y añadir plantillas para nuevos problemas (nombres, comentarios, CMake).
