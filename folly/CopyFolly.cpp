#include <string>
#include <iostream>

/* stuct to track constructors */
struct S {
  std::string s_;

  S (std::string const &s) : s_(s) {
    std::cout << "  S::<constructor>" << std::endl;
  }

  S (S const &s) : s_(s.s_) {
    std::cout << "  S::<copy constructor>" << std::endl;
  }

  S (S&& s) noexcept : s_(std::move(s.s_)) {
    std::cout << "  S::<move constructor>" << std::endl;
  }

  ~S () {
    std::cout << "  S::<destructor>" << std::endl;
  }

};


/* construct by reference */
struct A {
  S s_;

  /* expecting one copy here */
  explicit A (const S& s) : s_(s) {
    std::cout << "  A::<constructor>" << std::endl;
  }

  A (A const &a) : s_(a.s_) {
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

  B (B const &b) : s_ (b.s_){
    std::cout << "B::<copy constructor>" << std::endl;
  }

  ~B (){
    std::cout << "B::<destructor>" << std::endl;
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

  return 0;
}
