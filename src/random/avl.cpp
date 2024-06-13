#include "common.h"

template <class T>
struct Avl {
  struct Node {
    T val;
    size_t ht = 1;
    Node* lhs = nullptr;
    Node* rhs = nullptr;
    Node(T val) : val{val} {}
  };
  Node* root = nullptr;

  void insert(const T& val);
  void remove(const T& val);
};

template <class T>
using Node = typename Avl<T>::Node;

template <class T>
Node<T>* make_node(T val) {
  return new Node<T>(val);
}

template <class T>
void free_node(Node<T>* node) {
  delete node;
}

namespace impl {
  template <class T>
  size_t height(Node<T>* node) {
    if (!node) return 0;
    return std::max(height(node->lhs), height(node->rhs)) + 1;
  }

  template <class T>
  ssize_t factor(Node<T>* node) {
    if (!node) return -1;
    return height(node->rhs) - height(node->lhs);
  }

  template <class T>
  Node<T>* rotate_r(Node<T>* top) {
    auto mid = top->lhs;
    auto ext = mid->rhs;
    mid->rhs = top;
    top->lhs = ext;
    top->ht = height(top);
    mid->height = height(mid);
    return mid;
  }

  template <class T>
  Node<T>* rotate_l(Node<T>* top) {
    auto mid = top->rhs;
    auto ext = mid->lhs;
    mid->lhs = top;
    top->rhs = ext;
    top->ht = height(top);
    mid->height = height(mid);
    return mid;
  }
} // namespace impl
namespace impl {
  template <class T>
  Node<T>* insert(Node<T>* node, const T& val) {
    // insert
    if (!node) return make_node(val);
    if (val < node->val) node->lhs = insert(node->lhs, val);
    else if (val > node->val) node->rhs = insert(node->rhs, val);
    else return node;

    node->ht = height(node);
    ssize_t factor = factor(node);

    // balance
    if (factor < -1) {
      if (val < node->lhs->val) {
        return rotate_r(node);
      } else {
        node->rhs = rotate_l(node->lhs);
        return rotate_r(node);
      }
    }
    if (factor > 1) {
      if (val > node->rhs->val) {
        return rotate_l(node);
      } else {
        node->rhs = rotate_r(node->rhs);
        return rotate_l(node);
      }
    }
    return node;
  }

  template <class T>
  Node<T>* remove(Node<T>* node, const T& val) {
    if (!node) return nullptr;
    if (val < node->val) node->lhs = remove(node->lhs, val);
    else if (val > node->val) node->rhs = remove(node->rhs, val);
    else {
      if (node->lhs && node->rhs) {
        auto next = node->lhs;
        while (next->rhs) next = next->rhs;
        node->val = next->val;
        node->lhs = remove(node->lhs, next->val);
      } else if (!node->lhs && !node->rhs) {
        free_node(node);
        return nullptr;
      } else {
        auto next = (node->lhs) ? node->lhs : node->rhs;
        free_node(node);
        node = next;
      }
    }
    node->ht = height(node);
    ssize_t factor = factor(node);

    // balance
    if (factor < -1) {
      if (factor(node->lhs) <= 0) {
        return rotate_r(node);
      } else {
        node->lhs = rotate_l(node->lhs);
        return rotate_r(node);
      }
    }
    if (factor > 1) {
      if (factor(node->rhs) >= 0) {
        return rotate_l(node);
      } else {
        node->rhs = rotate_r(node->rhs);
        return rotate_l(node);
      }
    }
    return node;
  }
} // namespace impl

template <class T>
void Avl<T>::insert(const T& val) {
  root = impl::insert(root, val);
}

template <class T>
void Avl<T>::remove(const T& val) {
  root = impl::remove(root, val);
}

int main() {}
