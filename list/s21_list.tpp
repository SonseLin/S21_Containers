using namespace s21;

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), last_(nullptr), size_(0) {
  last_ = new Node(size_);
  link_list();
}

template <typename T> list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T> list<T>::list(const list &other) : list() {
  for (const auto &value : other) {
    push_back(value);
  }
}

template <typename T> list<T>::list(list &&l) noexcept : list() { swap(l); }

template <typename T> list<T>::~list() {
  clear();
  delete last_;
}

template <typename T> list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

template <typename T> bool list<T>::operator==(list &other) {
  if (size_ != other.size_)
    return false;

  auto it1 = this->begin();
  auto it2 = other.begin();

  while (it1 != last() && it2 != other.last()) {
    if (*it1 != *it2)
      return false;
    ++it1;
    ++it2;
  }
  return true;
}

template <typename T> void list<T>::pop_front() {
  if (empty() == false) {
    Node *tmp = head_;

    if (size_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      head_ = head_->next;
      head_->prev = nullptr;
    }

    --size_;
    delete tmp;
    link_list();
  }
}

template <typename T> void list<T>::pop_back() {
  if (empty() == false) {
    Node *tmp = tail_;

    if (size_ == 1) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      tail_ = tail_->prev;
      tail_->next = nullptr;
    }

    --size_;
    delete tmp;
    link_list();
  }
}

template <typename T> void list<T>::push_front(const_reference value) {
  Node *new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  ++size_;
  link_list();
}

template <typename T> void list<T>::push_back(const_reference value) {
  Node *new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
  }
  ++size_;
  link_list();
}

template <typename T> bool list<T>::empty() const { return size_ == 0; }

template <typename T> typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T> typename list<T>::size_type list<T>::max_size() const {
  return size_type(-1) / sizeof(Node);
}

template <typename T> typename list<T>::const_reference list<T>::front() const {
  if (!head_)
    throw std::out_of_range("list is empty");
  return head_->value;
}

template <typename T> typename list<T>::const_reference list<T>::back() const {
  if (!tail_)
    throw std::out_of_range("list is empty");
  return tail_->value;
}

template <typename T> typename list<T>::iterator list<T>::begin() {
  return head_ ? iterator(head_) : iterator(last_);
}

template <typename T> typename list<T>::const_iterator list<T>::cbegin() const {
  return head_ ? const_iterator(head_) : const_iterator(last_);
}

template <typename T> typename list<T>::iterator list<T>::last() {
  return iterator(last_);
}

template <typename T> typename list<T>::const_iterator list<T>::clast() const {
  return const_iterator(last_);
}

template <typename T> typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T> typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(nullptr);
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == last()) {
    push_back(value);
    return iterator(tail_);
  } else if (pos == begin()) {
    push_front(value);
    return iterator(head_);
  } else {
    Node *new_node = new Node(value);
    Node *cur = pos.ptr;
    new_node->next = cur;
    new_node->prev = cur->prev;
    cur->prev->next = new_node;
    cur->prev = new_node;
    ++size_;
    link_list();
    return iterator(new_node);
  }
}

template <typename T> void list<T>::erase(iterator pos) {
  if (empty() || pos.ptr == nullptr)
    return;

  Node *cur = pos.ptr;

  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else if (cur == head_) {
    head_ = head_->next;
    head_->prev = nullptr;
    delete cur;
  } else if (cur == tail_) {
    tail_ = tail_->prev;
    tail_->next = nullptr;
    delete cur;
  } else {
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
  }

  --size_;
}

template <typename T> void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <typename T> void list<T>::swap(list &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
  std::swap(this->last_, other.last_);
}

template <typename T> bool list<T>::compare(const list &other) const {
  if (size() != other.size())
    return false;
  auto it1 = begin();
  auto it2 = other.begin();
  while (it1 != end()) {
    if (*it1 != *it2)
      return false;
    ++it1;
    ++it2;
  }
  return true;
}

template <typename T> void list<T>::merge(list &other) {
  if (this == &other)
    return;
  if (empty()) {
    swap(other);
  } else if (!other.empty()) {
    tail_->next = other.head_;
    other.head_->prev = tail_;
    tail_ = other.tail_;
    size_ += other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
    link_list();
  }
}

template <typename T> void list<T>::splice(const_iterator pos, list &other) {
  if (this == &other || other.empty())
    return;

  Node *posNode = pos.ptr;
  Node *otherHead = other.head_;
  Node *otherTail = other.tail_;

  if (posNode) {
    if (posNode->prev) {
      posNode->prev->next = otherHead;
    } else {
      head_ = otherHead;
    }
    otherHead->prev = posNode->prev;
    posNode->prev = otherTail;
    otherTail->next = posNode;
  } else {
    if (tail_) {
      tail_->next = otherHead;
      otherHead->prev = tail_;
      tail_ = otherTail;
    } else {
      head_ = otherHead;
      tail_ = otherTail;
    }
  }

  size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <typename T> void list<T>::unique() {
  if (size_ <= 1)
    return;

  iterator it = begin();
  while (it != end()) {
    iterator next = it;
    ++next;

    while (next != end() && *it == *next) {
      iterator to_delete = next;
      ++next;
      erase(to_delete);
    }
    it = next;
  }
}

template <typename T> void list<T>::sort() {
  if (size_ <= 1)
    return;

  list<T> left;
  list<T> right;

  auto mid = begin();
  size_type midIndex = size_ / 2;
  for (size_type i = 0; i < midIndex; ++i) {
    ++mid;
  }

  while (begin() != mid) {
    left.push_back(*begin());
    pop_front();
  }
  while (!empty()) {
    right.push_back(*begin());
    pop_front();
  }

  left.sort();
  right.sort();

  auto it_left = left.begin();
  auto it_right = right.begin();

  while (it_left != left.end() && it_right != right.end()) {
    if (*it_left < *it_right) {
      push_back(*it_left);
      ++it_left;
    } else {
      push_back(*it_right);
      ++it_right;
    }
  }

  while (it_left != left.end()) {
    push_back(*it_left);
    ++it_left;
  }

  while (it_right != right.end()) {
    push_back(*it_right);
    ++it_right;
  }
}

template <typename T> void list<T>::reverse() {
  list tmp;
  Node *last = tail_;
  while (last != head_) {
    tmp.push_front(last->value);
    last = last->prev;
  }
  tmp.push_front(last->value);
  swap(tmp);
}

template <typename T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator it = pos;
  (insert(it++, std::forward<Args>(args)), ...);
  return it;
}

template <typename T>
template <class... Args>
void list<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <class... Args>
void list<T>::insert_many_front(Args &&...args) {
  (push_front(std::forward<Args>(args)), ...);
}

template <typename T> void list<T>::link_list() {
  if (last_) {
    last_->next = head_;
    last_->prev = tail_;

    if (head_) {
      head_->prev = last_;
    }
    if (tail_) {
      tail_->next = last_;
    }
  }
}

template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() const {
  return ptr->value;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator++() {
  ptr = ptr->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  ListIterator temp = *this;
  ptr = ptr->next;
  return temp;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator--() {
  ptr = ptr->prev;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
  ListIterator temp = *this;
  ptr = ptr->prev;
  return temp;
}

template <typename T>
typename list<T>::ListIterator
list<T>::ListIterator::operator+(const size_type value) {
  ListIterator temp = *this;
  for (size_type i = 0; i < value && temp.ptr; ++i) {
    temp.ptr = temp.ptr->next;
  }
  return temp;
}

template <typename T>
typename list<T>::ListIterator
list<T>::ListIterator::operator-(const size_type value) {
  ListIterator temp = *this;
  for (size_type i = 0; i < value && temp.ptr; ++i) {
    temp.ptr = temp.ptr->prev;
  }
  return temp;
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator &other) const {
  return ptr == other.ptr;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator &other) const {
  return ptr != other.ptr;
}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(const ListIterator &it)
    : ListIterator(it.ptr) {}

template <typename T>
typename list<T>::const_reference
list<T>::ListConstIterator::operator*() const {
  return ListIterator::operator*();
}