#include <string>
#include <tuple>

struct RetVal {
  int inumber;
  std::string str;
  float fnumber;
};

RetVal create_a_struct() { return {20, std::string("baz"), 1.2f}; }

RetVal create_a_struct_named() {
  return {.inumber = 20, .str = std::string("baz"), .fnumber = 1.2f};
}

void cpp_17() {
  // auto {i, s, f} = create_a_tuple();
  // Note: proposed C++17 code, doesn't compile yet
  // The types of i, s and f are "auto"-inferred by the compiler from the return
  // type of create_a_tuple.

  // Note: proposed C++17 code, doesn't compile yet
  // The structured bindings proposal is for returned struct values as well, not
  // just tuples, so we'll be able to do this:
  // auto {i, s, f} = create_a_struct();
}

// Moreover, a different enhancement of C++17 is to permit a shorter tuple
// creation syntax as well, removing the need for std::make_tuple and making it
// as concise as struct creation:
std::tuple<int, std::string, float> create_a_tuple() {
  // error: chosen constructor is explicit in copy-initialization
  // return {20, std::string("baz"), 1.2f};
  return std::make_tuple(20, std::string("baz"), 1.2f);
}

int main() {
  return create_a_struct().inumber + create_a_struct_named().inumber +
             std::get<0>(create_a_tuple()),
         0;
}
