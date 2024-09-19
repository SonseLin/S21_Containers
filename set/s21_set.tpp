using namespace s21;

template <typename Key> set<Key>::set() : BinaryTree<Key, Key>() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items)
    : BinaryTree<Key, Key>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    BinaryTree<Key, Key>::insert(*i, Key());
  }
}

template <typename Key> set<Key>::set(const set &s) : BinaryTree<Key, Key>(s) {}

template <typename Key>
set<Key>::set(set &&s) : BinaryTree<Key, Key>(std::move(s)) {}

template <typename Key> set<Key> set<Key>::operator=(set &&s) {
  BinaryTree<Key, Key>::operator=(std::move(s));
  return *this;
}

template <typename Key> bool set<Key>::contains(const Key &key) {
  return BinaryTree<Key, Key>::contains(key);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  return BinaryTree<Key, Key>::find(key);
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool>
set<Key>::insert(const value_type &value) {
  return BinaryTree<Key, Key>::insert(value, Key());
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename set<Key>::iterator, bool>>
set<Key>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> result_vector;
  (result_vector.push_back(insert(std::forward<Args>(args))), ...);
  return static_cast<s21::vector<std::pair<typename set<Key>::iterator, bool>>>(
      result_vector);
}

template <typename Key> bool set<Key>::empty() {
  return BinaryTree<Key, Key>::empty();
}

template <typename Key> typename set<Key>::iterator set<Key>::begin() const {
  return BinaryTree<Key, Key>::begin();
}

template <typename Key> typename set<Key>::iterator set<Key>::end() const {
  return BinaryTree<Key, Key>::end();
}

template <typename Key> typename set<Key>::size_type set<Key>::Size() {
  return BinaryTree<Key, Key>::Size();
}

template <typename Key> typename set<Key>::size_type set<Key>::max_size() {
  return std::numeric_limits<typename set<Key>::size_type>::max() /
         sizeof(typename set<Key>::value_type);
}

template <typename Key> void set<Key>::clear() {
  BinaryTree<Key, Key>::clear();
}

template <typename Key> void set<Key>::erase(iterator pos) {
  BinaryTree<Key, Key>::erase(pos);
}

template <typename Key> void set<Key>::swap(set &other) {
  BinaryTree<Key, Key>::swap(other);
}

template <typename Key> void set<Key>::merge(set &other) {
  BinaryTree<Key, Key>::merge(other);
}