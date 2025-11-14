# Linked Lists (Listas Enlazadas)

## 📌 Definición

Una **Linked List** es una estructura de datos lineal donde los elementos (nodos) no están almacenados en posiciones contiguas de memoria. Cada nodo contiene:

1. **Datos** (el valor que almacena)
2. **Puntero** al siguiente nodo (o `nullptr` si es el último)

A diferencia de los arrays, las listas enlazadas permiten inserciones y eliminaciones eficientes en cualquier posición, pero no tienen acceso aleatorio (no puedes acceder directamente al elemento en la posición `i`).

---

## 🏗️ Tipos de Listas Enlazadas

### 1. **Singly Linked List (Lista Simplemente Enlazada)**

- Cada nodo apunta **solo al siguiente**
- Recorrido unidireccional (head → tail)
- Implementación que usamos en este proyecto

```
[10|•]-->[20|•]-->[30|•]-->nullptr
 head              tail
```

### 2. **Doubly Linked List (Lista Doblemente Enlazada)**

- Cada nodo tiene punteros `next` y `prev`
- Recorrido bidireccional
- Más memoria, pero más flexible

```
nullptr<--[•|10|•]<-->[•|20|•]<-->[•|30|•]-->nullptr
          head                     tail
```

### 3. **Circular Linked List**

- El último nodo apunta al primero (no hay `nullptr`)
- Útil para colas circulares

---

## 🔑 Conceptos Clave

### **Node (Nodo)**

El bloque básico de construcción:

```cpp
struct Node {
    T data;       // Valor almacenado
    Node* next;   // Puntero al siguiente nodo
};
```

**¿Por qué usar `struct`?**

- En C++, `struct` y `class` son casi idénticos (la única diferencia es que `struct` es pública por defecto)
- Para nodos simples, `struct` es convencional y más legible

### **Head y Tail**

- **`head`**: Puntero al primer nodo (punto de entrada)
- **`tail`**: Puntero al último nodo (optimiza `push_back`)

**¿Por qué mantener `tail`?**

- Sin `tail`: `push_back()` sería O(n) (tendríamos que recorrer toda la lista)
- Con `tail`: `push_back()` es O(1)

```cpp
Node* head;  // Siempre apunta al inicio
Node* tail;  // Siempre apunta al final
```

### **Manejo de Memoria**

Las listas enlazadas **requieren gestión manual de memoria** (en C++ sin smart pointers):

```cpp
// Crear un nodo
Node* newNode = new Node(value);  // Asignación dinámica

// Destruir un nodo
delete current;  // Liberar memoria
```

**Importante:**

- Cada `new` debe tener su correspondiente `delete`
- El destructor `~LinkedList()` debe liberar **todos** los nodos
- Olvidar `delete` → **memory leak** (fuga de memoria)

---

## ⚙️ Complejidad de Operaciones

| Operación            | Complejidad | Explicación                              |
| -------------------- | ----------- | ---------------------------------------- |
| `push_front()`       | **O(1)**    | Solo actualizamos `head`                 |
| `push_back()`        | **O(1)**    | Gracias a `tail`                         |
| `pop_front()`        | **O(1)**    | Solo actualizamos `head`                 |
| `pop_back()`         | **O(n)**    | Debemos recorrer hasta el penúltimo nodo |
| `insert(pos)`        | **O(n)**    | Debemos llegar a la posición             |
| `erase(pos)`         | **O(n)**    | Debemos llegar a la posición             |
| `find(value)`        | **O(n)**    | Búsqueda lineal                          |
| `clear()`            | **O(n)**    | Debemos eliminar cada nodo               |
| Acceso directo `[i]` | **O(n)**    | No existe acceso aleatorio               |

---

## 🎯 Ventajas vs Desventajas

### ✅ Ventajas

1. **Inserción/eliminación eficiente** en el inicio O(1)
2. **Tamaño dinámico** (crece/decrece según necesidad)
3. **No requiere memoria contigua** (funciona bien con memoria fragmentada)
4. **No hay redimensionamiento costoso** (como en `std::vector`)

### ❌ Desventajas

1. **No hay acceso aleatorio** (no puedes hacer `list[5]` en O(1))
2. **Mayor uso de memoria** (cada nodo tiene overhead del puntero: 8 bytes en sistemas de 64 bits)
3. **Mala localidad de caché** (los nodos están dispersos en memoria)
4. **Gestión manual de memoria** (riesgo de leaks si no se hace bien)

---

## 🧪 Casos de Uso Comunes

### 1. **Implementar Stacks y Queues**

```cpp
// Stack: push_front() + pop_front() = O(1)
// Queue: push_back() + pop_front() = O(1)
```

### 2. **Deshacer/Rehacer (Undo/Redo)**

- Navegación bidireccional en historial

### 3. **Representar polinomios**

```cpp
// 3x^2 + 5x + 7 → [3,2] -> [5,1] -> [7,0]
```

### 4. **Problemas de LeetCode/HackerRank**

- Detectar ciclos (Floyd's algorithm)
- Invertir listas
- Encontrar el medio de la lista
- Merge de listas ordenadas

---

## 🔧 Implementación Detallada

### **Constructor**

```cpp
LinkedList() : head(nullptr), tail(nullptr), ssize_t(0) {}
```

- Inicializa `head` y `tail` a `nullptr` (lista vacía)
- **¿Por qué `nullptr` y no `NULL`?** `nullptr` es type-safe en C++11+

### **Destructor**

```cpp
~LinkedList() {
    clear();
}
```

- **Crítico:** Libera toda la memoria al destruir el objeto
- Sin esto → memory leak garantizado

### **push_back() - Insertar al final**

```cpp
void push_back(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;  // Lista vacía: head y tail apuntan al mismo nodo
    } else {
        tail->next = newNode;   // Enlazar el último nodo al nuevo
        tail = newNode;         // Actualizar tail
    }
    ++ssize_t;
}
```

**Paso a paso:**

1. Crear nuevo nodo en el heap
2. Si la lista está vacía → el nuevo nodo es head y tail
3. Si no → enlazar el actual `tail` al nuevo nodo y actualizar `tail`

**Visualización:**

```
Antes:  [10]-->[20]-->nullptr
         head   tail

Llamar: push_back(30)

Después: [10]-->[20]-->[30]-->nullptr
         head          tail
```

### **push_front() - Insertar al inicio**

```cpp
void push_front(const T& value) {
    Node* node = new Node(value);
    node->next = head;  // El nuevo nodo apunta al actual head
    head = node;        // Actualizar head
    if (!tail) {        // Si era lista vacía
        tail = node;
    }
    ++ssize_t;
}
```

**¿Por qué verificar `tail`?**

- Si la lista estaba vacía, `tail` también debe apuntar al nuevo nodo

**Visualización:**

```
Antes:  [10]-->[20]-->nullptr
         head   tail

Llamar: push_front(5)

Después: [5]-->[10]-->[20]-->nullptr
        head          tail
```

### **clear() - Limpiar toda la lista**

```cpp
void clear() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;  // Guardar el siguiente ANTES de delete
        delete cur;              // Liberar memoria del nodo actual
        cur = next;              // Avanzar
    }
    head = tail = nullptr;
    ssize_t = 0;
}
```

**¿Por qué guardar `next` antes de `delete`?**

- Una vez que haces `delete cur`, no puedes acceder a `cur->next`
- Guardar `next` primero evita acceder a memoria liberada (undefined behavior)

**Visualización del proceso:**

```
Inicio: [10]-->[20]-->[30]-->nullptr
         cur

Paso 1: next = cur->next;  // next apunta a [20]
        delete cur;         // Libera [10]
        cur = next;         // cur ahora apunta a [20]

Paso 2: next = cur->next;  // next apunta a [30]
        delete cur;         // Libera [20]
        cur = next;         // cur ahora apunta a [30]

Paso 3: next = cur->next;  // next es nullptr
        delete cur;         // Libera [30]
        cur = next;         // cur es nullptr, termina el while

Final: head = tail = nullptr;
```

### **print() - Visualizar la lista**

```cpp
void print() const {
    Node* cur = head;
    std::cout << "[";
    while (cur) {
        std::cout << cur->data;
        if (cur->next) std::cout << " -> ";
        cur = cur->next;
    }
    std::cout << "]\n";
}
```

**Salida ejemplo:**

```
[5 -> 10 -> 20]
```

---

## 🐛 Errores Comunes y Debugging

### 1. **Memory Leak (Fuga de Memoria)**

```cpp
// ❌ MAL: No liberar memoria
void clear() {
    head = nullptr;  // ¡Los nodos siguen en memoria!
}

// ✅ BIEN: Liberar cada nodo
void clear() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
}
```

### 2. **Olvidar actualizar `tail`**

```cpp
// ❌ MAL
void push_back(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;  // ¡Falta actualizar tail!
    }
}

// ✅ BIEN
if (!head) {
    head = tail = newNode;
}
```

### 3. **Acceder a nodo después de `delete`**

```cpp
// ❌ MAL
delete cur;
cur = cur->next;  // ¡Undefined behavior! cur ya fue liberado

// ✅ BIEN
Node* next = cur->next;
delete cur;
cur = next;
```

### 4. **No verificar lista vacía**

```cpp
// ❌ MAL
T front() {
    return head->data;  // ¡Crash si head es nullptr!
}

// ✅ BIEN
T front() {
    if (!head) throw std::out_of_range("List is empty");
    return head->data;
}
```

### 5. **Confusión con el nombre de la variable size**

```cpp
// 🤔 NAMING MEJORABLE en tu implementación actual
size_t ssize_t;  // Confuso: parece un tipo, no una variable

// ✅ MEJOR
size_t size_;    // Convención común en C++
```

---

## 🎓 Patrones de Algoritmos con Linked Lists

### 1. **Two Pointers (Fast & Slow)**

Encontrar el nodo del medio:

```cpp
Node* findMiddle() {
    if (!head) return nullptr;
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;  // slow apunta al medio
}
```

**¿Por qué funciona?**

- `fast` avanza el doble de rápido que `slow`
- Cuando `fast` llega al final, `slow` está en el medio

### 2. **Reverse (Invertir lista)**

```cpp
void reverse() {
    Node* prev = nullptr;
    Node* current = head;
    tail = head;  // El antiguo head será el nuevo tail

    while (current) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}
```

**Visualización:**

```
Original: [1]-->[2]-->[3]-->nullptr

Invertida: nullptr<--[1]<--[2]<--[3]
                              head
```

### 3. **Detectar ciclo (Floyd's Cycle Detection)**

```cpp
bool hasCycle() {
    if (!head) return false;
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;  // Hay ciclo
    }
    return false;
}
```

**Analogía:** Dos corredores en una pista circular. Si hay ciclo, el más rápido alcanzará al lento.

### 4. **Merge de dos listas ordenadas**

```cpp
static Node* mergeTwoLists(Node* l1, Node* l2) {
    Node dummy(0);
    Node* tail = &dummy;

    while (l1 && l2) {
        if (l1->data < l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
```

---

## 📚 Problemas Recomendados de LeetCode

### Easy

| #   | Título                                                                                                  | Concepto clave       |
| --- | ------------------------------------------------------------------------------------------------------- | -------------------- |
| 206 | [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)                               | Inversión básica     |
| 21  | [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)                         | Merge con dummy node |
| 83  | [Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) | Two pointers         |
| 141 | [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)                                   | Floyd's algorithm    |
| 876 | [Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/)                   | Fast & slow pointers |

### Medium

| #   | Título                                                                                      | Concepto clave                |
| --- | ------------------------------------------------------------------------------------------- | ----------------------------- |
| 2   | [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)                           | Carry handling                |
| 19  | [Remove Nth Node From End](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) | Two pointers con gap          |
| 142 | [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)                 | Floyd + matemáticas           |
| 143 | [Reorder List](https://leetcode.com/problems/reorder-list/)                                 | Find middle + reverse + merge |
| 328 | [Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/)                 | Separar y concatenar          |

### Hard

| #   | Título                                                                              | Concepto clave              |
| --- | ----------------------------------------------------------------------------------- | --------------------------- |
| 25  | [Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/) | Reverse en bloques          |
| 23  | [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)         | Min heap o divide & conquer |

---

## 🔍 Comparación: Linked List vs Array/Vector

| Característica            | Linked List       | Array/Vector           |
| ------------------------- | ----------------- | ---------------------- |
| **Acceso aleatorio**      | O(n)              | O(1) ⭐                |
| **Inserción al inicio**   | O(1) ⭐           | O(n)                   |
| **Inserción al final**    | O(1) con tail ⭐  | O(1) amortizado ⭐     |
| **Eliminación al inicio** | O(1) ⭐           | O(n)                   |
| **Eliminación al final**  | O(n)              | O(1) ⭐                |
| **Memoria**               | No contigua       | Contigua ⭐            |
| **Cache locality**        | Mala              | Buena ⭐               |
| **Overhead por elemento** | 8 bytes (puntero) | Casi 0 ⭐              |
| **Redimensionamiento**    | No necesario ⭐   | Costoso ocasionalmente |

**Regla general:**

- Usa **arrays/vectors** si necesitas acceso aleatorio frecuente o iterar mucho
- Usa **linked lists** si haces muchas inserciones/eliminaciones al inicio

---

## 🛠️ Tips para Debugging

### 1. **Dibuja en papel**

```
Antes de codear, dibuja:
[10|•]-->[20|•]-->[30|•]-->nullptr
 ^        ^        ^
 head              tail
```

### 2. **Print statements**

```cpp
void debug_print() {
    Node* cur = head;
    int i = 0;
    while (cur) {
        std::cout << "Node " << i << ": data=" << cur->data
                  << ", next=" << cur->next << "\n";
        cur = cur->next;
        i++;
    }
}
```

### 3. **Valgrind (detector de memory leaks)**

```bash
# Compilar con símbolos de debug
g++ -g -std=c++17 debug_linked_list.cpp -o debug

# Ejecutar con valgrind
valgrind --leak-check=full ./debug
```

### 4. **GDB breakpoints**

```bash
gdb ./debug_linked_list
(gdb) break push_back
(gdb) run
(gdb) print *head
(gdb) print *tail
```

---

## 📖 Recursos Adicionales

- [C++ Reference - std::list](https://en.cppreference.com/w/cpp/container/list)
- [GeeksforGeeks - Linked List](https://www.geeksforgeeks.org/data-structures/linked-list/)
- [Visualgo - Linked List Visualization](https://visualgo.net/en/list)
- [LeetCode - Linked List Study Plan](https://leetcode.com/study-plan/linked-list/)

---

## 🎯 Estructura de este módulo

- **`include/ds/LinkedList.hpp`**: Implementación de la estructura
- **`src/playground/debug_linked_list.cpp`**: Playground para experimentar
- **`tests/ds/test_linked_list_ds.cpp`**: Tests unitarios (próximamente)
- **`src/platforms/leetcode/`**: Problemas resueltos usando LinkedList

**Cómo usar:**

```bash
cd build
cmake ..
cmake --build . --target debug_linked_list
./debug_linked_list
```

---

**Recuerda:** La mejor forma de aprender listas enlazadas es **dibujándolas en papel**. Dibuja los nodos, los punteros, y sigue el flujo de cada operación paso a paso. ¡Pon breakpoints en VS Code y observa cómo cambian `head`, `tail` y los punteros `next`!
