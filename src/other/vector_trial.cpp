//
// Created by chenlei on 2021/10/17.
//

#include <algorithm>
#include <iostream>
#include <vector>

class A {
public:
    A() {
        val = 1;
        std::cout << "Default construct: " << val << std::endl;
    }

    A(int _val) : val(_val) {
        std::cout << "Parameter construct: " << val << std::endl;
    }

    A(const A &a) : val(a.val) {
        std::cout << "Copy construct: " << val << std::endl;
    }

    ~A() {
        val = -1;
        std::cout << "~,";
    }

    friend std::ostream &operator<<(std::ostream &ost, const A &a) {
        ost << a.val;
        return ost;
    }

private:
    int val, b, c;
};

class B {
public:
    B() : val(new int(1)) {
        std::cout << "Default construct: " << *val << std::endl;
    }

    B(int b) : val(new int(b)) {
        std::cout << "Parameter construct: " << *val << std::endl;
    }

    B(const B &b) : val(new int(*b.val)) {
        std::cout << "Copy construct: " << *val << std::endl;
    }

    B(B &&b) : val(b.val) {
        b.val = nullptr;
        std::cout << "Move construct: " << *val << std::endl;
    }

    ~B() {
        delete val;
        val = nullptr;
        std::cout << "~,";
    }

private:
    int *val;
};

int arr1[10];

template<typename T>
static void print_vector(const T &a) {
    for (const auto &i : a)
        std::cout << i << ",";
    std::cout << "\b\n";
}

void test_resize_reserve() {
    std::vector<A> a;
    std::cout << "====== resize to 5 ======\n";
    a.resize(5);
    std::cout << "capacity: " << a.capacity() << std::endl;  // 5
    print_vector(a);
    /**
     * 注意体会是否执行 a.reserve(10) 的区别
     */
    // a.reserve(10);
    // std::cout << "capacity: " << a.capacity() << std::endl;  // 10
    std::cout << "====== resize to 10 ======\n";
    a.resize(10, 3);
    std::cout << "capacity: " << a.capacity() << std::endl;  // 10
    print_vector(a);
    a.push_back(4);
    std::cout << "capacity:" << a.capacity() << std::endl;  // 20
    print_vector(a);
    std::cout << "====== resize to 5 ======\n";
    a.resize(5, 2);
    std::cout << "capacity:" << a.capacity() << std::endl;  // 20
    print_vector(a);
    std::cout << a[6] << std::endl;
}

void test_emplace_back() {
    std::vector<B> b;
    b.reserve(10);
    std::cout << "push left value:" << std::endl;
    B temp_b1 = 2, temp_b2 = 3;
    b.push_back(temp_b1);
    b.emplace_back(temp_b2);
    std::cout << "push right value:" << std::endl;
    b.push_back(4);
    b.emplace_back(5);

}

int main() {
    std::cout << "\n*** test resize and reserve" << std::endl;
    test_resize_reserve();
    std::cout << "\n*** test push_back and emplace_back" << std::endl;
    test_emplace_back();

    // {
    //     std::vector<A> aa(3, 10);
    //     // aa.push_back(A(7));
    //     // aa.push_back(8);
    //     aa.clear();
    //     std::cout << "clear over.\n";
    //     std::cout << aa.capacity() << std::endl;
    // }
    // std::cout << "Over!\n";
    // bool arr2[10] = {true};
    // print_vector(arr1);
    // print_vector(arr2);
    //
    // std::vector<std::string> v_s = {10, "abc"};
    // print_vector(v_s);
    // v_s = {10, "efg"};
    // print_vector(v_s);
    //
    // int size = 10;
    // int arr[size];
    // // print_vector(arr);
    // for (auto &i: arr)
    //     std::cout << i << ",";
    // std::cout << std::endl;
    //
    // std::vector<int> v1 = {10};
    // std::vector<int> v2{10};
    // print_vector(v1);
    // print_vector(v2);
    // std::vector<int> temp(25000000000);
    // std::cout << "temp, " << "max_size = " << temp.max_size() << ", capacity = " << temp.capacity() << std::endl;
    // for (int i = 0; i < 100000000; i ++) {
    //     int a = 200 + i;
    //     for (int i = 0; i < 100000000; i ++) {
    //         int b = a + i;
    //     }
    // }
    return 0;
}
