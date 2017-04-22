// Copyright [2017] <Stefano Bergamini Poletto>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

//! classe lista circular
template<typename T>
class CircularList {
 public:
    CircularList() {
        size_ = 0;
        head = new Node((T)0, nullptr);
        head->next(head);
    }
    //! destrutor
    ~CircularList() {
        clear();
        delete head;
    }
    //! limpa lista
    void clear() {
        while (!empty())
            pop_front();
    }
    //! insere no final
    void push_back(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node *prev = head->next();
            for (int i = 0; i < size_-1; ++i) {
                prev = prev->next();
            }
            prev->next(new Node(data, head));
            ++size_;
        }
    }
    //! insere no inicio
    void push_front(const T& data) {
        Node *novo = new Node(data, head->next());
        if (novo == nullptr) {
            throw std::out_of_range("ERROLISTACHEIA-pushfront");
        }
        head->next(novo);
        size_++;
    }
    //! insere em uma posição desejada
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
          throw std::out_of_range("Erro de posicao.");
        } else if (index == 0) {
            push_front(data);
        } else if (index == size_) {
            return push_back(data);
        } else {
            Node *prev = head->next();
            for (int i = 0; i < index-1; ++i) {
                prev = prev->next();
            }
            prev->next(new Node(data, prev->next()));
            ++size_;
        }
    }
    //! insere em ordem
    void insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* curr = head->next();
            int i = 0;
            while (i < size_ && data > curr->data()) {
                curr = curr->next();
                ++i;
            }
            insert(data, i);
        }
    }
    //! retorna o que existe na posição desejada
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Erro de posicao.");
        } else if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            Node *curr = head->next();
            for (int i = 0; i < index; i++) {
                curr = curr->next();
            }
            return curr->data();
        }
    }
    //! retorna da posição de forma constante
    const T& at(std::size_t index) const {
        Node *curr = head->next();
        for (int i = 0; i < index; ++i) {
            curr = curr->next();
        }
        return curr->data();
    }
    //! remove da posição desejada
    T pop(std::size_t index) {
        Node *prev, *del;
        T back;
        if (index >= size_) {
            throw std::out_of_range("Erro de posicao.");
        }
        if (index == 0) {
            pop_front();
        }
        prev = head->next();
        for (int i = 0; i < index-1; ++i) {
            prev = prev->next();
        }
        del = prev->next();
        back = del->data();
        prev->next(del->next());
        --size_;
        delete del;
        return back;
    }
    //! remove da ultima posição
    T pop_back() {
        if (size_ == 1) {
            return pop_front();
        } else {
            return pop(size_-1);
        }
    }
    //! remove do inicio
    T pop_front() {
        T volta;
        Node *aux, *del;
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            volta = head->next()->data();
            aux = head->next()->next();
            del = head->next();
            head->next(aux);
            --size_;
            delete del;
            return volta;
        }
    }
    //! remove o item desejado
    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            pop(find(data));
        }
    }
    //! testa se esta vazia
    bool empty() const {
        return size_ == 0;
    }
    //! procura se a lista contem
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else if (find(data) == size_) {
            return false;
        } else {
            return true;
        }
    }
    //! procura o item
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Empty.");
        } else {
            Node *curr = head->next();
            for (int i = 0; i < size_; ++i) {
                if (curr->data() == data) {
                    return i;
                }
                curr = curr->next();
            }
            return size_;
        }
    }
    //! retorna o tamanho
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
