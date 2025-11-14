#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace ds {

/**
 * @brief Wrapper alrededor de std::vector con utilidades adicionales para estudio
 * 
 * Esta clase encapsula std::vector y añade métodos útiles para debugging,
 * visualización y operaciones comunes en problemas de DSA.
 */
template <typename T>
class Array {
private:
    std::vector<T> data_;

public:
    // ========================================================================
    // Constructores
    // ========================================================================
    
    Array() = default;
    
    explicit Array(size_t size) : data_(size) {}
    
    Array(size_t size, const T& value) : data_(size, value) {}
    
    Array(std::initializer_list<T> init) : data_(init) {}
    
    Array(const std::vector<T>& vec) : data_(vec) {}
    
    // ========================================================================
    // Acceso a elementos
    // ========================================================================
    
    T& operator[](size_t index) {
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        return data_[index];
    }
    
    T& at(size_t index) {
        if (index >= data_.size()) {
            throw std::out_of_range("Array::at() - index out of range");
        }
        return data_[index];
    }
    
    const T& at(size_t index) const {
        if (index >= data_.size()) {
            throw std::out_of_range("Array::at() - index out of range");
        }
        return data_[index];
    }
    
    T& front() { return data_.front(); }
    const T& front() const { return data_.front(); }
    
    T& back() { return data_.back(); }
    const T& back() const { return data_.back(); }
    
    // ========================================================================
    // Capacidad
    // ========================================================================
    
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    void resize(size_t newSize) { data_.resize(newSize); }
    void resize(size_t newSize, const T& value) { data_.resize(newSize, value); }
    void clear() { data_.clear(); }
    
    // ========================================================================
    // Modificadores
    // ========================================================================
    
    void push_back(const T& value) {
        data_.push_back(value);
    }
    
    void push_back(T&& value) {
        data_.push_back(std::move(value));
    }
    
    void pop_back() {
        if (!data_.empty()) {
            data_.pop_back();
        }
    }
    
    void insert(size_t index, const T& value) {
        if (index > data_.size()) {
            throw std::out_of_range("Array::insert() - index out of range");
        }
        data_.insert(data_.begin() + index, value);
    }
    
    void erase(size_t index) {
        if (index >= data_.size()) {
            throw std::out_of_range("Array::erase() - index out of range");
        }
        data_.erase(data_.begin() + index);
    }
    
    // ========================================================================
    // Iteradores (para usar con STL algorithms)
    // ========================================================================
    
    auto begin() { return data_.begin(); }
    auto begin() const { return data_.begin(); }
    auto end() { return data_.end(); }
    auto end() const { return data_.end(); }
    
    // ========================================================================
    // Conversión a std::vector
    // ========================================================================
    
    std::vector<T>& toVector() { return data_; }
    const std::vector<T>& toVector() const { return data_; }
    
    // ========================================================================
    // Utilidades para debugging
    // ========================================================================
    
    /**
     * @brief Imprime el array en formato legible
     */
    void print(const std::string& label = "") const {
        if (!label.empty()) {
            std::cout << label << ": ";
        }
        std::cout << "[";
        for (size_t i = 0; i < data_.size(); i++) {
            std::cout << data_[i];
            if (i + 1 < data_.size()) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    /**
     * @brief Retorna representación string del array
     */
    std::string toString() const {
        std::string result = "[";
        for (size_t i = 0; i < data_.size(); i++) {
            result += std::to_string(data_[i]);
            if (i + 1 < data_.size()) result += ", ";
        }
        result += "]";
        return result;
    }
    
    /**
     * @brief Llena el array con un valor específico
     */
    void fill(const T& value) {
        std::fill(data_.begin(), data_.end(), value);
    }
    
    /**
     * @brief Invierte el array in-place
     */
    void reverse() {
        std::reverse(data_.begin(), data_.end());
    }
    
    /**
     * @brief Ordena el array in-place
     */
    void sort() {
        std::sort(data_.begin(), data_.end());
    }
    
    /**
     * @brief Busca un elemento (retorna índice o -1 si no existe)
     */
    int find(const T& value) const {
        auto it = std::find(data_.begin(), data_.end(), value);
        if (it != data_.end()) {
            return static_cast<int>(std::distance(data_.begin(), it));
        }
        return -1;
    }
    
    /**
     * @brief Cuenta ocurrencias de un valor
     */
    size_t count(const T& value) const {
        return std::count(data_.begin(), data_.end(), value);
    }
};

} // namespace ds
