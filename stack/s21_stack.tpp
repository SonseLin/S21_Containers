using namespace s21;

template <class T, class Container>
stack<T, Container>::stack() : container() {} // Конструктор по умолчанию

template <class T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const
                               &items) { // Конструктор списка инициализаторов
  for (auto i = items.begin(); i != items.end(); i++)
    push(*i);
}

template <class T, class Container>
stack<T, Container>::stack(const stack &other)
    : container(other.container) {} // Конструктор копирования

template <class T, class Container>
stack<T, Container>::stack(stack &&other)
    : container(std::move(other.container)) {} // Конструктор перемещения

template <class T, class Container>
void stack<T, Container>::swap(stack &other) noexcept { // Метод обмена
  container.swap(other.container);
}

template <class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(
    const stack &other) { // Оператор присваивания копирования
  if (this != &other) {
    container = other.container;
  }
  return *this;
}

template <class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(
    stack &&other) noexcept { // Оператор присваивания перемещения
  if (this != &other) {
    container = std::move(other.container);
  }
  return *this;
}

template <class T, class Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() const {
  if (container.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return container.front(); // Должен возвращать верхний элемент стека
}

template <class T, class Container>
void stack<T, Container>::push(
    const_reference value) { // Метод добавления элемента
  container.push_front(value);
}

template <class T, class Container>
void stack<T, Container>::pop() { // Метод удаления элемента
  if (container.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return container.pop_front();
}

template <class T, class Container>
bool stack<T, Container>::empty() const { // Метод проверки на пустоту
  return container.empty();
}

template <class T, class Container>
typename stack<T, Container>::size_type
stack<T, Container>::size() const { // Метод получения размера стека
  return container.size();
}

template <class T, class Container>
T &stack<T, Container>::operator[](
    const int index) { // Оператор доступа по индексу
  if (index < 0 ||
      static_cast<s21::deque<int>::size_type>(index) >= container.size()) {
    throw std::out_of_range("Index out of range");
  }
  return container[index]; // Возвращаем элемент данных по индексу
}

template <class T, class Container>
template <class... Args>
void stack<T, Container>::insert_many_back(Args &&...args) {
  (container.push_back(std::forward<Args>(args)), ...);
}