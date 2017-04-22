// "Copyright [2017] Stefano Bergamini"

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
/*!
    Classe que representa uma estrutura dados estilo pilha
*/
class ArrayStack {
 public:
    //! Construtor padrão
    ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        top_ = -1;
    }
    //! Contrutor
    explicit ArrayStack(std::size_t max) {
        max_size_ =  max;
        contents = new T[max_size_];
        top_ = -1;
    }

    ~ArrayStack() {
        delete[] contents;
    }
    //! inicio do metodo empilha
    void push(const T& data) {
        if (full()) {
            throw std::out_of_range("Pilha cheia");
        }
        top_ += 1;
        contents[top_] = data;
    }  //! Fim do metodo empilha
    //! Inicio do metodo de desempilha
    T pop() {
        if (empty()) {
            throw std::out_of_range("Pilha Vazia");
        } else {
            top_--;
            return(contents[top_ + 1]);
        }
    }  //! Fim do metodo desempilha
    //! inicio do metodo que informa o valor
    T& top() {
        if (empty()) {
            throw std::out_of_range("Pilha Vazia");
        } else {
            return(contents[top_]);
        }
    }
    //! inicio do metodo que limpa a pilha
    void clear() {
        top_ = -1;
    }     // limpa
    //! inicio do metodo que retorna o tamanho atual da pilha
    std::size_t size() {
        return(top_ + 1);
    }  //! tamanho
    //! inicio do metodo que retorna o tamanho maximo da pilha
    std::size_t max_size() {
        return(max_size_);
    }
    //! inicio do metodo informa se a pilha esta vazia
    bool empty() {
        if (top_ == -1) {
            return(true);
        } else {
            return(false);
        }
    }  //! vazia
    //! inicio do metodo que informa se a pilha esta cheia
    bool full() {
        if (top_ == max_size_ - 1) {
            return(true);
        } else {
            return(false);
        }
    }  //! cheia

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  //! namespace structures

#endif
