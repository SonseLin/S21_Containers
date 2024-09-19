#include <algorithm>
#include <limits>

using namespace s21;

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator++() {
  _ptr++;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator
vector<T>::VectorIterator::operator+(int n) const {
  VectorIterator tmp(*this);
  tmp._ptr += n;
  return tmp;
}

template <typename T>
typename vector<T>::VectorIterator &vector<T>::VectorIterator::operator--() {
  _ptr--;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator
vector<T>::VectorIterator::operator-(int n) const {
  VectorIterator tmp(*this);
  tmp._ptr -= n;
  return tmp;
}

template <typename T>
ptrdiff_t vector<T>::VectorIterator::operator-(const VectorIterator &vi) const {
  return _ptr - vi._ptr;
}

template <typename T>
bool vector<T>::VectorIterator::operator>(const VectorIterator &vi) const {
  return _ptr > vi._ptr;
}

template <typename T>
bool vector<T>::VectorIterator::operator<(const VectorIterator &vi) const {
  return _ptr < vi._ptr;
}

template <typename T>
bool vector<T>::VectorIterator::operator>=(const VectorIterator &vi) const {
  return _ptr >= vi._ptr;
}

template <typename T>
bool vector<T>::VectorIterator::operator<=(const VectorIterator &vi) const {
  return _ptr >= vi._ptr;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator &vi) {
  return _ptr == vi._ptr;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator &vi) {
  return _ptr != vi._ptr;
}

template <typename T>
typename vector<T>::reference vector<T>::VectorIterator::operator*() {
  return *_ptr;
}

template <typename T>
typename vector<T>::VectorConstIterator &
vector<T>::VectorConstIterator::operator++() {
  _constPtr++;
  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator &
vector<T>::VectorConstIterator::operator--() {
  _constPtr--;
  return *this;
}

template <typename T>
ptrdiff_t vector<T>::VectorConstIterator::operator-(
    const VectorConstIterator &c_vi) const {
  return _constPtr - c_vi._constPtr;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator-(int n) const {
  VectorConstIterator tmp(*this);
  tmp._constPtr -= n;
  return tmp;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator+(int n) const {
  VectorConstIterator tmp(*this);
  tmp._constPtr += n;
  return tmp;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator==(const VectorConstIterator &vi) {
  return _constPtr == vi._constPtr;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator!=(const VectorConstIterator &vi) {
  return _constPtr != vi._constPtr;
}

template <typename T>
typename vector<T>::const_reference
vector<T>::VectorConstIterator::operator*() const {
  return *_constPtr;
}

template <typename value_type>
vector<value_type>::vector() : _size(0), _capacity(0), _vectorPtr(nullptr) {}

template <typename value_type>
vector<value_type>::vector(const size_type size)
    : _size(size), _capacity(size) {
  _vectorPtr = static_cast<value_type *>(new value_type[size]);
  std::fill_n(_vectorPtr, _size, value_type{});
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items)
    : _size(items.size()), _capacity(items.size()) {
  _vectorPtr = static_cast<value_type *>(new value_type[items.size()]);
  std::copy(items.begin(), items.end(), _vectorPtr);
}

template <typename value_type>
vector<value_type>::vector(const vector<value_type> &v)
    : _size(v._size), _capacity(v._capacity) {
  _vectorPtr = static_cast<value_type *>(new value_type[v._capacity]);
  std::copy(v._vectorPtr, v._vectorPtr + v._size, _vectorPtr);
}

template <typename value_type>
vector<value_type>::vector(vector<value_type> &&v)
    : _size(v._size), _capacity(v._capacity), _vectorPtr(v._vectorPtr) {
  v._size = 0;
  v._capacity = 0;
  v._vectorPtr = nullptr;
}

template <typename value_type> vector<value_type>::~vector() {
  if (_vectorPtr) {
    delete[] _vectorPtr;
  }
  _vectorPtr = nullptr;
  _size = 0;
  _capacity = 0;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector<value_type> &&v) {
  if (this != &v) {
    if (_vectorPtr) {
      delete[] _vectorPtr;
    }
    _vectorPtr = v._vectorPtr;
    _size = v._size;
    _capacity = v._capacity;

    v._vectorPtr = nullptr;
    v._size = 0;
    v._capacity = 0;
  }
  return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (empty() == true || pos >= _size) {
    throw std::out_of_range("Index out of range vector");
  }
  return *(_vectorPtr + pos);
}

template <typename value_type>
typename vector<value_type>::reference
vector<value_type>::operator[](size_type pos) {
  return *(_vectorPtr + pos);
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
  return *(begin());
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
  return *(--end());
}

template <typename value_type>
typename vector<value_type>::value_type *vector<value_type>::data() {
  return _vectorPtr;
}

template <typename T> typename vector<T>::iterator vector<T>::begin() {
  return iterator(_vectorPtr);
}

template <typename T> typename vector<T>::iterator vector<T>::end() {
  return iterator(_vectorPtr + _size);
}

template <typename T> typename vector<T>::const_iterator vector<T>::cbegin() {
  return const_iterator(_vectorPtr);
}

template <typename T> typename vector<T>::const_iterator vector<T>::cend() {
  return const_iterator(_vectorPtr + _size);
}

template <typename value_type> bool vector<value_type>::empty() {
  return _size == 0;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
  return _size;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename value_type>
void vector<value_type>::reserve(typename vector<value_type>::size_type size) {
  if (size > max_size()) {
    throw std::out_of_range("New size is larger than the allowed one");
  }
  if (size > _capacity) {
    vector<value_type> tmp(size);
    tmp._size = _size;
    std::copy(_vectorPtr, _vectorPtr + _size, tmp._vectorPtr);
    tmp._capacity = size;
    *this = std::move(tmp);
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() {
  return _capacity;
}

template <typename value_type> void vector<value_type>::shrink_to_fit() {
  if (_size < _capacity) {
    vector<value_type> tmp(_size);
    std::copy(_vectorPtr, _vectorPtr + _size, tmp._vectorPtr);
    tmp._capacity = _size;
    *this = std::move(tmp);
  }
}

template <typename value_type> void vector<value_type>::clear() {
  while (_size != 0) {
    pop_back();
  }
}

template <typename value_type>
typename vector<value_type>::iterator
vector<value_type>::insert(iterator pos, const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator is out of range Vector");
  }
  size_t index = pos - begin();
  if (_size == _capacity) {
    this->reserve(_capacity ? _capacity * 2 : 1);
  }
  iterator new_pos = begin() + index;
  for (iterator i = end(); i != new_pos; --i) {
    *i = *(i - 1);
  }
  *new_pos = value;
  ++_size;
  return new_pos;
}

template <typename value_type> void vector<value_type>::erase(iterator pos) {
  if (empty() || pos < begin() || pos >= end()) {
    throw std::out_of_range("Iterator is out of range Vector");
  }
  for (iterator i = pos; i < --end(); ++i) {
    *i = *(++pos);
  }
  --_size;
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename value_type> void vector<value_type>::pop_back() {
  if (_size > 0) {
    erase(--end());
  }
}

template <typename value_type>
void vector<value_type>::swap(vector<value_type> &other) {
  if (this != &other) {
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_vectorPtr, other._vectorPtr);
  }
}

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator
vector<value_type>::insert_many(const_iterator c_pos, Args &&...args) {
  vector tmp{args...};
  iterator pos = begin() + (c_pos - cbegin());
  for (size_type i = 0; i < tmp._size; ++i, ++pos) {
    pos = insert(pos, tmp[i]);
  }
  --pos;
  return pos;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}