#include <iostream>
#include "ds/Array.hpp"

using namespace std;
using namespace ds;

int main() {
    cout << "=== Array Data Structure - Playground ===\n\n";

    // 1. Construcción y acceso básico
    {
        cout << "1. Construcción y acceso básico\n";
        Array<int> arr1;  // vacío
        Array<int> arr2(5);  // 5 elementos con valor por defecto
        Array<int> arr3(3, 10);  // [10, 10, 10]
        Array<int> arr4 = {1, 2, 3, 4, 5};  // initializer list
        
        arr4.print("arr4");
        cout << "size: " << arr4.size() << "\n";
        cout << "arr4[0]: " << arr4[0] << "\n";
        cout << "arr4.front(): " << arr4.front() << "\n";
        cout << "arr4.back(): " << arr4.back() << "\n\n";
    }

    // 2. Modificación de elementos
    {
        cout << "2. Modificación de elementos\n";
        Array<int> arr = {10, 20, 30, 40, 50};
        arr.print("original");
        
        arr[2] = 99;
        arr.print("después de arr[2] = 99");
        
        arr.push_back(60);
        arr.print("después de push_back(60)");
        
        arr.pop_back();
        arr.print("después de pop_back()");
        cout << "\n";
    }

    // 3. Insert y erase
    {
        cout << "3. Insert y erase\n";
        Array<int> arr = {1, 2, 4, 5};
        arr.print("original");
        
        arr.insert(2, 3);  // insertar 3 en índice 2
        arr.print("después de insert(2, 3)");
        
        arr.erase(0);  // eliminar primer elemento
        arr.print("después de erase(0)");
        cout << "\n";
    }

    // 4. Utilidades de búsqueda
    {
        cout << "4. Utilidades de búsqueda\n";
        Array<int> arr = {10, 20, 30, 20, 40, 20};
        arr.print("arr");
        
        int idx = arr.find(30);
        cout << "find(30): " << idx << "\n";
        
        size_t cnt = arr.count(20);
        cout << "count(20): " << cnt << "\n\n";
    }

    // 5. Operaciones in-place
    {
        cout << "5. Operaciones in-place\n";
        Array<int> arr = {5, 2, 8, 1, 9};
        arr.print("original");
        
        arr.reverse();
        arr.print("después de reverse()");
        
        arr.sort();
        arr.print("después de sort()");
        
        arr.fill(7);
        arr.print("después de fill(7)");
        cout << "\n";
    }

    // 6. Iteradores (uso con STL)
    {
        cout << "6. Iteradores (uso con STL)\n";
        Array<int> arr = {1, 2, 3, 4, 5};
        arr.print("arr");
        
        cout << "Usando range-based for: ";
        for (const auto& val : arr) {
            cout << val << " ";
        }
        cout << "\n\n";
    }

    // 7. Manejo de errores con at()
    {
        cout << "7. Manejo de errores con at()\n";
        Array<int> arr = {1, 2, 3};
        arr.print("arr");
        
        try {
            cout << "arr.at(1): " << arr.at(1) << "\n";
            cout << "arr.at(10): ";
            cout << arr.at(10) << "\n";  // lanzará excepción
        } catch (const std::out_of_range& e) {
            cout << "Excepción capturada: " << e.what() << "\n";
        }
        cout << "\n";
    }

    cout << "=== Fin del playground ===\n";
    return 0;
}
