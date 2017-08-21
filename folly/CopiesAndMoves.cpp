#include <string>
#include <iostream>
#include <vector>

/* struct to track constructors */
struct S {
  std::string s_;

  S (const std::string &s) : s_(s) {
    std::cout << "  S::<constructor> for: " << s << std::endl;
  }

  S (const S &s) : s_(s.s_) {
    std::cout << "  S::<copy constructor> for: " << s.s_ << std::endl;
  }

  S (S&& s) noexcept : s_(std::move(s.s_)) {
    std::cout << "  S::<move constructor> for " << s_ << std::endl;
  }

  ~S () {
    std::cout << "  S::<destructor> for " << s_ << std::endl;
  }

};

/* construct by reference */
struct A {
  S s_;

  /* expecting one copy here */
  explicit A (const S& s) : s_(s) {
    std::cout << "  A::<constructor>" << std::endl;
  }

  A (const A &a) : s_(a.s_) {
    std::cout << "A::<copy constructor>" << std::endl;
  }

  ~A () {
    std::cout << "A::<destructor>" << std::endl;
  }

};

/* construct by value */
struct B{
  S s_;

  // expecting no copies here if local is moved or 1 copy of local is not moved
  explicit B (S s) : s_ (std::move(s)){
    std::cout << "  B::<constructor>" << std::endl;
  }

  B (const B &b) : s_ (b.s_){
    std::cout << "  B::<copy constructor>" << std::endl;
  }

  ~B (){
    std::cout << "  B::<destructor>" << std::endl;
  }

};

void by_reference() {
  S s1 ("some string 1");
  std::cout << "Constructor by-reference" << std::endl;
  A a1(s1);
}

void by_value_copy() {
  S s1 ("some string 1");
  std::cout << "Constructor by-value" << std::endl;
  B b1(s1);
}

void by_value_move() {
  S s1 ("some string 1");
  std::cout << "Constructor by-value+move" << std::endl;
  B b2(std::move(s1));
}

void by_value_temp_move() {
  S s1 ("some string 1");
  std::cout << "Constructor by-value+move temporary" << std::endl;
  // warning that moveing from temporary prevents RVO
  // -Wpessimizing-move
  B b3(std::move(S(std::string("Super cool"))));
}

void by_value_temp_move_rvo() {
  S s1 ("some string 1");
  std::cout << "Constructor by-value from temporary + RVO" << std::endl;
  B b4(S(std::string("Super cool")));
}

void some_method_by_reference(const A& ref) {
  std::cout << ref.s_.s_ << std::endl;
}

void some_method_by_reference(const B& ref) {
  std::cout << ref.s_.s_ << std::endl;
}

// shows that we can safely move on iteration into another vector
// with emplace_back
void emplace_into_vector() {
  std::vector<B> bs;
  std::vector<std::string> iter = {"a", "b", "c"};
  std::cout << "Emplace back movable into vector" << std::endl;
  for(const auto& element : iter) {
    bs.emplace_back(std::move(element));
  }

  for(const auto& element : bs) {
    std::cout << element.s_.s_ << std::endl;
  }
}

void process_object(const B& b) {
  std::cout << b.s_.s_ << std::endl;
}

bool return_smth(const S& a) {
  std::cout << "Inside: " << a.s_ << std::endl;
  return true;
}

S get_string() {
  S s("Local string");
  return s;
}

int main () {

  by_reference();
  std::cout << std::endl;

  by_value_copy();
  std::cout << std::endl;

  by_value_move();
  std::cout << std::endl;

  by_value_temp_move();
  std::cout << std::endl;

  by_value_temp_move_rvo();
  std::cout << std::endl;

  some_method_by_reference(A(S(std::string("cool string"))));
  std::cout << std::endl;

  some_method_by_reference(B(S(std::string("cool string"))));
  std::cout << std::endl;

  emplace_into_vector();
  std::cout << std::endl;

  process_object(B(get_string()));
  std::cout << std::endl;


  std::cout << std::endl;
  if (return_smth(S(std::string("a"))) && return_smth(S(std::string("b")))) {
    std::cout << "" << std::endl;
  }

  return 0;
}
