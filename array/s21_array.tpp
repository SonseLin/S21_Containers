using namespace s21;

template <typename value_type, size_t N>
array<value_type, N>::array()
    : _arrayPtr(static_cast<value_type *>(new value_type[N]{})) {}

template <typename value_type, size_t N>
array<value_type, N>::array(std::initializer_list<value_type> const &items)
    : _arrayPtr(static_cast<value_type *>(new value_type[N]{})) {
  if (items.size() > _size) {
    throw std::out_of_range("Too many initializers for array");
  }
  std::copy(items.begin(), items.end(), _arrayPtr);
}

template <typename value_type, size_t N>
array<value_type, N>::array(const array<value_type, N> &a)
    : _size(a._size),
      _arrayPtr(static_cast<value_type *>(new value_type[a._size]{})) {
  std::copy(a._arrayPtr, a._arrayPtr + a._size, _arrayPtr);
}
template <typename value_type, size_t N>
array<value_type, N>::array(array<value_type, N> &&a)
    : _size(a._size), _arrayPtr(a._arrayPtr) {
  a._size = 0;
  a._arrayPtr = nullptr;
}

template <typename value_type, size_t N> array<value_type, N>::~array() {
  if (_arrayPtr) {
    delete[] _arrayPtr;
  }
  _size = 0;
  _arrayPtr = nullptr;
}

template <typename value_type, size_t N>
array<value_type, N> &
array<value_type, N>::operator=(array<value_type, N> &&a) {
  if (this != &a) {
    if (_arrayPtr) {
      delete[] _arrayPtr;
    }
    _arrayPtr = a._arrayPtr;
    _size = a._size;

    a._size = 0;
    a._arrayPtr = nullptr;
  }
  return *this;
}

template <typename value_type, size_t N>
typename array<value_type, N>::reference
array<value_type, N>::at(size_type pos) {
  if (empty() == true || pos >= _size) {
    throw std::out_of_range("Index out of range vector");
  }
  return *(_arrayPtr + pos);
}
template <typename value_type, size_t N>
typename array<value_type, N>::reference
array<value_type, N>::operator[](size_type pos) {
  return *(_arrayPtr + pos);
}

template <typename value_type, size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::front() {
  return *(begin());
}

template <typename value_type, size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::back() {
  return *(end() - 1);
}

template <typename value_type, size_t N>
typename array<value_type, N>::iterator array<value_type, N>::data() {
  return _arrayPtr;
}

template <typename value_type, size_t N>
typename array<value_type, N>::iterator array<value_type, N>::begin() {
  return _arrayPtr;
}

template <typename value_type, size_t N>
typename array<value_type, N>::iterator array<value_type, N>::end() {
  return _arrayPtr + _size;
}

template <typename value_type, size_t N> bool array<value_type, N>::empty() {
  return _size == 0;
}

template <typename value_type, size_t N>
typename array<value_type, N>::size_type array<value_type, N>::size() {
  return _size;
}

template <typename value_type, size_t N>
typename array<value_type, N>::size_type array<value_type, N>::max_size() {
  return size();
}

template <typename value_type, size_t N>
void array<value_type, N>::swap(array<value_type, N> &other) {
  std::swap(_size, other._size);
  std::swap(_arrayPtr, other._arrayPtr);
}

template <typename value_type, size_t N>
void array<value_type, N>::fill(const_reference value) {
  for (size_type i = 0; i < _size; ++i) {
    _arrayPtr[i] = value;
  }
}