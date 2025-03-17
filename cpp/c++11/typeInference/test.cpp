 #include <iostream>
 #include <map>
 #include <vector>
 #include <unordered_map>

 
//  int main()
//     {
//         auto v = std::vector<std::map<std::string, float>>{
//                 {{"first" , 1.0f}}, 
//                 {{"second" , 2.0f}, {"third" , 3.0f}}
//         };

    
        
//        auto it = v.begin();
//        auto unitialized_it = decltype(it){};

//         auto result = v[0].insert({"fifth", 5.0f});
//         if (!result.second) {
//             return 1;
//         }

//         std::cout << "successfuly inserted element '"
//                   << (result.first)->second
//                   << "' at key '"
//                   << (result.first)->first
//                   << "'\n";

//         return 0;
//     }

// using namespace std;

// class Visualizer
// {
// public:
//     Visualizer(int a) : m_a(a) {cout << "Ctor" << endl;}
//     Visualizer(const Visualizer & other) : m_a(other.m_a) {cout << "Cpy Ctor" << endl;}
//     Visualizer(Visualizer && other) : m_a(other.m_a) { cout << "Move Ctor" << endl; }
//     Visualizer & operator=(const Visualizer & other) { m_a = other.m_a; cout << "Cpy Cpy Ctor" << endl; return *this; }
//     Visualizer&& operator=(Visualizer && other) { m_a = other.m_a;  cout << "Move Cpy Ctor" << endl; return std::move(*this); }
//     ~Visualizer() {}
//     ostream& operator<<(ostream& os) { os << m_a; return os; }


// private:
//     int m_a;
// };


//     Visualizer Foo(){return Visualizer(5);}
//     Visualizer &Bar(){ auto res = new Visualizer(5); return *res;}
//     Visualizer && Baz();
//     const Visualizer & Qux();

//     int main()
//     {
//         // auto a{Foo()}; // int
//         // auto & b{a}; // int&
//         // auto && c{a}; // int&&
       


//         auto d{Bar()}; //int&
//         // auto & e{Bar()};// int&
//         // auto && f{Bar()};//int&

//         // auto g{Baz()};//int&&
//         // auto & h{Baz()};// error converting rvalue to lvalue
//         // auto && i{Baz()};//int&&

//         // const auto j{Foo()};//const int
//         // const auto & k{Foo()};

//         // auto l{Qux()};
//         // const auto m{Qux()};
//         // const auto & n{Qux()};

//         // auto o{"hello"};

//         return 0;
//     }

struct Foo
{
     char arr[3];
     int val;
};

int main(){
   //const Foo foo[2] = {{{1,2,3},{5}}, {{4,5,6},{7}}};

   // std::cout << sizeof(foo) << std::endl;
std::unordered_map<std::string, int> m;
m["hello"]++;
m["hello"]++;
m["hello"]++;
std::cout << m["wello"] << "r esult"<<std::endl;

std::cout << m["hello"] << "r esult"<<std::endl;


    return 0;
}