using namespace s21;

template <class T> deque<T>::deque() { // Конструктор по умолчанию
  nList.size = 0;
  nList.head = nullptr;
  nList.tail = nullptr;
}

template <class T>
deque<T>::deque(std::initializer_list<value_type> const &items)
    : deque() { // Конструктор с инициализацией
  for (auto i = items.begin(); i != items.end(); i++)
    push_back(*i);
}

template <class T>
deque<T>::deque(const deque &other) : deque() { // Конструктор копирования
  Node *current = other.nList.head;
  while (current) {
    push_back(current->value);
    current = current->next;
  }
}

template <class T> deque<T>::deque(deque &&other) { // Конструктор перемещения
  nList.size = other.nList.size;
  nList.head = other.nList.head;
  nList.tail = other.nList.tail;
  other.nList.size = 0;
  other.nList.head = nullptr;
  other.nList.tail = nullptr;
}

template <typename T>
void deque<T>::swap(deque &other) noexcept { // Метод обмена
  // Обмен указателей на голову списка
  std::swap(nList.head, other.nList.head);
  // Обмен указателей на хвост списка
  std::swap(nList.tail, other.nList.tail);
  // Обмен значениями переменной Size
  std::swap(nList.size, other.nList.size);
}

template <class T> deque<T> &deque<T>::operator=(const deque &other) {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    Node *current = other.nList.head;
    while (current) {
      push_back(current->value);
      current = current->next;
    }
  }
  return *this;
}

template <class T> deque<T> &deque<T>::operator=(deque &&other) noexcept {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    nList.size = other.nList.size;
    nList.head = other.nList.head;
    nList.tail = other.nList.tail;
    other.nList.size = 0;
    other.nList.head = nullptr;
    other.nList.tail = nullptr;
  }
  return *this;
}

template <class T> deque<T>::~deque() { clear(); }

template <class T> void deque<T>::clear() {
  while (nList.size > 0) {
    pop_front();
  }
}

template <class T> bool deque<T>::empty() const { return size() == 0; }

template <class T> typename deque<T>::size_type deque<T>::size() const {
  return nList.size;
}

template <class T>
const typename deque<T>::value_type &deque<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Deque is empty");
  }
  return nList.head->value;
}

template <class T> const typename deque<T>::value_type &deque<T>::back() const {
  return nList.tail->value;
}

template <class T> void deque<T>::push_front(const_reference data) {
  Node *node = new Node(data);
  node->next = nList.head;
  node->prev = nullptr;
  if (nList.head) {
    nList.head->prev = node;
  }
  nList.head = node;
  if (nList.tail == nullptr) {
    nList.tail = node;
  }
  ++nList.size;
}

template <class T> void deque<T>::pop_front() {
  if (nList.head == nullptr)
    return; // Проверка на пустоту списка
  Node *temp = nList.head;
  nList.head = nList.head->next;
  if (nList.head != nullptr) {
    nList.head->prev = nullptr;
  } else {
    nList.tail = nullptr; // Если список пуст, обнуляем tail
  }
  delete temp;
  --nList.size;
}

template <class T> void deque<T>::push_back(const_reference data) {
  Node *node = new Node(data);
  node->prev = nList.tail;
  node->next = nullptr;
  if (nList.tail) {
    nList.tail->next = node;
  }
  nList.tail = node;
  if (nList.head == nullptr) {
    nList.head = node;
  }
  ++nList.size;
}

template <class T> void deque<T>::pop_back() {
  if (nList.tail) {
    Node *node = nList.tail;
    nList.tail = nList.tail->prev;
    if (nList.tail) {
      nList.tail->next = nullptr;
    } else {
      nList.head = nullptr;
    }
    delete node;
    --nList.size;
  }
}

template <typename T> T &deque<T>::operator[](const int index) {
  if (index < 0 ||
      static_cast<s21::deque<int>::size_type>(index) >= nList.size) {
    throw std::out_of_range("Index out of range");
  }

  Node *current = nList.head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  return current->value;
}