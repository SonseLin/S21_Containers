using namespace s21;

template <typename K, typename T>
BinaryTree<K, T>::Node::Node(
    K _key, T _value,
    Node *_parent) // Создание узел дерева с ключом _key и значением _value
    : left(nullptr), right(nullptr), parent(_parent), key(_key), value(_value) {
}

// ************************************************************************************************************************

template <typename K, typename T>
BinaryTree<K, T>::Node::~Node() { // Удаление узла
  if (right)
    delete right;
  if (left)
    delete left;
}

// ************************************************************************************************************************
template <typename K, typename T>
BinaryTree<K, T>::Iterator::Iterator()
    : ptr(nullptr) {} // Конструктор создания итератора по умолчанию

// ************************************************************************************************************************

template <typename K, typename T>
BinaryTree<K, T>::Iterator::Iterator(Node *_ptr)
    : ptr(_ptr) {
} // Конструктор итератора с указателем на узел _ptr (узел дерева)

// ************************************************************************************************************************

template <typename K, typename T>
typename BinaryTree<K, T>::Iterator &
BinaryTree<K, T>::Iterator::operator++() { // Перейти к следующему узлу
  if (ptr != nullptr) {
    // Если есть правое поддерево, идем в его самый левый узел
    if (ptr->right != nullptr) {
      ptr = ptr->right;
      while (ptr->left != nullptr)
        ptr = ptr->left;
    } else {
      // Если правого поддерева нет, поднимаемся вверх по дереву
      Node *parent = ptr->parent;
      while (parent != nullptr && ptr == parent->right) {
        ptr = parent;
        parent = parent->parent;
      }
      ptr = parent; // Либо родитель, либо nullptr (если дошли до конца)
    }
  }
  return *this;
}

// ************************************************************************************************************************

template <typename K, typename T>
typename BinaryTree<K, T>::Iterator
BinaryTree<K, T>::Iterator::operator++(int) { // Постфиксный инкремент
  // Если итератор уже указывает на nullptr, возвращаем итератор на nullptr
  if (ptr == nullptr)
    return *this;

  Iterator tmp(ptr); // Сохраняем текущее состояние итератора
  ++(*this);  // Выполняем префиксный инкремент
  return tmp; // Возвращаем сохраненное состояние
}

// ************************************************************************************************************************

template <typename K, typename T>
typename BinaryTree<K, T>::Iterator &
BinaryTree<K, T>::Iterator::operator--() { // Перейти к предыдущему узлу
  if (ptr != nullptr) {
    if (ptr->left != nullptr) {
      // Перейти к левому поддереву
      ptr = ptr->left;
      // Найти самый правый узел в левом поддереве
      while (ptr->right != nullptr) {
        ptr = ptr->right;
      }
    } else {
      // Перемещаться вверх по дереву, пока не найдем родителя, который является
      // правым потомком
      Node *parent = ptr->parent;
      while (parent != nullptr && ptr == parent->left) {
        ptr = parent;
        parent = parent->parent;
      }
      ptr = parent;
    }
  }
  return *this;
}

// ************************************************************************************************************************

template <typename K, typename T>
typename BinaryTree<K, T>::Iterator
BinaryTree<K, T>::Iterator::operator--( // Постфиксный декремент
    int) {
  Iterator tmp(ptr);
  --(*this);
  return tmp;
}

// ************************************************************************************************************************

template <typename K, typename T>
bool BinaryTree<K, T>::Iterator::operator==(Iterator other) const {
  return other.ptr == this->ptr;
}

template <typename K, typename T>
bool BinaryTree<K, T>::Iterator::operator!=(Iterator other) const {
  return other.ptr != this->ptr;
}

template <typename K, typename T>
typename BinaryTree<K, T>::Node *
BinaryTree<K, T>::Iterator::operator->() const {
  return ptr;
}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree() : size(0), null_node(nullptr) {}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree(std::initializer_list<value_type> const &items)
    : size(0), null_node(nullptr) {
  for (auto i = items.begin(); i != items.end(); ++i)
    insert(i->first, i->second);
}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree(const BinaryTree &other)
    : size(0), null_node(nullptr) {
  assign(other);
}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree(BinaryTree &&other) : size(0), null_node(nullptr) {
  assign(other);
  other.clear();
}

template <typename K, typename T> BinaryTree<K, T>::~BinaryTree() {
  if (root.ptr)
    delete root.ptr;
}

template <typename K, typename T>
BinaryTree<K, T> BinaryTree<K, T>::operator=(BinaryTree &&other) {
  assign(other);
  other.clear();
  return *this;
}

template <typename K, typename T>
T &BinaryTree<K, T>::operator[](const K &key) {
  iter.ptr = root.ptr;
  Node *result = find(iter.ptr, key);
  if (result == nullptr)
    result = insert_or_assign(key, T()).first.ptr;
  return result->value;
}

template <typename K, typename T> T &BinaryTree<K, T>::at(const K &key) {
  iter.ptr = root.ptr;
  Node *result = find(iter.ptr, key);
  if (result == nullptr)
    throw std::out_of_range("");
  return result->value;
}

template <typename K, typename T>
bool BinaryTree<K, T>::contains(Node *root, const K &key) {
  bool result = false;
  if (root != nullptr) {
    if (root->key == key)
      result = true;
    else if (root->key < key) {
      if (root->right != nullptr)
        result = contains(root->right, key);
    } else if (root->left != nullptr)
      result = contains(root->left, key);
  }
  return result;
}

template <typename K, typename T>
bool BinaryTree<K, T>::contains(const K &key) {
  return contains(root.ptr, key);
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::find(const K &key) {
  iter.ptr = root.ptr;
  iter.ptr = find(iter.ptr, key);
  return iter;
}

template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator, bool>
BinaryTree<K, T>::insert(const value_type &value) {
  return insert(value.first, value.second);
}

template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator, bool>
BinaryTree<K, T>::insert(const K &key, const T &obj) {
  bool result = false;
  std::pair<iterator, bool> pair;
  if (!contains(key)) {
    pair = insert_or_assign(key, obj);
    result = pair.second;
  }
  return std::pair<iterator, bool>(pair.first, result);
}

template <typename K, typename T> bool BinaryTree<K, T>::empty() {
  return size == 0;
}

template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator, bool>
BinaryTree<K, T>::insert_or_assign(const K &key, const T &obj) {
  bool result = true;
  if (null_node != nullptr && end_i.ptr != nullptr) {
    --end_i;
    end_i->right = nullptr;
    delete null_node;
  }
  if (!empty())
    iter.ptr = root.ptr;
  iter.ptr = insert(iter.ptr, key, obj);
  ++size;
  set_begin();
  set_end();
  return std::pair<iterator, bool>(iter, result);
}

template <typename K, typename T>
typename BinaryTree<K, T>::Node *BinaryTree<K, T>::insert(
    Node *
        iter, // -------------------------------------------------------------------
    const K &key, const T &value) {
  if (root.ptr == nullptr) {
    root.ptr = new Node(key, value, nullptr);
    iter = root.ptr;
  } else {
    if (iter->key == key) {
      iter->value = value;
    } else if (key > iter->key) {
      if (iter->right == nullptr) {
        iter->right = new Node(key, value, iter);
        iter = iter->right;
      } else
        iter = insert(iter->right, key, value);
    } else {
      if (iter->left == nullptr) {
        iter->left = new Node(key, value, iter);
        iter = iter->left;
      } else
        iter = insert(iter->left, key, value);
    }
  }
  return iter;
}

// ************************************************************************************************************************

template <typename K, typename T>
void BinaryTree<K, T>::insert(
    Node *iter, Node *_node) { // Вставка узла в бинарное дерево по итератору
  if (root.ptr == nullptr) {
    root.ptr = _node;
    return;
  }

  if (_node->key >= iter->key) {
    if (iter->right == nullptr) {
      _node->parent = iter;
      iter->right = _node;
    } else {
      insert(iter->right, _node);
    }
  } else {
    if (iter->left == nullptr) {
      _node->parent = iter;
      iter->left = _node;
    } else {
      insert(iter->left, _node);
    }
  }
}

// ************************************************************************************************************************

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::set_end() {
  end_i.ptr = root.ptr;
  if (root.ptr != nullptr) {
    while (end_i->right != nullptr)
      end_i.ptr = end_i->right;
    null_node = new Node(end_i->key, end_i->value);
    null_node->parent = end_i.ptr;
    end_i->right = null_node;
    end_i.ptr = null_node;
  }
  return end_i;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::set_begin() {
  begin_i.ptr = root.ptr;
  if (root.ptr != nullptr)
    while (begin_i->left != nullptr)
      begin_i.ptr = begin_i->left;
  return begin_i;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::begin() const {
  return begin_i;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::end() const {
  return end_i;
}

template <typename K, typename T>
typename BinaryTree<K, T>::size_type BinaryTree<K, T>::Size() {
  return BinaryTree<K, T>::size;
}

template <typename K, typename T>
typename BinaryTree<K, T>::size_type BinaryTree<K, T>::max_size() {
  return std::numeric_limits<typename BinaryTree<K, T>::size_type>::max() /
         sizeof(typename BinaryTree<K, T>::value_type);
}

template <typename K, typename T> void BinaryTree<K, T>::clear() {
  if (root.ptr)
    delete root.ptr;
  root.ptr = nullptr;
  null_node = nullptr;
  iter.ptr = nullptr;
  begin_i.ptr = nullptr;
  end_i.ptr = nullptr;
  size = 0;
}

template <typename K, typename T>
void BinaryTree<K, T>::erase(
    iterator
        pos) { // -------------------------------------------------------------------
  Node *tmp = nullptr;
  for (auto i = begin(); i != end(); ++i) {
    if (pos == i) {
      tmp = i.ptr;
    }
  }
  if (tmp != nullptr) {
    if (null_node != nullptr) {
      --end_i;
      end_i->right = nullptr;
      delete null_node;
    }
    if (tmp->parent == nullptr) {
      root.ptr = (tmp->right != nullptr) ? tmp->right : tmp->left;
    } else {
      iter.ptr = tmp->parent;
      if (iter->right == tmp)
        iter->right = nullptr;
      else
        iter->left = nullptr;
    }
    if (tmp->right != nullptr && root.ptr != tmp->right) {
      iter.ptr = root.ptr;
      insert(iter.ptr, tmp->right);
    }
    if (tmp->left != nullptr && root.ptr != tmp->left) {
      iter.ptr = root.ptr;
      insert(iter.ptr, tmp->left);
    }
    --size;
    tmp->right = nullptr;
    tmp->left = nullptr;
    delete tmp;
    set_begin();
    set_end();
  }
}

// ************************************************************************************************************************

template <typename K, typename T>
void BinaryTree<K, T>::assign(const BinaryTree &other) { // Копирование дерева
  // Очистить текущее дерево
  clear();

  // Копировать все узлы из другого дерева
  for (auto i = other.begin(); i != other.end();
       ++i) { // Перебрать узлы другого дерева
    insert(i->key, i->value); // Вставить новый узел в текущее дерево
  }
}

// ************************************************************************************************************************

template <typename K, typename T>
void BinaryTree<K, T>::swap(BinaryTree &other) { // Обмен значений двух деревьев
  BinaryTree tmp(other); // Создание временного дерева
  other.clear();         // Очистка временного дерева
  other.assign(*this); // Копирование текущего дерева во временное
  BinaryTree<K, T>::clear(); // Очистка текущего дерева
  assign(tmp); // Копирование временного дерева в текущее
  tmp.clear(); // Очистка временного дерева
}

// ************************************************************************************************************************
template <typename K, typename T>
void BinaryTree<K, T>::merge(BinaryTree &other) { // Слияние двух деревьев
  for (auto it = other.begin(); it != other.end(); ++it) {
    // Вставляем элементы из другого дерева в текущее дерево
    insert(it->key, it->value);
  }
  other.clear(); // Очищаем дерево other после слияния
}

// ************************************************************************************************************************
template <typename K, typename T>
typename BinaryTree<K, T>::Node *
BinaryTree<K, T>::find(Node *root,
                       const K &key) { // Поиск узла с заданным ключом
  // Если текущий узел nullptr, возвращаем nullptr (узел не найден)
  if (root == nullptr) {
    return nullptr;
  }
  // Если ключ узла совпадает с искомым ключом, возвращаем текущий узел
  if (root->key == key) {
    return root;
  }
  // Если искомый ключ больше ключа текущего узла, ищем в правом поддереве
  if (key > root->key) {
    return find(root->right, key);
  }
  // Если искомый ключ меньше ключа текущего узла, ищем в левом поддереве
  else {
    return find(root->left, key); // Ищем в левом поддереве
  }
}

// ************************************************************************************************************************
template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::insert(
    const K &key) { // Вставка узла с заданным ключом в бинарное дерево
  // Удаление нулевого узла, если он существует
  if (null_node != nullptr) {
    // Удаляем указатель на нулевой узел
    if (end_i.ptr != nullptr) {
      --end_i;
      end_i->right = nullptr;
    }
    delete null_node;
    null_node = nullptr; // Устанавливаем null_node в nullptr после удаления
  }
  // Если дерево пустое, устанавливаем iter.ptr на корень дерева
  if (empty()) {
    root.ptr = new Node(key, T()); // Создаем новый узел в качестве корня
    iter.ptr = root.ptr;
  } else {
    iter.ptr = root.ptr;
    // Вставляем новый узел с ключом key
    insert(iter.ptr, new Node(key, T()));
  }
  // Увеличиваем размер дерева
  ++size;
  // Обновляем итераторы
  set_begin();
  set_end();
  // Возвращаем итератор на вставленный узел
  return iter;
}

// ************************************************************************************************************************

template <typename K, typename T>
typename BinaryTree<K, T>::size_type BinaryTree<K, T>::count(
    const K &key) { // Подсчет количества узлов с заданным ключом
  size_type _count = 0;
  for (auto i = begin(); i != end(); ++i)
    if (key == i->key)
      ++_count;
  return _count;
}

// ************************************************************************************************************************
template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator,
          typename BinaryTree<K, T>::iterator>
BinaryTree<K, T>::equal_range(
    const K
        &key) { // Поиск узла с заданным ключом, возвращает диапазон итераторов,
                // который охватывает все элементы с заданным ключом key
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

// ************************************************************************************************************************
template <typename K, typename T>
typename BinaryTree<K, T>::iterator
BinaryTree<K, T>::lower_bound(const K &key) { // должен находить первый элемент,
                                              // который больше или равен ключу
  Node *current = root.ptr;
  Node *last_valid = nullptr;

  while (current != nullptr) {
    if (current->key >= key) {
      last_valid =
          current; // Сохраняем текущий узел как потенциальный результат
      current = current->left; // Идем в левое поддерево
    } else {
      current = current->right; // Идем в правое поддерево
    }
  }

  iter.ptr = (last_valid != nullptr) ? last_valid : end().ptr;
  return iter;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator
BinaryTree<K, T>::upper_bound(const K &key) { // должен находить первый элемент,
                                              // который строго больше ключа
  Node *current = root.ptr;
  Node *last_valid = nullptr;

  while (current != nullptr) {
    if (current->key > key) {
      last_valid =
          current; // Сохраняем текущий узел как потенциальный результат
      current = current->left; // Идем в левое поддерево
    } else {
      current = current->right; // Идем в правое поддерево
    }
  }

  iter.ptr = (last_valid != nullptr) ? last_valid : end().ptr;
  return iter;
}
