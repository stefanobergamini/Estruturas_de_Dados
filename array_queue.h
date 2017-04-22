// "Copyright [2017] Stefano Bergamini"

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! Classe que representa uma estrutura dados estilo fila
class ArrayQueue {
 public:
    //! Construtor Padrão
    ArrayQueue() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        size_ = -1;
    }
    //! Contrutor
    explicit ArrayQueue(std::size_t max) {
        max_size_ =  max;
        contents = new T[max_size_];
        size_ = -1;
    }

    ~ArrayQueue() {
        delete[] contents;
    }
    //! inicio do metodo enfileira
    void enqueue(const T& data) {
        if (full()) {
            throw std::out_of_range("Fila cheia");
        }
        size_ += 1;
        contents[size_] = data;
    }
    //! Inicio do metodo de desenfileirar
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
        } else {
            T temp = contents[0];
            for (int i = 0; i < size_; i++) {
                contents[i] = contents[i + 1];
            }
            size_--;
            return(temp);
        }
    }
    //! inicio do metodo que informa o valor
    T& back() {
        if (empty()) {
            throw std::out_of_range("Fila Vazia");
        } else {
            return(contents[size_]);
        }
    }
    //! inicio do metodo que informa o valor
    void clear() {
        size_ = -1;
    }
    //! inicio do metodo que retorna o tamanho atual da fila
    std::size_t size() {
        return(size_ + 1);
    }
    //! inicio do metodo que retorna o tamanho maximo da fila
    std::size_t max_size() {
        return(max_size_);
    }
    //! inicio do metodo informa se a fila esta vazia
    bool empty() {
        if (size_ == -1) {
            return(true);
        } else {
            return(false);
        }
    }
    //! inicio do metodo informa se a fila esta cheia
    bool full() {
        if (size_ == (max_size_ - 1)) {
            return(true);
        } else {
            return(false);
        }
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif
