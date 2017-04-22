// "Copyright [2017] Stefano Bergamini"

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Classe que representa uma estrutura dados estilo lista
class ArrayList {
 public:
    //! contrutor padrao
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
        size_ = 0;
    }
    //! contrutor
    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        contents = new T[max_size_];
        size_ = 0;
    }
    //! destrutor
    ~ArrayList() {
        delete[] contents;
    }
    //! metodo que limpa lista
    void clear() {
        size_ = 0;
    }
    //! metodo que insere no inicio
    void push_back(const T& data) {
        insert(data, size_);
    }
    //! metodo que insere no final
    void push_front(const T& data) {
        insert(data, 0);
    }
    //! metodo que insere no local desejado
    void insert(const T& data, std::size_t index) {
        std::size_t atual;
        if (full())
            throw std::out_of_range("lista cheia");
        if (index > size_)
            throw std::out_of_range("Posição invalida");
        atual = size_;
        while (atual > index) {
            contents[atual] = contents[atual - 1];
            atual--;
        }
        contents[index] = data;
        size_ = size_ + 1;
    }
    //! insere de maneira ordenada
    void insert_sorted(const T& data) {
        std::size_t atual;
        if (full())
            throw std::out_of_range("lista vazia");
        atual = 0;
        while ((atual < size_) && (data > contents[atual])) {
            atual++;
        }
        insert(data, atual);
    }
    //! metodo que retira na posição desejada
    T pop(std::size_t index) {
        std::size_t atual;
        T temp;
        if (index >= size_)
            throw std::out_of_range("Posição invalida");
        temp = contents[index];
        atual = index;
        while (atual < size_ - 1) {
            contents[atual] = contents[atual + 1];
            atual++;
        }
        size_ = size_ - 1;
        return(temp);
    }
    //! metodo que retira do final da lista
    T pop_back() {
        return pop(size_ - 1);
    }
    //! metodo que retira do inicio da lista
    T pop_front() {
        return pop(0);
    }
    //! metodo que retira o dado selecionado
    void remove(const T& data) {
        std::size_t atual;
        if (empty())
            throw std::out_of_range("lista vazia");
        atual = find(data);
        pop(atual);
    }
    //! inicio do metodo informa se a lista esta cheia
    bool full() const {
        return(size_ == max_size_);
    }
    //! inicio do metodo informa se a lista esta vazia
    bool empty() const {
        return(size_ == 0);
    }
    //! inicio metodo que procura um certo dado
    bool contains(const T& data) const {
        if (empty())
            throw std::out_of_range("lista vazia");
        bool tem = false;
        for (int i = 0; i < size_; i++) {
            if (data == contents[i]) {
                tem = true;
                break;
            }
        }
        return tem;
    }
    //! inicio do metodo que procura certo dado e retorna a posição
    std::size_t find(const T& data) const {
        std::size_t atual = 0;
        if (empty())
            throw std::out_of_range("lista vazia");
        while (atual < size_ && (data != contents[atual])) {
            atual++;
        }
        return(atual);
    }
    //! metodo que retorna o tamanho
    std::size_t size() const {
        return(size_);
    }
    //! metodo que retorna o tamanho maximo
    std::size_t max_size() const {
        return(max_size_);
    }
    //! metodode retorno seguro
    T& at(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("Posição invalida");
        return(contents[index]);
    }
    //! metodo de retorno rapido
    T& operator[](std::size_t index) {
        return(contents[index]);
    }
    //! metodo de retorno seguro const
    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Posição invalida");
        } else {
            return(contents[index]);
        }
    }
    //! metodo de retorno rapido const
    const T& operator[](std::size_t index) const {
        return(contents[index]);
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif
